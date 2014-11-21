/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

//
template <hkMathSortDir ORDER, typename KEYS>
HK_FORCE_INLINE void hkVectorSort::sort(const KEYS& keys, KEYS* HK_RESTRICT keysOut)
{
	// Compare exchange [XY,ZW]
	KEYS	yxwz_v; yxwz_v.template setPermutation<hkVectorPermutation::YXWZ>(keys);
	KEYS	yyww; yyww.template setPermutation<hkVectorPermutation::YYWW>(keys);
	KEYS	xxzz; xxzz.template setPermutation<hkVectorPermutation::XXZZ>(keys);
	
	hkVector4Comparison c1 = vectorCompareT<ORDER>(yyww, xxzz);
	
	KEYS	k1; k1.template setSelect(c1, yxwz_v, keys);
			
	// Compare exchange [XZ,YW]
	KEYS	zwxy_v; zwxy_v.template setPermutation<hkVectorPermutation::ZWXY>(k1);
	KEYS	zwzw; zwzw.template setPermutation<hkVectorPermutation::ZWZW>(k1);
	KEYS	xyxy; xyxy.template setPermutation<hkVectorPermutation::XYXY>(k1);
	
	hkVector4Comparison c2 = vectorCompareT<ORDER>(zwzw,xyxy);
	
	KEYS	k2; k2.template setSelect(c2, zwxy_v, k1);
	
	// Compare exchange [YZ]
	KEYS	xzyw_v; xzyw_v.template setPermutation<hkVectorPermutation::XZYW>(k2);
	KEYS	xzzw; xzzw.template setPermutation<hkVectorPermutation::XZZW>(k2);
	KEYS	xyyw; xyyw.template setPermutation<hkVectorPermutation::XYYW>(k2);
	
	hkVector4Comparison c3 = vectorCompareT<ORDER>(xzzw,xyyw);
	
	KEYS	k3; k3.setSelect(c3, xzyw_v, k2);
	
	// Store results.
	*keysOut = k3;
}

//
template <hkMathSortDir ORDER, typename KEYS, typename VALUES>
HK_FORCE_INLINE void hkVectorSort::sort(const KEYS& keys, const VALUES& values, KEYS* HK_RESTRICT keysOut, VALUES* HK_RESTRICT valuesOut)
{
	// Compare exchange [XY,ZW]
	VALUES	yxwz_v; yxwz_v.template setPermutation<hkVectorPermutation::YXWZ>(values);
	KEYS	yxwz_k; yxwz_k.template setPermutation<hkVectorPermutation::YXWZ>(keys);
	KEYS	yyww; yyww.template setPermutation<hkVectorPermutation::YYWW>(keys);
	KEYS	xxzz; xxzz.template setPermutation<hkVectorPermutation::XXZZ>(keys);
	
	hkVector4Comparison c1 = vectorCompareT<ORDER>(yyww, xxzz);
	
	KEYS	k1; k1.setSelect(c1, yxwz_k, keys);
	VALUES	v1; v1.setSelect(c1, yxwz_v, values);
			
	// Compare exchange [XZ,YW]
	VALUES	zwxy_v; zwxy_v.template setPermutation<hkVectorPermutation::ZWXY>(v1);
	KEYS	zwxy_k; zwxy_k.template setPermutation<hkVectorPermutation::ZWXY>(k1);
	KEYS	zwzw; zwzw.template setPermutation<hkVectorPermutation::ZWZW>(k1);
	KEYS	xyxy; xyxy.template setPermutation<hkVectorPermutation::XYXY>(k1);
	
	hkVector4Comparison c2 = vectorCompareT<ORDER>(zwzw,xyxy);
	
	KEYS	k2; k2.setSelect(c2, zwxy_k, k1);
	VALUES	v2; v2.setSelect(c2, zwxy_v, v1);

	// Compare exchange [YZ]
	VALUES	xzyw_v; xzyw_v.template setPermutation<hkVectorPermutation::XZYW>(v2);
	KEYS	xzyw_k; xzyw_k.template setPermutation<hkVectorPermutation::XZYW>(k2);
	KEYS	xzzw; xzzw.template setPermutation<hkVectorPermutation::XZZW>(k2);
	KEYS	xyyw; xyyw.template setPermutation<hkVectorPermutation::XYYW>(k2);
	
	hkVector4Comparison c3 = vectorCompareT<ORDER>(xzzw,xyyw);
	
	KEYS	k3; k3.setSelect(c3, xzyw_k, k2);
	VALUES	v3; v3.setSelect(c3, xzyw_v, v2);

	// Store results.
	*keysOut = k3;
	*valuesOut = v3;		
}

