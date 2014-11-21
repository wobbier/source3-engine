/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

template<typename IntegerType>
hkResult hkXmlStreamParser::getIntListAttribute(const char* key, hkArray<IntegerType>& out) const
{
	HK_COMPILE_TIME_ASSERT(hkTrait::IsConvertibleTo<IntegerType, hkInt64>::result);

	hkSubString subString;
	if (getValue(key, subString) != HK_SUCCESS)
	{
		return HK_FAILURE;
	}

	if (!(subString.m_start[0] == '"' && subString.m_end[-1] == '"'))
	{
		return HK_FAILURE;
	}
	subString.m_start++;
	subString.m_end--;

	for(const char* it = subString.m_start; it < subString.m_end; ++it)
	{
		// Find the next comma or end of string
		const char* endIt = it;
		while(endIt != subString.m_end && *endIt != ',')
		{
			++endIt;
		}

		hkSubString substr(it, endIt);
		hkInt64 valueOut;
		if(parseInt(substr, valueOut) == HK_FAILURE)
		{
			return HK_FAILURE;
		}

		out.pushBack(static_cast<IntegerType>(valueOut));

		it = endIt;
	}

	return HK_SUCCESS;
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
