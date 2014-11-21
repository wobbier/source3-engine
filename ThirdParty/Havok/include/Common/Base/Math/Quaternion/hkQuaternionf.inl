/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// construction

HK_FORCE_INLINE const hkVector4f& hkQuaternionf::getImag() const
{
	return m_vec;
}

HK_FORCE_INLINE void hkQuaternionf::setImag(hkVector4fParameter i)
{
	m_vec.setXYZ(i);
}


HK_FORCE_INLINE hkFloat32 hkQuaternionf::getReal() const
{
	return m_vec(3);
}

HK_FORCE_INLINE void hkQuaternionf::setReal(hkFloat32 r)
{
	m_vec(3) = r;
}

HK_FORCE_INLINE const hkSimdFloat32 hkQuaternionf::getRealPart() const
{
	return m_vec.getComponent<3>();
}

HK_FORCE_INLINE void hkQuaternionf::setRealPart(hkSimdFloat32Parameter r)
{
	m_vec.setComponent<3>(r);
}

#ifndef HK_DISABLE_MATH_CONSTRUCTORS
HK_FORCE_INLINE hkQuaternionf::hkQuaternionf(const hkRotationf& r)
{
	set(r);
}

HK_FORCE_INLINE hkQuaternionf::hkQuaternionf(hkFloat32 x, hkFloat32 y, hkFloat32 z, hkFloat32 w)
{
	set(x,y,z,w);
}

HK_FORCE_INLINE hkQuaternionf::hkQuaternionf(hkSimdFloat32Parameter x, hkSimdFloat32Parameter y, hkSimdFloat32Parameter z, hkSimdFloat32Parameter w)
{
	set(x,y,z,w);
}

HK_FORCE_INLINE hkQuaternionf::hkQuaternionf(hkVector4fParameter axis, hkFloat32 angle)
{
	setAxisAngle(axis,angle);
}
#endif

HK_FORCE_INLINE void hkQuaternionf::operator= (const hkQuaternionf& q)
{
	m_vec = q.m_vec;
}

HK_FORCE_INLINE void hkQuaternionf::set(hkFloat32 x, hkFloat32 y, hkFloat32 z, hkFloat32 w)
{
	m_vec.set(x,y,z,w);
	HK_MATH_ASSERT(0x1adaad0e,  isOk(), "hkQuaternionf components were not normalized." );
}

HK_FORCE_INLINE void hkQuaternionf::set(hkSimdFloat32Parameter x, hkSimdFloat32Parameter y, hkSimdFloat32Parameter z, hkSimdFloat32Parameter w)
{
	m_vec.set(x,y,z,w);
	HK_MATH_ASSERT(0x1adaad0e,  isOk(), "hkQuaternionf components were not normalized." );
}

HK_FORCE_INLINE void hkQuaternionf::setIdentity()
{
	m_vec = hkVector4f::getConstant<HK_QUADREAL_0001>();
}

HK_FORCE_INLINE /*static*/ const hkQuaternionf& HK_CALL hkQuaternionf::getIdentity()
{
	union { const hkQuadFloat32* r; const hkQuaternionf* q; } r2q;
	r2q.r = g_vectorfConstants + HK_QUADREAL_0001;
	return *r2q.q;
}

HK_FORCE_INLINE void hkQuaternionf::setMul(hkSimdFloat32Parameter r, hkQuaternionfParameter q)
{
	m_vec.setMul(q.m_vec, r);
}

HK_FORCE_INLINE void hkQuaternionf::addMul(hkSimdFloat32Parameter r, hkQuaternionfParameter q)
{
	m_vec.addMul(r,q.m_vec);
}

HK_FORCE_INLINE void hkQuaternionf::setMul(hkQuaternionfParameter q0, hkQuaternionfParameter q1)
{
	const hkVector4f q0Imag = q0.getImag();
	const hkVector4f q1Imag = q1.getImag();
	const hkSimdFloat32 q0Real = q0.getRealPart();
	const hkSimdFloat32 q1Real = q1.getRealPart();

	hkVector4f vec;
	vec.setCross(q0Imag, q1Imag);
	vec.addMul(q0Real, q1Imag);
	vec.addMul(q1Real, q0Imag);
	const hkSimdFloat32 w = (q0Real * q1Real) - q0Imag.dot<3>(q1Imag);
	m_vec.setXYZ_W(vec, w);
}


