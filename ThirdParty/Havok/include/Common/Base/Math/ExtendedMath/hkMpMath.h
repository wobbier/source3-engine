/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_MP_MATH_H
#define HK_MP_MATH_H

#include <Common/Base/System/Io/OStream/hkOStream.h>
#include <Common/Base/Container/String/hkStringBuf.h>

#define HK_MP_PRINT_RATIONAL_AS_DOUBLE

/// Multi-precision unsigned integer.
/// Adapted from Matt McCutchen's 'C++ Big Integer Library' @ https://mattmccutchen.net/bigint/
struct HK_EXPORT_COMMON hkMpUint
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_MATH, hkMpUint);

	//
	typedef hkUint32	Atom;
	typedef hkUint16	HalfAtom;

	//
	enum
	{
		BITS_PER_ATOM		=	sizeof(Atom) * 8,
		BITS_PER_HALF_ATOM	=	BITS_PER_ATOM >> 1,
	};

	//
	typedef hkArray<Atom> AtomArray;
	
	//
	HK_FORCE_INLINE				hkMpUint() {}

	//
	HK_FORCE_INLINE				hkMpUint(const hkMpUint& other) { operator=(other); }

	//
	HK_FORCE_INLINE int			getSize() const { return m_atoms.getSize(); }

	//
	HK_FORCE_INLINE int			getSizeInBits() const { return getSize() * BITS_PER_ATOM; }

	//
	HK_FORCE_INLINE int			msb() const;

	//
	HK_FORCE_INLINE bool		isZero() const { return getSize() == 0; }
	
	//
	HK_FORCE_INLINE void		setZero() { m_atoms.clear(); }

	//
	HK_FORCE_INLINE hkMpUint&	operator=(const hkMpUint& other) { if(this != &other) { m_atoms = other.m_atoms; } return *this; }
	
	//
	HK_FORCE_INLINE Atom&		operator[](int index) { return m_atoms[index]; }

	//
	HK_FORCE_INLINE Atom		operator[](int index) const { return m_atoms[index]; }

	//
	HK_FORCE_INLINE void		stripLeadingZeros() { while(m_atoms.getSize() && 0 == m_atoms.back()) m_atoms.popBack(); }

	//
	HK_FORCE_INLINE Atom		getAtom(int index, int shift) const;
	
	//
	friend inline void			set(hkMpUint& bi, hkUint64 value);
	
	//
	friend int					compare(const hkMpUint& bi0, const hkMpUint& bi1);

	//
	friend void					pow(hkMpUint& bi, unsigned exp);
	
	//
	friend void					add(const hkMpUint& bi0, const hkMpUint& bi1, hkMpUint& biOut);
	
	//
	friend void					sub(const hkMpUint& bi0, const hkMpUint& bi1, hkMpUint& biOut);
		
	//
	friend void					mul(const hkMpUint& bi0, const hkMpUint& bi1, hkMpUint& biOut);
	
	//
	friend void					div(const hkMpUint& bi0, const hkMpUint& bi1, hkMpUint& qOut);
	
	//
	friend void					mod(const hkMpUint& bi0, const hkMpUint& bi1, hkMpUint& rOut);
	
	//
	friend void					div(const hkMpUint& bi0, const hkMpUint& bi1, hkMpUint& qOut, hkMpUint& rOut);
		
	//
	friend void					gcd(const hkMpUint& x, const hkMpUint& y, hkMpUint& output);

	// x << count if count > 0 else x >> -count
	friend void					shift(hkMpUint& x, int count);
	
	//
	friend void					toString(const hkMpUint& bi, unsigned base, hkStringBuf& stringOut);

	//
	friend hkOstream&			operator<<(hkOstream& stream, const hkMpUint& bi) { hkStringBuf s; toString(bi,10,s); stream << s; return stream; }
	
	private:

	AtomArray	m_atoms;
};

