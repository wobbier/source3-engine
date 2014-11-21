/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

//
//	Constructor

HK_FORCE_INLINE hkDisplacementMappingUtil::DominantInfo::DominantInfo()
{
	m_data0.setZero();
	m_data1.setZero();
}

//
//	Sets the displacement normal

HK_FORCE_INLINE void hkDisplacementMappingUtil::DominantInfo::setNormal(hkVector4Parameter n)
{
	// The normal is assumed to be normalized, but make sure the components are properly clamped in between [-1, 1]
	const hkVector4 vOne	= hkVector4::getConstant<HK_QUADREAL_1>();
	const hkVector4 vHalf	= hkVector4::getConstant<HK_QUADREAL_INV_2>();
	hkVector4 vNegOne;		vNegOne.setNeg<4>(vOne);
	hkVector4 vNrm;			vNrm.setMin(n, vOne);
							vNrm.setMax(n, vNegOne);

	// Translate the n.xy components from [-1, 1] to [0.5, 1]
	vNrm.add(vOne);				// [0, 2]
	vNrm.mul(hkSimdReal_Inv4);	// [0, 0.5]
	vNrm.add(vHalf);			// [0.5, 1]

	// Encode the sign of n.z
	hkVector4 nz;	nz.setXYZ_0(n);										// [x, y, z, 0]
					nz.setPermutation<hkVectorPermutation::ZWWW>(nz);	// [z, 0, 0, 0]
	vNrm.setFlipSign(vNrm, nz.lessZero());								// Sets vNrm.x in [-1, -0.5] iff z < 0.
	
	// Finally, store
#if defined(HK_REAL_IS_DOUBLE)
	{
		HK_ALIGN16(hkFloat32) conversionBuf[4];
		vNrm.store<4>(conversionBuf);
		hkVector4f vNrmF; vNrmF.load<4>(conversionBuf);
		m_data1.setSelect<hkVector4ComparisonMask::MASK_XY>(vNrmF, m_data1);
	}
#else
	m_data1.setSelect<hkVector4ComparisonMask::MASK_XY>(vNrm, m_data1);
#endif
}

//
//	Retrieves the normal

HK_FORCE_INLINE void hkDisplacementMappingUtil::DominantInfo::getNormal(hkVector4& nrmOut) const
{
	const hkVector4f vOne	= hkVector4f::getConstant<HK_QUADREAL_1>();
	const hkVector4f vHalf	= hkVector4f::getConstant<HK_QUADREAL_INV_2>();

	// Extract the sign of Z
	hkVector4f sz;	sz.setPermutation<hkVectorPermutation::XXXX>(m_data1);	// sign(z)

	// Translate the .xy components from [0.5, 1] to [-1, 1]
	hkVector4f xy;	xy.setAbs(m_data1);				// [0.5, 1]
					xy.sub(vHalf);					// [0, 0.5]
					xy.mul(hkSimdFloat32_4);			// [0, 2]
					xy.sub(vOne);					// [-1, 1]
	hkSimdFloat32 nz= xy.dot<2>(xy);				// (nx * nx + ny * ny)
					nz.setSub(hkSimdFloat32_1, nz);	// 1 - (nx * nx + ny * ny)
					nz.setFlipSign(nz.sqrt<HK_ACC_FULL, HK_SQRT_SET_ZERO>(), sz.lessZero());	// Set proper sign

	// Store
	xy.setComponent<2>(nz);
#if defined(HK_REAL_IS_DOUBLE)
	{
		HK_ALIGN16(hkDouble64) conversionBuf[4];
		xy.store<4>(conversionBuf);
		nrmOut.load<4>(conversionBuf);
	}
#else
	nrmOut = xy;
#endif
}

//
//	Gets / sets the interpolation factor between the two displacement maps

HK_FORCE_INLINE const hkSimdReal hkDisplacementMappingUtil::DominantInfo::getBlendFactor() const
{
#if defined(HK_REAL_IS_DOUBLE)
	return hkSimdReal::fromFloat(m_data1.getComponent<2>().getReal());
#else
	return m_data1.getComponent<2>();
#endif
}

HK_FORCE_INLINE void hkDisplacementMappingUtil::DominantInfo::setBlendFactor(hkSimdRealParameter f)
{
#if defined(HK_REAL_IS_DOUBLE)
	const hkSimdFloat32 ff = hkSimdFloat32::fromFloat((hkFloat32)f.getReal());
	m_data1.setComponent<2>(ff);
#else
	m_data1.setComponent<2>(f);
#endif
}

//
//	Gets / sets the displacement amount, i.e. a factor in [0, 1] used to scale the displacement normal

HK_FORCE_INLINE const hkSimdReal hkDisplacementMappingUtil::DominantInfo::getDisplacement() const
{
#if defined(HK_REAL_IS_DOUBLE)
	return hkSimdReal::fromFloat(m_data1.getComponent<3>().getReal());
#else
	return m_data1.getComponent<3>();
#endif
}

HK_FORCE_INLINE void hkDisplacementMappingUtil::DominantInfo::setDisplacement(hkSimdRealParameter d)
{
#if defined(HK_REAL_IS_DOUBLE)
	const hkSimdFloat32 dd = hkSimdFloat32::fromFloat((hkFloat32)d.getReal());
	m_data1.setComponent<3>(dd);
#else
	m_data1.setComponent<3>(d);
#endif
}

//
//	Sets the I-th uv

