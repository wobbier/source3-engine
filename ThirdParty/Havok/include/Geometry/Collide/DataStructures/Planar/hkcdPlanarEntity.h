/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_HAVOK_ASSEMBLY_EXCLUDE_FILE

#ifndef HKCD_PLANAR_ENTITY_H
#define HKCD_PLANAR_ENTITY_H

#include <Common/Base/Math/Vector/hkIntVector.h>
#include <Common/Base/Types/Geometry/hkGeometry.h>

#include <Geometry/Collide/DataStructures/Planar/Primitives/hkcdPlanarGeometryPrimitives.h>
#include <Geometry/Collide/DataStructures/Planar/Memory/hkcdPlanarGeometryPolygonCollection.h>
#include <Geometry/Collide/DataStructures/Planar/Memory/hkcdPlanarGeometryPlanesCollection.h>
#include <Geometry/Collide/DataStructures/Planar/Predicates/hkcdPlanarGeometryPredicates.h>

/// Base class for a planar geometry debugger
class HK_EXPORT_COMMON hkcdPlanarEntityDebugger : public hkReferencedObject
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_GEOMETRY);

	public:

		/// Constructor
		hkcdPlanarEntityDebugger()
		:	hkReferencedObject()
		{}

	public:

		/// Called by the geometric entities during processing. Can be used to capture snapshots of the geometries during execution.
		virtual void addTrace(const char* debugTraceString, const class hkcdPlanarEntity* callerEntity) {}

		/// Called by the geometric entities during processing.
		virtual int addGeometry(const char* geometryName, const hkGeometry* tempGeometry) { return -1; }
};

/// Base class for all plane-based geometric objects
class HK_EXPORT_COMMON hkcdPlanarEntity : public hkReferencedObject
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_GEOMETRY);
		HK_DECLARE_REFLECTION();

	public:

		// Types
		typedef hkcdPlanarGeometryPrimitives::Plane						Plane;
		typedef hkcdPlanarGeometryPrimitives::PlaneId					PlaneId;
		typedef hkcdPlanarGeometryPolygonCollection::Polygon			Polygon;
		typedef hkcdPlanarGeometryPolygonCollection::PolygonId			PolygonId;
		typedef hkcdPlanarGeometryPredicates::Orientation				Orientation;
		typedef hkcdPlanarGeometryPlanesCollection::OrientationCache	OrientationCache;
		typedef hkcdPlanarGeometryPlanesCollection						PlanesCollection;

	public:

		/// Constructor
		hkcdPlanarEntity(hkcdPlanarEntityDebugger* debugger = HK_NULL)
		:	hkReferencedObject()
		,	m_debugger(debugger)
		{}

		/// Copy constructor
		hkcdPlanarEntity(const hkcdPlanarEntity& other)
		:	hkReferencedObject()
		,	m_debugger(other.m_debugger)
		{}

		/// Serialization constructor
		hkcdPlanarEntity(class hkFinishLoadedObjectFlag flag)
		:	hkReferencedObject(flag)
		{}

		/// Builds a vertex-based geometry representation from this entity. Default implementation does nothing.
		virtual void extractGeometry(hkGeometry& geomOut) const {}

	public:

		/// Returns the debugger
		HK_FORCE_INLINE const hkcdPlanarEntityDebugger* getDebugger()	const	{	return m_debugger;	}
		HK_FORCE_INLINE hkcdPlanarEntityDebugger* accessDebugger()				{	return m_debugger;	}

	protected:

		/// Adds a debug trace
		HK_FORCE_INLINE void addTrace(const char* debugString) const
		{
			if ( m_debugger )
			{
				m_debugger->addTrace(debugString, this);
			}
		}

	protected:

		/// The debugger, can be null
		hkRefPtr<hkcdPlanarEntityDebugger> m_debugger;		//+nosave
};

#endif	//	HKCD_PLANAR_ENTITY_H

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
