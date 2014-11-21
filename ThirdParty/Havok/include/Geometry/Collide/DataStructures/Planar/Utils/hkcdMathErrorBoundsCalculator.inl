/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

//
//	Returns the unit in the last place for the given number, x

HK_FORCE_INLINE void HK_CALL hkcdMathErrorBoundsCalculator::ulp(hkVector4dParameter xIn, hkVector4d& ulpOut)
{
	HK_ALIGN32(hkUint64 buf[4]);
	// Cast from double to its bits.
	hkInt64Vector4 x;		xIn.store<4, HK_IO_NATIVE_ALIGNED>((hkDouble64*)buf);
							x.load<4, HK_IO_SIMD_ALIGNED>(buf);

	// Clear the sign bit and set mantissa to 1.0
	hkInt64Vector4 mMask;
	mMask.setAll(0x7FF0000000000000L);
	x.setAnd(x, mMask);					// x = 1.0 * 2^E

	// Subtract numMantissaBits units from the exponent
	const hkUint64 MB		= 52;
	hkInt64Vector4 mBits;	mBits.setAll(MB << MB);				// mBits = 1.0 * 2^53
							x.setSub(x, mBits);					// x = E - 53

	// Set negative exponents to zero
	mBits.setZero();
	x.setSelect(x.lessZero(), mBits, x);

	// Write output
	x.store<4, HK_IO_SIMD_ALIGNED>(buf);
	ulpOut.load<4, HK_IO_NATIVE_ALIGNED>((hkDouble64*)buf);
}

//
//	Returns the unit in the last place for the given number, x

HK_FORCE_INLINE void HK_CALL hkcdMathErrorBoundsCalculator::ulp(hkSimdDouble64Parameter xIn, hkSimdDouble64& ulpOut)
{
	const hkInt64 MB = 52;
	HK_ALIGN32(hkInt64) x;

	// Cast from double to its bits.
	xIn.store<1, HK_IO_SIMD_ALIGNED>((hkDouble64*)&x);

	// Clear the sign bit and set mantissa to 1.0
	x = x & 0x7FF0000000000000L;	// x = 1.0 * 2^E
	x = x - (MB << MB);				// Subtract numMantissaBits units from the exponent
	x = (x < 0) ? 0 : x;			// Set negative exponents to zero

	// Write output
	ulpOut.load<1, HK_IO_SIMD_ALIGNED>((hkDouble64*)&x);
}

//
//	Adds the scalars

HK_FORCE_INLINE void hkcdMathErrorBoundsCalculator::Scalar::setAdd(const Scalar& vA, const Scalar& vB)
{
	m_val.setAdd(vA.m_val, vB.m_val);

	// Propagate error present in the source value
	ulp(m_val, m_err);
	m_err.add(vA.m_err);
	m_err.add(vB.m_err);
}

//
//	Multiplies the vectors

HK_FORCE_INLINE void hkcdMathErrorBoundsCalculator::Scalar::setMul(const Scalar& vA, const Scalar& vB)
{
	m_val.setMul(vA.m_val, vB.m_val);

	// Propagate errors present in the source values
	hkSimdDouble64 errA;	errA.setAbs(vA.m_val);
							errA.mul(vB.m_err);
	hkSimdDouble64 errB;	errB.setAbs(vB.m_val);
							errB.mul(vA.m_err);
	hkSimdDouble64 errAB;	errAB.setMul(vA.m_err, vB.m_err);
							errAB.add(errA);
							errAB.add(errB);

	// Add the ulp of the result
	ulp(m_val, m_err);
	m_err.add(errAB);
}

//
//	Sets this = xA / xB

HK_FORCE_INLINE void hkcdMathErrorBoundsCalculator::Scalar::setDiv(const Scalar& xA, const Scalar& xB)
{
	m_val.setDiv<HK_ACC_FULL, HK_DIV_IGNORE>(xA.m_val, xB.m_val);

	// Propagate error present in the source value
	ulp(m_val, m_err);

	// Let A' = A + eA, B' = B + eB, where A, B are the true values and eA, eB are their errors
	// The error during division is:
	//		(A'/B') - (A/B) = (A + eA) / (B - eB) - (A/B)					// use subtraction to maximize the error
	//						= (A/B) * (1 + (eA/A)) / (1 - (eB/B)) - (A/B)	// Use the Taylor expansion of (1-x)^(-1) in x = 0, i.e. f(x) = 1 + x + x^2 + x^3 + ... and eval f(eB/B)
	//						= (A/B) * (1 + (eA/A)) * (1 + (eB/B)) - (A/B)
	//				approx	= (A/B) * (1 + (eA/A) + (eB/B)) - (A/B)
	//						= (eA/B) + (A/B) * (eB/B)

	// For the reciprocal case, A = 1, eA = 0
	hkSimdDouble64 e;
	
	e.setDiv<HK_ACC_FULL, HK_DIV_IGNORE>(xA.m_err, xB.m_val);	// (eA/B)
	e.setAbs(e);
	m_err.add(e);												// ulp + (eA/B)

	e.setDiv<HK_ACC_FULL, HK_DIV_IGNORE>(xB.m_err, xB.m_val);	// (eB/B)
	e.mul(m_val);												// (A/B) * (eB/B)
	e.setAbs(e);
	m_err.add(e);												// ulp + (eA/B) + (A/B) * (eB/B)
}