template <>
HK_FORCE_INLINE void hkDisplacementMappingUtil::DominantInfo::setUv<0>(hkVector4Parameter uv)
{
#if defined(HK_REAL_IS_DOUBLE)
	{
		HK_ALIGN16(hkFloat32) convBuffer[4];
		uv.store<4>(convBuffer);
		hkVector4f uvf;	uvf.load<4>(convBuffer);
		m_data0.setSelect<hkVector4ComparisonMask::MASK_XY>(uvf, m_data0);
	}
#else
	m_data0.setSelect<hkVector4ComparisonMask::MASK_XY>(uv, m_data0);
#endif
}

template <>
HK_FORCE_INLINE void hkDisplacementMappingUtil::DominantInfo::setUv<1>(hkVector4Parameter uv)
{	
	hkVector4 uvuv;
	uvuv.setPermutation<hkVectorPermutation::XYXY>(uv);

#if defined(HK_REAL_IS_DOUBLE)
	{
		HK_ALIGN16(hkFloat32) convBuffer[4];
		uvuv.store<4>(convBuffer);
		hkVector4f uvuvf;	uvuvf.load<4>(convBuffer);
		m_data0.setSelect<hkVector4ComparisonMask::MASK_ZW>(uvuvf, m_data0);
	}
#else
	m_data0.setSelect<hkVector4ComparisonMask::MASK_ZW>(uvuv, m_data0);
#endif
}

//
//	Sets the uv for the i-th map

HK_FORCE_INLINE void hkDisplacementMappingUtil::DominantInfo::setUv(int mapIdx, hkVector4Parameter uv)
{
	const int m				= (mapIdx * hkVector4ComparisonMask::MASK_ZW + (1 - mapIdx) * hkVector4ComparisonMask::MASK_XY);
	hkVector4fComparison c;	c.set((hkVector4ComparisonMask::Mask)m);

	hkVector4f uvuv;
#if defined(HK_REAL_IS_DOUBLE)
	{
		HK_ALIGN16(hkFloat32) convBuffer[4];
		uv.store<4>(convBuffer);
		hkVector4f uvf;	uvf.load<4>(convBuffer);
		uvuv.setPermutation<hkVectorPermutation::XYXY>(uvf);
	}
#else
	uvuv.setPermutation<hkVectorPermutation::XYXY>(uv);
#endif

	m_data0.setSelect(c, uvuv, m_data0);
}

//
//	Returns the uv for the i-th map

HK_FORCE_INLINE void hkDisplacementMappingUtil::DominantInfo::getUv(int mapIdx, hkVector4& uvOut) const
{
	hkVector4f uv1;			uv1.setPermutation<hkVectorPermutation::ZWZW>(m_data0);
	const int m				= (-mapIdx) & hkVector4ComparisonMask::MASK_XYZW;	// map0 -> MASK_NONE, map1 -> MASK_XYZW
	hkVector4fComparison c;	c.set((hkVector4ComparisonMask::Mask)m);
	hkVector4f uvOutF;		uvOutF.setSelect(c, uv1, m_data0);

#if defined(HK_REAL_IS_DOUBLE)
	{
		HK_ALIGN16(hkDouble64) convBuffer[4];
		uvOutF.store<4>(convBuffer);
		uvOut.load<4>(convBuffer);
	}
#else
	uvOut = uvOutF;
#endif
}

//
//	Gets the displacement vector

HK_FORCE_INLINE void hkDisplacementMappingUtil::DominantInfo::getDisplacementVector(hkVector4& dOut) const
{
	hkVector4 n;
	getNormal(n);
	dOut.setMul(n, getDisplacement());
}

//
//	Sets the displacement vector (i.e. n = normalize(vD), d = length(vD))

HK_FORCE_INLINE void hkDisplacementMappingUtil::DominantInfo::setDisplacementVector(hkVector4Parameter vD, hkSimdRealParameter tol)
{
	hkSimdReal d			= vD.length<3>();
	hkSimdReal invD;		invD.setReciprocal<HK_ACC_FULL, HK_DIV_SET_ZERO>(d);
	hkVector4 n;			n.setMul(vD, invD);
	hkVector4Comparison cmp	= d.greater(tol);

	invD.setZero();
	n.setSelect(cmp, n, hkVector4::getConstant<HK_QUADREAL_1000>());	setNormal(n);
	d.setSelect(cmp, d, invD);											setDisplacement(d);
}

//
//	Permutes the displacement maps

HK_FORCE_INLINE void hkDisplacementMappingUtil::DominantInfo::permuteDisplacementMaps()
{
	// Flip uvs
	m_data0.setPermutation<hkVectorPermutation::ZWXY>(m_data0);

	// Flip blending factor
	hkSimdReal fBlend;
	fBlend.setSub(hkSimdReal_1, getBlendFactor());
	setBlendFactor(fBlend);
}

//
//	Returns the I-th element

HK_FORCE_INLINE hkDisplacementMappingUtil::DominantInfo& hkDisplacementMappingUtil::DominantsBuffer::operator[](int i)
{
	return *reinterpret_cast<DominantInfo*>(m_data + sizeof(Descriptor) + sizeof(DominantInfo) * i);
}

HK_FORCE_INLINE const hkDisplacementMappingUtil::DominantInfo& hkDisplacementMappingUtil::DominantsBuffer::operator[](int i) const
{
	return *reinterpret_cast<const DominantInfo*>(m_data + sizeof(Descriptor) + sizeof(DominantInfo) * i);
}

//
//	Loads the values from a buffer

HK_FORCE_INLINE void hkDisplacementMappingUtil::DominantInfo::load(const void* buffer)
{
	const hkFloat32* HK_RESTRICT ptr = reinterpret_cast<const hkFloat32*>(buffer);
	m_data0.load<4, HK_IO_NATIVE_ALIGNED>(&ptr[0]);
	m_data1.load<4, HK_IO_NATIVE_ALIGNED>(&ptr[4]);
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
