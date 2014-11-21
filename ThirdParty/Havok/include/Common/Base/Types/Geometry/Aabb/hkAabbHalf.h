/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_MATH_AABB_HALF_H
#define HK_MATH_AABB_HALF_H

#include <Common/Base/Types/Geometry/Aabb/hkAabb.h>
#include <Common/Base/Math/Vector/hkIntVector.h>

struct HK_EXPORT_COMMON hkAabbHalf
{
	//+version(1)
	HK_DECLARE_REFLECTION();

	typedef union { hkUint16	u16[8]; hkUint32	u32[4]; } data;

	HK_FORCE_INLINE	void	pack(const hkAabb& aabb)
	{
		data* mData = (data*)m_data;
		const hkUint16		extras0 = mData->u16[6];
		const hkUint16		extras1 = mData->u16[7];
		hkVector4Comparison	maskMin = aabb.m_min.lessZero();
		hkVector4Comparison	maskMax = aabb.m_max.lessZero();
		hkIntVector rdown;  rdown.load<4>(cstRoundingD);
		hkIntVector rup;    rup.load<4>(cstRoundingU);

		hkIntVector minI; minI.loadAsFloat32BitRepresentation( aabb.m_min );
		hkIntVector maxI; maxI.loadAsFloat32BitRepresentation( aabb.m_max );
		hkIntVector			iminD; iminD.setAnd(	minI, rdown);
		hkIntVector			iminU; iminU.setAddU32(	minI, rup);
		hkIntVector			imaxD; imaxD.setAnd(	maxI, rdown);
		hkIntVector			imaxU; imaxU.setAddU32(	maxI, rup);
		hkIntVector			imin; imin.setSelect(maskMin,iminU,iminD);
		hkIntVector			imax; imax.setSelect(maskMax,imaxD,imaxU);
		hkIntVector			interleaved;
		imin.setShiftRight32<16>(imin);
		imax.setAnd(imax,rdown);
		interleaved.setOr(imin,imax);
		interleaved.storeNotAligned<4>(mData->u32);
		mData->u16[6] = extras0;
		mData->u16[7] = extras1;
	}

	HK_FORCE_INLINE void	unpackUnaligned(hkAabb& aabb) const
	{
		const data* mData = (const data*)m_data;
		hkIntVector	interleaved; interleaved.loadNotAligned<4>(mData->u32);
		hkIntVector rdown; rdown.load<4>(cstRoundingD);
		hkIntVector	imin; imin.setShiftLeft32<16>(interleaved); imin.setAnd(imin,rdown);
		hkIntVector	imax; imax.setAnd(interleaved,rdown);
		imax.storeAsFloat32BitRepresentation( aabb.m_max );
		imin.storeAsFloat32BitRepresentation( aabb.m_min );
	}

	HK_FORCE_INLINE void	unpackAligned(hkAabb& aabb) const
	{
		const data* mData = (const data*)m_data;
		hkIntVector	interleaved; interleaved.load<4>(mData->u32);
		hkIntVector rdown; rdown.load<4>(cstRoundingD);
		hkIntVector	imin; imin.setShiftLeft32<16>(interleaved); imin.setAnd(imin,rdown);
		hkIntVector	imax; imax.setAnd(interleaved,rdown);
		imax.storeAsFloat32BitRepresentation( aabb.m_max );
		imin.storeAsFloat32BitRepresentation( aabb.m_min );
	}

	hkUint16	m_data[8]; ///< Packed bounding box min/max (6 shorts) + Extras padding data, kept intact during packing operation (2 shorts)

	static HK_ALIGN16(const hkUint32 cstRoundingU[4]);
	static HK_ALIGN16(const hkUint32 cstRoundingD[4]);
};

#endif // HK_MATH_AABB_HALF_H

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
