/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_COMPAT_SERIALIZE_DEPRECATED_H
#define HK_COMPAT_SERIALIZE_DEPRECATED_H

#include <Common/Serialize/Packfile/hkPackfileWriter.h>
#include <Common/Serialize/Util/hkSerializeUtil.h>

class HK_EXPORT_COMMON hkSerializeDeprecated : public hkReferencedObject, public hkSingleton<hkSerializeDeprecated>
{
	public:

		struct XmlPackfileHeader
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(XmlPackfileHeader, HK_MEMORY_CLASS_BASE);

			int m_classVersion;
			hkStringPtr m_contentsVersion;
			hkStringPtr m_topLevelObject;

			bool supportsPredicates() const { return m_classVersion >= 10; }
			hkUint16 m_maxpredicate;
			hkArray<hkUint16> m_truePredicates;
		};

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
		hkSerializeDeprecated() {}

		static void HK_CALL initDeprecated();

			/// Whether or not deprecated serialization has been enabled.
		virtual bool isEnabled() const;
		
		virtual hkResult saveXmlPackfile( const void* object, const hkClass& klass, hkStreamWriter* writer, const hkPackfileWriter::Options& options, hkPackfileWriter::AddObjectListener* userListener, hkSerializeUtil::ErrorDetails* errorOut );
		virtual hkBool32 isLoadable(const hkSerializeUtil::FormatDetails& details);
		virtual hkResource* loadOldPackfile(hkStreamReader& sr, const hkSerializeUtil::FormatDetails& details, hkSerializeUtil::ErrorDetails* errorOut);
		virtual hkObjectResource* loadOldPackfileOnHeap(hkStreamReader& sr, const hkSerializeUtil::FormatDetails& details, hkSerializeUtil::ErrorDetails* errorOut);

			/// Reads an XML packfile header from buffer.
		virtual hkResult readXmlPackfileHeader(hkStreamReader* stream, XmlPackfileHeader& out, hkSerializeUtil::ErrorDetails* errorOut);
};

namespace hkSerializeDeprecatedInit
{
	// You need to link to hkCompat if you call this
	void HK_CALL initDeprecated();
};	


#endif // HK_COMPAT_SERIALIZE_DEPRECATED_H

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