HK_FORCE_INLINE void hkQuaternionf::mul(hkQuaternionfParameter q)
{
	const hkVector4f thisImag = getImag();
	const hkVector4f qImag = q.getImag();
	const hkSimdFloat32 thisReal = getRealPart();
	const hkSimdFloat32 qReal = q.getRealPart();

	hkVector4f vec;
	vec.setCross(thisImag, qImag);
	vec.addMul(thisReal, qImag);
	vec.addMul(qReal, thisImag);
	const hkSimdFloat32 w = (thisReal * qReal) - thisImag.dot<3>(qImag);
	m_vec.setXYZ_W(vec, w);
}

HK_FORCE_INLINE void hkQuaternionf::setMulInverse(hkQuaternionfParameter q0, hkQuaternionfParameter q1)
{
	const hkVector4f q0Imag = q0.getImag();
	const hkVector4f q1Imag = q1.getImag();

	hkVector4f xyz; 
	xyz.setCross(q1Imag, q0Imag);
	xyz.subMul(q0.getRealPart(), q1Imag);
	xyz.addMul(q1.getRealPart(), q0Imag);
	const hkSimdFloat32 w = q0Imag.dot<4>(q1Imag);
	m_vec.setXYZ_W(xyz, w);
}

HK_FORCE_INLINE void hkQuaternionf::setInverseMul(hkQuaternionfParameter q0, hkQuaternionfParameter q1)
{
	const hkVector4f q0Imag = q0.getImag();
	const hkVector4f q1Imag = q1.getImag();

	hkVector4f xyz; 
	xyz.setCross(q1Imag, q0Imag);
	xyz.addMul(q0.getRealPart(), q1Imag);
	xyz.subMul(q1.getRealPart(), q0Imag);
	const hkSimdFloat32 w = q0Imag.dot<4>(q1Imag);
	m_vec.setXYZ_W(xyz,w);
}

HK_FORCE_INLINE void hkQuaternionf::estimateAngleTo(hkQuaternionfParameter to, hkVector4f& angleOut) const
{
	const hkVector4f fromImag = getImag();
	const hkVector4f toImag = to.getImag();

	hkVector4f angle;
	angle.setCross(fromImag, toImag);
	angle.subMul(to.getRealPart(), fromImag);
	angle.addMul(   getRealPart(), toImag);
	angle.add(angle);
	angleOut.setFlipSign( angle, toImag.dot<4>(fromImag) );
}


HK_FORCE_INLINE void hkQuaternionf::setInverse( hkQuaternionfParameter q )
{
	m_vec.setNeg<3>( q.getImag() );
}

HK_FORCE_INLINE const hkFloat32& hkQuaternionf::operator()(int i) const
{
	return m_vec(i);
}

template <int I> 
HK_FORCE_INLINE const hkSimdFloat32 hkQuaternionf::getComponent() const
{
	return m_vec.getComponent<I>(); // has asserts
}

HK_FORCE_INLINE hkFloat32 hkQuaternionf::getAngle() const
{
	return getAngleSr().getReal();
}

HK_FORCE_INLINE hkBool32 hkQuaternionf::hasValidAxis() const
{
	return m_vec.lengthSquared<3>().isGreater(hkSimdFloat32::getConstant<HK_QUADREAL_EPS_SQRD>());
}

HK_FORCE_INLINE void hkQuaternionf::getAxis(hkVector4f &axisOut) const
{
	hkVector4f axisTmp = m_vec;

	HK_MATH_ASSERT(0x266e2bd7, hasValidAxis(), "Cannot extract axis from a Quaternion representing (within numerical tolerance) the Identity rotation (or Quaternion may not be normalized).");
	axisTmp.normalize<3>();

#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	const hkVector4fComparison wLessZero = m_vec.getComponent<3>().lessZero();
	axisOut.setFlipSign(axisTmp, wLessZero);
#else
	if(m_vec(3) < hkFloat32(0))
	{
		axisOut.setNeg<4>(axisTmp);
	}
	else
	{
		axisOut = axisTmp;
	}
#endif
}

