/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

//
HK_FORCE_INLINE hkMpUint::Atom	hkMpUint::getAtom(int index, int shift) const
{
	const Atom	a0 = (index == 0 || shift == 0) ? 0 : m_atoms[index-1] >> Atom(BITS_PER_ATOM - shift);
	const Atom	a1 = (index == getSize()) ? 0 : m_atoms[index] << Atom(shift);
	return a0 | a1;
}

//
HK_FORCE_INLINE int				hkMpUint::msb() const
{
	if(m_atoms.getSize())
	{
		int		the_msb = sizeof(Atom) * 8 * (m_atoms.getSize() - 1);
		Atom	value = m_atoms.back();
		do { value >>= 1; the_msb++; } while(value);
		return the_msb;
	}
	return 0;
}

//
inline void						set(hkMpUint& bi, hkUint64 value)
{
	bi.m_atoms.setSize(0);
	if(value)
	{
		do
		{
			hkMpUint::HalfAtom ha[2];
			ha[0] = value & ((1 << hkMpUint::BITS_PER_HALF_ATOM) - 1); value >>= hkMpUint::BITS_PER_HALF_ATOM;
			ha[1] = value & ((1 << hkMpUint::BITS_PER_HALF_ATOM) - 1); value >>= hkMpUint::BITS_PER_HALF_ATOM;
			bi.m_atoms.pushBack( (((hkMpUint::Atom)ha[1]) << hkMpUint::BITS_PER_HALF_ATOM) | ha[0] );
		} while(value);
	}
}

//
template <typename TN, typename TD>
inline void						hkMpRational::setNumeratorAndDemominator(TN numerator, TD denominator)
{
	// the float casts are here to silence PlayStation(R)3 compiler warnings about comparing unsigned TN and TD with 0
	if((float)denominator < 0)
	{
		numerator = TN(0)-numerator;
		denominator = TD(0)-denominator;
	}
	m_signed = (float)numerator < 0;
	set(m_num, m_signed ? TN(0)-numerator : numerator);
	set(m_den, denominator);	
}

//
template <int MANTISSA_BITS, typename T>
void							hkMpRational::setIEEE(hkMpRational& ratOut, T valueAsUint)
{
	const int EXP_BITS = sizeof(T) * 8 - 1 - MANTISSA_BITS;
	HK_COMPILE_TIME_ASSERT( sizeof(T) * 8 == (1 + EXP_BITS + MANTISSA_BITS) );

	if(valueAsUint == 0)
	{
		ratOut.setNumeratorAndDemominator(0, 1);
		return;
	}
	
	const T bias = T((1 << (EXP_BITS - 1)) - 1);
	const T mask = T(1 << EXP_BITS) - 1;
	const T	s = valueAsUint >> (T(EXP_BITS + MANTISSA_BITS));
	const T e = (valueAsUint >> (T(MANTISSA_BITS))) & ((1 << EXP_BITS)-1);
	const T f = (valueAsUint << (T(EXP_BITS + 1))) >> (T(EXP_BITS + 1));

	if(e == mask)
	{
		if(f == 0)
		{
			ratOut.setNumeratorAndDemominator(s ? -1 : +1, 0);
			return;
		}
		else
		{
			HK_ERROR(0x5955E4AF, "Cannot represent NAN.");
		}
	}

	const bool		denorm = e == 0;
	hkMpUint		m; set(m, f | (denorm ? T(0) : T(1) << (T(MANTISSA_BITS))));
	const int		en = int(e) - int(bias) + (denorm?1:0) - MANTISSA_BITS;
	ratOut.setNumeratorAndDemominator(2,1);
	pow(ratOut, en);
	mul(ratOut, m, ratOut);
	ratOut.m_signed = s ? true : false;
}