///
/// Multi-precision rational.
///
struct HK_EXPORT_COMMON hkMpRational
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_MATH, hkMpRational);

	//
	HK_FORCE_INLINE					hkMpRational(hkInt32 num = 0, hkInt32 den = 1) { setNumeratorAndDemominator(num, den); }

	//
	HK_FORCE_INLINE					hkMpRational(hkUint32 num, hkUint32 den = 1) { setNumeratorAndDemominator(num, den); }
	
	//
	HK_FORCE_INLINE					hkMpRational(hkInt64 num, hkInt64 den = 1) { setNumeratorAndDemominator(num, den); }

	//
	HK_FORCE_INLINE					hkMpRational(hkUint64 num, hkUint64 den = 1) { setNumeratorAndDemominator(num, den); }

	//
	HK_FORCE_INLINE					hkMpRational(hkReal value) { set(*this, value); }

	//
	HK_FORCE_INLINE					hkMpRational(hkSimdRealParameter value) { set(*this, value); }
	
	//
	HK_FORCE_INLINE bool			isZero() const { return m_num.isZero(); }

	//
	HK_FORCE_INLINE bool			isLessZero() const { return m_signed; }

	//
	HK_FORCE_INLINE bool			isLessEqualZero() const { return isLessZero() || isZero(); }

	//
	HK_FORCE_INLINE bool			isGreaterZero() const { return !isZero() && !m_signed; }

	//
	HK_FORCE_INLINE bool			isGreaterEqualZero() const { return !m_signed; }

	//
	HK_FORCE_INLINE void			setZero() { m_num.setZero(); m_den.setZero(); m_signed = false; }

	//
	HK_FORCE_INLINE bool			isInfinity() const { return m_den.isZero(); }

	//
	HK_FORCE_INLINE int				getSign() const { return isZero() ? 0 : (m_signed ? -1 : +1); }

	//
	HK_FORCE_INLINE void			cleanZero() { if(isZero()) m_signed = false; }

	//
	HK_FORCE_INLINE int				compareTo(const hkMpRational& rat) const { return compare(*this, rat); }
	
	//
	inline hkMpRational				operator+(const hkMpRational& rat) const { hkMpRational r; add(*this, rat, r); return r; }

	//
	inline hkMpRational				operator-(const hkMpRational& rat) const { hkMpRational r; sub(*this, rat, r); return r; }

	//
	inline hkMpRational				operator*(const hkMpRational& rat) const { hkMpRational r; mul(*this, rat, r); return r; }

	//
	inline hkMpRational				operator/(const hkMpRational& rat) const { hkMpRational r; div(*this, rat, r); return r; }

	//
	inline hkMpRational				operator^(int power) const { hkMpRational r = *this; pow(r,power); return r; }
	
	//
	friend int						compare(const hkMpRational& rat0, const hkMpRational& rat1);

	//
	friend int						compare(const hkMpRational& rat, const hkMpUint& bi);

	//
	friend int						compare(const hkMpUint& bi, const hkMpRational& rat) { return compare(rat, bi) * -1; }

	//
	friend void						abs(hkMpRational& rat) { rat.m_signed = false; }

	//
	friend void						round(hkMpRational& rat) { hkMpUint intVal; get(rat, intVal); rat.m_num = intVal; set(rat.m_den,1); rat.cleanZero(); }
	
	//
	friend void						inv(hkMpRational& rat);
	
	//
	friend void						pow(hkMpRational& rat, int exp);

	//
	friend inline void				neg(hkMpRational& rat) { if(!rat.isZero()) rat.m_signed = !rat.m_signed; }
	
	//
	friend void						compact(hkMpRational& rat);

	//
	friend void						sum(const hkMpRational& rat0, bool sgn0, const hkMpRational& rat1, bool sgn1, hkMpRational& ratOut);
	
	//
	friend void						add(const hkMpRational& rat0, const hkMpRational& rat1, hkMpRational& ratOut);
	
	//
	friend void						sub(const hkMpRational& rat0, const hkMpRational& rat1, hkMpRational& ratOut);
	
	//
	friend void						mul(const hkMpRational& rat0, const hkMpRational& rat1, hkMpRational& ratOut);

	//
	friend void						mul(const hkMpRational& rat, const hkMpUint& bi, hkMpRational& ratOut);
	
	//
	friend void						div(const hkMpRational& rat0, const hkMpRational& rat1, hkMpRational& ratOut);

	//
	friend void						set(hkMpRational& ratOut, float value) { setIEEE<23>(ratOut,*reinterpret_cast<hkUint32*>(&value)); }

	//
	friend void						set(hkMpRational& ratOut, double value) { setIEEE<52>(ratOut,*reinterpret_cast<hkUint64*>(&value));	}

	//
	friend void						set(hkMpRational& ratOut, hkSimdRealParameter value) { set(ratOut, value.getReal()); }
	
	//
	template <typename TN, typename TD>
	inline void						setNumeratorAndDemominator(TN numerator, TD denominator);
		
	//
	friend void						get(const hkMpRational& rat, hkMpUint& valueOut);

	//
	friend void						get(const hkMpRational& rat, float& valueOut) { hkMpRational::getIEEE<23>(rat, *reinterpret_cast<hkUint32*>(&valueOut)); }

	//
	friend void						get(const hkMpRational& rat, double& valueOut) { hkMpRational::getIEEE<52>(rat, *reinterpret_cast<hkUint64*>(&valueOut)); }

	//
	friend void						get(const hkMpRational& rat, hkSimdReal& valueOut) { hkReal v; get(rat,v); valueOut.setFromFloat(v); }

	//
	template <int MANTISSA_BITS, typename T>
	inline static void				setIEEE(hkMpRational& ratOut, T valueAsUint);

	//
	template <int MANTISSA_BITS, typename T>
	inline static void				getIEEE(const hkMpRational& rat, T& valueAsUint);

	//
	friend void						toString(const hkMpRational& rat, unsigned base, hkStringBuf& stringOut);

	//
	friend hkOstream&				operator<<(hkOstream& stream, const hkMpRational& rat)
	{
		#ifdef HK_MP_PRINT_RATIONAL_AS_DOUBLE
		double value = 0; get(rat, value);
		stream << value;
		#else
		if(m_signed) stream << '-';
		stream << m_num;
		stream << '/';
		stream << m_den;
		#endif
		return stream;
	}

	private:
	
	hkMpUint	m_num;
	hkMpUint	m_den;
	bool		m_signed;
};