//
//	Sets the quaternion to the given quaternion, eventually transforming it so they are in the same hemisphere

HK_FORCE_INLINE void hkQuaternionf::setClosest(hkQuaternionfParameter q, hkQuaternionfParameter qReference)
{
	m_vec.setFlipSign(q.m_vec, qReference.m_vec.dot<4>(q.m_vec));
}

//
//	HK_FORCE_INLINEd. Sets/initializes this quaternion from a given rotation matrix.
//	The rotation r must be orthonormal.
//
//	HK_FORCE_INLINEd. Sets/initializes this quaternion from a given rotation matrix.
//	The rotation r must be orthonormal.

HK_FORCE_INLINE void hkQuaternion_setFromRotationFpu(const hkRotationf& r, hkVector4f& vec)
{
	const hkFloat32 trace = r(0,0) + r(1,1) + r(2,2);
	const hkFloat32 half = hkFloat32(0.5f);

	// This is an exceptional case:
	// if trace==-1.0 since this means real=sqrt(trace+1) =0.0
	// hence we can't use real to compute the imaginary terms
	// if trace is close to -1.0, then the normal algorithm is
	// subject to numerical error.
	// Either way, we should use an alternate algorithm.
	// Please see doc "Numerical Problem In Quaternion-Matrix Conversion.doc"

	HK_ALIGN_FLOAT(hkFloat32 v[4]);
	if( trace > hkFloat32(0) )
	{
		// else we calculate simply:
		hkFloat32 s = hkMath::sqrt( trace + hkFloat32(1) );
		hkFloat32 t = half / s;
		v[0] = (r(2,1)-r(1,2)) * t;
		v[1] = (r(0,2)-r(2,0)) * t;
		v[2] = (r(1,0)-r(0,1)) * t;
		v[3] = half * s;
	}
	else
	{
		const int next[] = {1,2,0};
		int i=0;

		if(r(1,1) > r(0,0)) i=1;
		if(r(2,2) > r(i,i)) i=2;

		int j = next[i];
		int k = next[j];

		hkFloat32 s = hkMath::sqrt(r(i,i) - (r(j,j)+r(k,k)) + hkFloat32(1));
		hkFloat32 t = half / s;

		v[i] = half * s;
		v[3] = (r(k,j)-r(j,k)) * t;
		v[j] = (r(j,i)+r(i,j)) * t;
		v[k] = (r(k,i)+r(i,k)) * t;
	}

	vec.load<4>(v);
}

//
//	HK_FORCE_INLINEd. Sets/initializes this quaternion from a given rotation matrix.
//	The rotation r must be orthonormal.

HK_FORCE_INLINE void hkQuaternionf::_set(const hkRotationf& r)
{

	hkQuaternion_setFromRotationFpu(r, m_vec);


	// Note: we don't renormalize here as we assume the rotation is orthonormal
	// <pk.todo> this assert breaks setAndNormalize method.
	// HK_MATH_ASSERT(0x70dc41cb, isOk(), "hkRotationf used for hkQuaternionf construction is invalid. hkQuaternionf is not normalized/invalid!");
}

template <hkMathAccuracyMode A, hkMathNegSqrtMode S>
HK_FORCE_INLINE void hkQuaternionf::setAndNormalize(const hkRotationf& r)
{
	_set(r);
	normalize<A,S>();
	HK_MATH_ASSERT(0x70dc41cc, isOk(), "hkRotationf used for hkQuaternionf construction is invalid.");
}

HK_FORCE_INLINE void hkQuaternionf::setAndNormalize(const hkRotationf& r)
{
	_set(r);
	normalize<HK_ACC_MID,HK_SQRT_IGNORE>();
	HK_MATH_ASSERT(0x70dc41cc, isOk(), "hkRotationf used for hkQuaternionf construction is invalid.");
}

template <hkMathAccuracyMode A, hkMathNegSqrtMode S>
HK_FORCE_INLINE void hkQuaternionf::normalize()
{
	m_vec.normalize<4,A,S>();
}

HK_FORCE_INLINE void hkQuaternionf::normalize()
{
	m_vec.normalize<4,HK_ACC_MID,HK_SQRT_IGNORE>();
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