//
//	Sets this = 1 / x

HK_FORCE_INLINE void hkcdMathErrorBoundsCalculator::Scalar::setReciprocal(const Scalar& x)
{
	Scalar one;
	one.m_val = hkSimdDouble64_1;
	one.m_err.setZero();
	setDiv(one, x);
}

//
//	Sets the vector value and computes the error

HK_FORCE_INLINE void hkcdMathErrorBoundsCalculator::Vector::set(hkVector4dParameter x)
{
	m_val = x;
	ulp(m_val, m_err);
}

//
//	Sets the vector value

HK_FORCE_INLINE void hkcdMathErrorBoundsCalculator::Vector::set(const Scalar& x, const Scalar& y, const Scalar& z, const Scalar& w)
{
	m_val.set(x.m_val, y.m_val, z.m_val, w.m_val);
	m_err.set(x.m_err, y.m_err, z.m_err, w.m_err);
}

//
//	Adds the vectors

HK_FORCE_INLINE void hkcdMathErrorBoundsCalculator::Vector::setAdd(const Vector& vA, const Vector& vB)
{
	m_val.setAdd(vA.m_val, vB.m_val);

	// Propagate errors present in the source values
	ulp(m_val, m_err);
	m_err.add(vA.m_err);
	m_err.add(vB.m_err);
}

//
//	Multiplies the vectors

HK_FORCE_INLINE void hkcdMathErrorBoundsCalculator::Vector::setMul(const Vector& vA, const Vector& vB)
{
	m_val.setMul(vA.m_val, vB.m_val);

	// Propagate errors present in the source values
	hkVector4d errA;	errA.setAbs(vA.m_val);
						errA.mul(vB.m_err);
	hkVector4d errB;	errB.setAbs(vB.m_val);
						errB.mul(vA.m_err);
	hkVector4d errAB;	errAB.setMul(vA.m_err, vB.m_err);
						errAB.add(errA);
						errAB.add(errB);

	// Add the ulp of the result
	ulp(m_val, m_err);
	m_err.add(errAB);
}

//
//	Permutes the vector

template <hkVectorPermutation::Permutation p>
HK_FORCE_INLINE void hkcdMathErrorBoundsCalculator::Vector::setPermutation(const Vector& x)
{
	m_val.setPermutation<p>(x.m_val);
	m_err.setPermutation<p>(x.m_err);
}

//
//	Negates the vector

HK_FORCE_INLINE void hkcdMathErrorBoundsCalculator::Vector::setNeg(const Vector& x)
{
	m_val.setNeg<4>(x.m_val);
	m_err = x.m_err;
}

//
//	Subtracts the vectors

HK_FORCE_INLINE void hkcdMathErrorBoundsCalculator::Vector::setSub(const Vector& vA, const Vector& vB)
{
	Vector mB;
	mB.setNeg(vB);
	setAdd(vA, mB);
}

//
//	Computes the cross produt

HK_FORCE_INLINE void hkcdMathErrorBoundsCalculator::Vector::setCross(const Vector& vA, const Vector& vB)
{
	// Shuffle
	Vector a_yzx;	a_yzx.setPermutation<hkVectorPermutation::YZXW>(vA);	// [ay, az, ax]
	Vector a_zxy;	a_zxy.setPermutation<hkVectorPermutation::ZXYW>(vA);	// [az, ax, ay]
	Vector b_yzx;	b_yzx.setPermutation<hkVectorPermutation::YZXW>(vB);	// [by, bz, bx]
	Vector b_zxy;	b_zxy.setPermutation<hkVectorPermutation::ZXYW>(vB);	// [bz, bx, by]

	Vector abp;	abp.setMul(a_yzx, b_zxy);	// [ay bz, az bx, ax by]
	Vector abn;	abn.setMul(a_zxy, b_yzx);	// [az by, ax bz, ay bx]
	setSub(abp, abn);						// [ay bz - az by, az bx - ax bz, ax by - ay bx]
}

//
//	Returns the I-th component

template <int I>
HK_FORCE_INLINE void hkcdMathErrorBoundsCalculator::Vector::getComponent(Scalar& componentOut) const
{
	componentOut.m_val = m_val.getComponent<I>();
	componentOut.m_err = m_err.getComponent<I>();
}

//
//	Sign flip

HK_FORCE_INLINE void hkcdMathErrorBoundsCalculator::Vector::setFlipSign(const Vector& v, hkVector4dComparisonParameter m)
{
	m_val.setFlipSign(v.m_val, m);
	m_err = v.m_err;
}

//
//	Computes the dot product

template <>
HK_FORCE_INLINE void HK_CALL hkcdMathErrorBoundsCalculator::Vector::dot<3>(const Vector& vA, const Vector& vB, Scalar& dotAB)
{
	// Do the component multiplies
	Vector mAB;	mAB.setMul(vA, vB);
	Scalar d;

	mAB.getComponent<0>(dotAB);
	mAB.getComponent<1>(d);			dotAB.setAdd(d, dotAB);
	mAB.getComponent<2>(d);			dotAB.setAdd(d, dotAB);
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