///
/// Multi-precision vector.
///
template <int N>
struct HK_EXPORT_COMMON hkMpVector
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_MATH, hkMpVector);

	enum { DIMENSIONS = N };

	//
	HK_FORCE_INLINE						hkMpVector() {}

	//
	HK_FORCE_INLINE						hkMpVector(hkVector4Parameter value) { set(*this, value); }

	//
	HK_FORCE_INLINE						hkMpVector(hkSimdRealParameter value) { set(*this, value); }
	
	//
	HK_FORCE_INLINE						hkMpVector(hkReal value) { set(*this, value); }

	//
	HK_FORCE_INLINE hkMpRational&		operator[](int i) { HK_ASSERT2(0x45FE2134, i >= 0 && i < N, "Index out of range."); return m_components[i]; }

	//
	HK_FORCE_INLINE const hkMpRational&	operator[](int i) const { HK_ASSERT2(0x45FE2135, i >= 0 && i < N, "Index out of range."); return m_components[i]; }

	//
	friend void							compact(hkMpVector<N>& v)
	{
		for(int i=0; i<N; ++i) compact(v[i]);
	}

	//
	friend void							neg(hkMpVector<N>& v)
	{
		for(int i=0; i<N; ++i) neg(v[i]);
	}

	//
	friend void							inv(hkMpVector<N>& v)
	{
		for(int i=0; i<N; ++i) inv(v[i]);
	}

	//
	friend void							add(const hkMpVector<N>& v0, const hkMpVector<N>& v1, hkMpVector<N>& vOut)
	{
		for(int i=0; i<N; ++i) add(v0[i], v1[i], vOut[i]);
	}

	//
	friend void							sub(const hkMpVector<N>& v0, const hkMpVector<N>& v1, hkMpVector<N>& vOut)
	{
		for(int i=0; i<N; ++i) sub(v0[i], v1[i], vOut[i]);
	}

	//
	friend void							mul(const hkMpVector<N>& v0, const hkMpVector<N>& v1, hkMpVector<N>& vOut)
	{
		for(int i=0; i<N; ++i) mul(v0[i], v1[i], vOut[i]);
	}

	//
	friend void							mul(const hkMpVector<N>& v0, const hkMpRational& r1, hkMpVector<N>& vOut)
	{
		for(int i=0; i<N; ++i) mul(v0[i], r1, vOut[i]);
	}
	
	//
	friend void							div(const hkMpVector<N>& v0, const hkMpVector<N>& v1, hkMpVector<N>& vOut)
	{
		for(int i=0; i<N; ++i) div(v0[i], v1[i], vOut[i]);
	}

	//
	friend void							div(const hkMpVector<N>& v0, const hkMpRational& r1, hkMpVector<N>& vOut)
	{
		for(int i=0; i<N; ++i) div(v0[i], r1, vOut[i]);
	}

	//
	friend void							mins(const hkMpVector<N>& v0, const hkMpVector<N>& v1, hkMpVector<N>& vOut)
	{
		for(int i=0; i<N; ++i) vOut[i] = compare(v0[i], v1[i]) < 0 ? v0[i] : v1[i];
	}

	//
	friend void							maxs(const hkMpVector<N>& v0, const hkMpVector<N>& v1, hkMpVector<N>& vOut)
	{
		for(int i=0; i<N; ++i) vOut[i] = compare(v0[i], v1[i]) > 0 ? v0[i] : v1[i];
	}

	//
	friend void							horizontalMin(const hkMpVector<N>& v, hkMpRational& rOut)
	{
		hkMpRational current = v[0];
		for(int i = 1; i < N; ++i) if(compare(current, v[i]) < 0) current = v[i];
		rOut = current;
	}

	//
	friend void							horizontalMax(const hkMpVector<N>& v, hkMpRational& rOut)
	{
		hkMpRational current = v[0];
		for(int i = 1; i < N; ++i) if(compare(current, v[i]) > 0) current = v[i];
		rOut = current;
	}

	//
	friend void							horizontalSum(const hkMpVector<N>& v, hkMpRational& rOut)
	{
		hkMpRational current = v[0];
		for(int i = 1; i < N; ++i) add(current, v[i], current);
		rOut = current;
	}

	//
	friend void							cross(const hkMpVector<N>& v0, const hkMpVector<N>& v1, hkMpVector<N>& vOut)
	{
		HK_COMPILE_TIME_ASSERT(N >= 3);
		hkMpRational	p0,p1;
	
		mul(v0[1], v1[2], p0);
		mul(v0[2], v1[1], p1);
		hkMpRational	x; sub(p0, p1, x);

		mul(v0[2], v1[0], p0);
		mul(v0[0], v1[2], p1);
		hkMpRational	y; sub(p0, p1, y);

		mul(v0[0], v1[1], p0);
		mul(v0[1], v1[0], p1);
		hkMpRational	z; sub(p0, p1, z);

		vOut[0] = x;
		vOut[1] = y;
		vOut[2] = z;

		for(int i=N; i<N; ++i) vOut[i].setZero();
	}

	//
	friend void							dot(const hkMpVector<N>& v0, const hkMpVector<N>& v1, hkMpRational& rOut)
	{
		hkMpVector<N> p; mul(v0, v1, p);
		horizontalSum(p, rOut);
	}

	//
	friend void							dotAdd(const hkMpVector<N>& v0, const hkMpVector<N>& v1, const hkMpRational& offset, hkMpRational& rOut)
	{
		hkMpVector<N>	p; mul(v0, v1, p);
		hkMpRational	s; horizontalSum(p, s);
		add(s, offset, rOut);
	}

	//
	friend void							lengthSquared(const hkMpVector<N>& v, hkMpRational& rOut)
	{
		dot(v,v,rOut);
	}

	//
	friend void							distanceSquared(const hkMpVector<N>& v0, const hkMpVector<N>& v1, hkMpRational& rOut)
	{
		hkMpVector<N> delta; sub(v1,v0,delta);
		lengthSquared(delta, rOut);
	}

	//
	friend void							interpolate(const hkMpVector<N>& v0, const hkMpVector<N>& v1, const hkMpRational& fraction, hkMpVector<N>& vOut)
	{
		hkMpVector<N>	dv;
		sub(v1,v0,dv);
		mul(dv, fraction, dv);
		add(v0, dv, vOut);
	}

	//
	friend void							set(hkMpVector<N>& v, hkVector4Parameter value)
	{
		for(int i=0, n = N > 4 ? 4 : N; i<n; ++i)
		{
			set(v[i], value(i));
		}
	}

	//
	friend void							set(hkMpVector<N>& v, hkSimdRealParameter value)
	{
		set(v, value.getReal());
	}

	//
	friend void							set(hkMpVector<N>& v, hkReal value)
	{
		hkMpRational rv; set(rv,value);
		for(int i=0; i<N; ++i) v[i] = rv;
	}

	//
	friend void 						get(const hkMpVector<N>& v, hkVector4& value)
	{
		value.setZero();
		for(int i=0, n = N > 4 ? 4 : N; i<n; ++i)
		{
			get(v[i], value(i));
		}
	}

	//
	friend void							toString(const hkMpVector<N>& v, unsigned base, hkStringBuf& stringOut)
	{
		hkStringBuf t;
		stringOut.append("[");
		for(int i=0; i<N; ++i)
		{
			if(i) stringOut.append(",");
			toString(v[i], base, t);
			stringOut.append(t.cString());
		}
		stringOut.append("]");
	}

	//
	friend hkOstream&					operator<<(hkOstream& stream, const hkMpVector<N>& v)
	{
		stream << '[';
		for(int i=0; i<N; i++)
		{
			if(i) stream << ',';
			stream << v[i];
		}
		stream << ']';
		return stream;
	}

	private:

	hkMpRational	m_components[N];
};

// Solve Ax=b using Gauss-Seidel method. Note: No pivoting is performed so the diagonal of A must be non-zero.
// Axb_TYPE must implement the following:
// int					dims() const;
// const hkMpRational&	A(int row, int column) const;
// const hkMpRational&	b(int column) const;
// hkMpRational&		x(int column);
template <typename Axb_TYPE>
inline void hkMpLinearSolveGaussSeidel(Axb_TYPE& Axb, int iterations);

// Enable unit tests only on win32/64
bool	hkMpUnitTests();

#include <Common/Base/Math/ExtendedMath/hkMpMath.inl>

#endif // HK_MP_MATH_H

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