//
template <hkMathSortDir ORDER, typename KEYS, typename VALUES0, typename VALUES1>
HK_FORCE_INLINE void hkVectorSort::sort(const KEYS& keys, const VALUES0& values0, const VALUES1& values1, KEYS* HK_RESTRICT keysOut, VALUES0* HK_RESTRICT values0Out, VALUES1* HK_RESTRICT values1Out)
{
	// Compare exchange [XY,ZW]
	VALUES0	yxwz_v0; yxwz_v0.template setPermutation<hkVectorPermutation::YXWZ>(values0);
	VALUES1	yxwz_v1; yxwz_v1.template setPermutation<hkVectorPermutation::YXWZ>(values1);
	KEYS	yxwz_k; yxwz_k.template setPermutation<hkVectorPermutation::YXWZ>(keys);
	KEYS	yyww; yyww.template setPermutation<hkVectorPermutation::YYWW>(keys);
	KEYS	xxzz; xxzz.template setPermutation<hkVectorPermutation::XXZZ>(keys);
	
	hkVector4Comparison c1 = vectorCompareT<ORDER>(yyww, xxzz);
	
	KEYS	k1; k1.setSelect(c1, yxwz_k, keys);
    VALUES0	v10; v10.setSelect(c1, yxwz_v0, values0);
    VALUES1	v11; v11.setSelect(c1, yxwz_v1, values1);
			
	// Compare exchange [XZ,YW]
	VALUES0	zwxy_v0; zwxy_v0.template setPermutation<hkVectorPermutation::ZWXY>(v10);
	VALUES1	zwxy_v1; zwxy_v1.template setPermutation<hkVectorPermutation::ZWXY>(v11);
	KEYS	zwxy_k; zwxy_k.template setPermutation<hkVectorPermutation::ZWXY>(k1);
	KEYS	zwzw; zwzw.template setPermutation<hkVectorPermutation::ZWZW>(k1);
	KEYS	xyxy; xyxy.template setPermutation<hkVectorPermutation::XYXY>(k1);
	
	hkVector4Comparison c2 = vectorCompareT<ORDER>(zwzw,xyxy);
	
	KEYS	k2; k2.setSelect(c2, zwxy_k, k1);
	VALUES0	v20; v20.setSelect(c2, zwxy_v0, v10);
	VALUES1	v21; v21.setSelect(c2, zwxy_v1, v11);

	// Compare exchange [YZ]
	VALUES0	xzyw_v0; xzyw_v0.template setPermutation<hkVectorPermutation::XZYW>(v20);
	VALUES1	xzyw_v1; xzyw_v1.template setPermutation<hkVectorPermutation::XZYW>(v21);
	KEYS	xzyw_k; xzyw_k.template setPermutation<hkVectorPermutation::XZYW>(k2);
	KEYS	xzzw; xzzw.template setPermutation<hkVectorPermutation::XZZW>(k2);
	KEYS	xyyw; xyyw.template setPermutation<hkVectorPermutation::XYYW>(k2);
	
	hkVector4Comparison c3 = vectorCompareT<ORDER>(xzzw,xyyw);
	
	KEYS	k3; k3.setSelect(c3, xzyw_k, k2);
	VALUES0	v30; v30.setSelect(c3, xzyw_v0, v20);
	VALUES1	v31; v31.setSelect(c3, xzyw_v1, v21);

	// Store results.
	*keysOut = k3;
	*values0Out = v30;
	*values1Out = v31;
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
