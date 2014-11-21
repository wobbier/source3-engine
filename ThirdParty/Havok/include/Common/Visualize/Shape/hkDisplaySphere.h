/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_VISUALIZE_SHAPE_SPHERE_H
#define HK_VISUALIZE_SHAPE_SPHERE_H

#include <Common/Visualize/Shape/hkDisplayGeometry.h>
#include <Common/Base/Types/Geometry/Sphere/hkSphere.h>

class HK_EXPORT_COMMON hkDisplaySphere : public hkDisplayGeometry
{
	public:
	HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
		hkDisplaySphere(const hkSphere& sphere, int subdivisions);

		virtual void buildGeometry();

		virtual void getWireframeGeometry( hkArrayBase<hkVector4>& lines, hkMemoryAllocator& a );
		
		static void HK_CALL buildIcosahedron( hkGeometry& geomOut, hkSimdRealParameter r );

		inline void getSphere(hkSphere& s) const { s = m_sphere; }
		
		inline int getSubdivisions() { return m_subdivisions; }

	protected:

		hkSphere m_sphere;

		int m_subdivisions;
};


#endif // HK_VISUALIZE_DISPLAY_SPHERE_H

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