//
// Note, this is more or less an implementation of the following method described in gmp / get_d.c:
// "
// An alternative algorithm, that may be faster:
//   0. Let n be somewhat larger than the number of significant bits in a double.
//   1. Extract the most significant n bits of the denominator, and an equal
//      number of bits from the numerator.
//   2. Interpret the extracted numbers as integers, call them a and b
//      respectively, and develop n bits of the fractions ((a + 1) / b) and
//      (a / (b + 1)) using mpn_divrem.
//   3. If the computed values are identical UP TO THE POSITION WE CARE ABOUT,
//      we are done.  If they are different, repeat the algorithm from step 1,
//      but first let n = n * 2.
//   4. If we end up using all bits from the numerator and denominator, fall
//      back to a plain division.
//   5. Just to make life harder, The computation of a + 1 and b + 1 above
//      might give carry-out...  Needs special handling.  It might work to
//      subtract 1 in both cases instead.
// "
template <int MANTISSA_BITS, typename T>
void							hkMpRational::getIEEE(const hkMpRational& rat, T& valueAsUint)
{
	const int EXP_BITS = sizeof(T) * 8 - 1 - MANTISSA_BITS;
	HK_COMPILE_TIME_ASSERT( sizeof(T) * 8 == (1 + EXP_BITS + MANTISSA_BITS) );

	valueAsUint = 0;
	if(!rat.isZero())
	{
		const hkMpRational	one(1);
		const hkMpRational	two(2);
		const hkMpRational	minBound = hkMpRational(2) ^ MANTISSA_BITS;
		const hkMpRational	maxBound = minBound * two;
		
		hkMpRational	absRat = rat; abs(absRat);
		hkMpRational	b0_rat; div(minBound, absRat, b0_rat);
		const bool		invLog = compare(b0_rat,one) < 0;
		if(invLog) inv(b0_rat);

		hkMpUint		approx; get(b0_rat, approx);
		
		int				msb = approx.msb();
		if(invLog) msb = -(msb + 1);
		
		const hkMpRational	scale = two ^ msb;
		hkMpRational		scaledRat = absRat * scale;
		
		int				e = MANTISSA_BITS - msb;
		
		while(compare(scaledRat,minBound) < 0)
		{
			mul(scaledRat, two, scaledRat);
			e--;
		}

		while(compare(scaledRat,maxBound) > 0)
		{
			div(scaledRat, two, scaledRat);
			e++;
		}

		hkMpUint	bm; get(scaledRat, bm);
		
		if(compare(maxBound, bm) <= 0)
		{
			div(bm,two.m_num,bm);
			e++;
		}

		e += (1 << (EXP_BITS - 1)) - 1;

		T				m = 0;
		for(int i=0; i<bm.getSize(); ++i)
		{
			m <<= 16;
			m <<= 16;
			m |= bm[bm.getSize()-i-1];
		}

		const int	maxExp = (1 << EXP_BITS) - 1;

		if(e >= maxExp)
		{
			e = maxExp;
			m = 0;
		}

		if(e <= 0)
		{
			e = 0;
			m = 0;
		}
		
		if(e)
		{
			m &= ~(T(1) << MANTISSA_BITS);
		}

		valueAsUint	=	rat.m_signed ? 1 :0;
		valueAsUint =	(valueAsUint << EXP_BITS) | e;
		valueAsUint	=	(valueAsUint << MANTISSA_BITS) | m;
	}
}

//
template <typename Axb_TYPE>
inline void hkMpLinearSolveGaussSeidel(Axb_TYPE& Axb, int iterations)
{
	const int		n = Axb.dims();
	hkMpRational	product,sum,alpha;	
	int				iteration = 0;
	for(; iteration < iterations; iteration++)
	{
		for(int i=0; i<n; ++i)
		{
			alpha.setZero();
			for(int j=0; j<n; ++j)
			{
				if(j == i) continue;
				mul(Axb.A(i,j), Axb.x(j), product);
				add(alpha, product, alpha);
			}
			div(hkMpRational(1), Axb.A(i,i), product);
			sub(Axb.b(i), alpha, sum);
			mul(product, sum, Axb.x(i));
			compact(Axb.x(i));
		}
	}
}

/*
 * Havok SDK - NO SOURCE PC DOWNLOAD, BUILD(#20140907)
 * 
 * Confidential Information of Havok.  (C) Copyright 1999-2014
 * Telekinesys Research Limited t/a Havok. All Rights Reserved. The Havok
 * Logo, and the Havok buzzsaw logo are trademarks of Havok.  Title, ownership
 * rights, and intellectual property rights in the Havok software remain in
 * Havok and/or its suppliers.
 * 
 * Use of this software for evaluation purposes is subject to and indicates
 * acceptance of the End User licence Agreement for this product. A copy of
 * the license is included with this software and is also available at www.havok.com/tryhavok.
 * 
 */
