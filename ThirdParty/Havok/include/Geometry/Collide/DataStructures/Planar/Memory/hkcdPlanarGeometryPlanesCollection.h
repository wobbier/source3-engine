/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_HAVOK_ASSEMBLY_EXCLUDE_FILE

#ifndef HKCD_PLANE_COLLECTION_H
#define HKCD_PLANE_COLLECTION_H

#include <Common/Base/Math/Vector/hkIntVector.h>
#include <Common/Base/Container/BitField/hkBitField.h>
#include <Common/Base/Thread/CriticalSection/hkCriticalSection.h>

#include <Geometry/Collide/DataStructures/Planar/Primitives/hkcdPlanarGeometryPrimitives.h>
#include <Geometry/Collide/DataStructures/Planar/Predicates/hkcdPlanarGeometryPredicates.h>

/// Set of plane that can be shared amongst the geometries
class HK_EXPORT_COMMON hkcdPlanarGeometryPlanesCollection : public hkReferencedObject
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_GEOMETRY);
		HK_DECLARE_REFLECTION();

		typedef hkcdPlanarGeometryPrimitives::Plane			Plane;
		typedef hkcdPlanarGeometryPrimitives::PlaneId		PlaneId;
		typedef hkcdPlanarGeometryPredicates::Orientation	Orientation;

	public:

		/// Boundary planes
		enum Bounds
		{
			BOUND_POS_X	= 0,	// (+1, 0, 0)
			BOUND_NEG_X	= 1,	// (-1, 0, 0)
			BOUND_POS_Y	= 2,	// (0, +1, 0)
			BOUND_NEG_Y	= 3,	// (0, -1, 0)
			BOUND_POS_Z	= 4,	// (0, 0, +1)
			BOUND_NEG_Z	= 5,	// (0, 0, -1)

			NUM_BOUNDS	= 6,
		};

		/// Default cache size
		typedef hkcdPlanarGeometryPredicates::OrientationCacheBase<12>		OrientationCache;

	public:

		/// Empty constructor
		hkcdPlanarGeometryPlanesCollection();

		/// Default constructor
		hkcdPlanarGeometryPlanesCollection(const hkAabb& coordinateConversionAabb, int initialPlaneCapacity = 0);

		/// Copy constructor
		hkcdPlanarGeometryPlanesCollection(const hkcdPlanarGeometryPlanesCollection& other);

		/// Serialization constructor
		hkcdPlanarGeometryPlanesCollection(class hkFinishLoadedObjectFlag flag);

		/// Destructor
		virtual ~hkcdPlanarGeometryPlanesCollection();

	public:

		/// Applies the given transform on the planes. Note that this will lose precision!
		void applyTransform(const hkQTransform& transform, int numBitsTransform, bool simplifyEquations = true, int startPlaneIdx = NUM_BOUNDS, int endPlaneIdx = -1);

		/// Computes the maximum number of bits used by the plane equations
		void computeMaxNumUsedBits(int& numBitsNormal, int& numBitsOffset) const;

		/// Appends the planes of the given collection to this collection. Optionally returns the array of plane Ids for the merged planes.
		void append(const hkcdPlanarGeometryPlanesCollection& src, hkArray<PlaneId>* appendedPlaneIdsOut = HK_NULL);

		/// Welds the planes
		void weldPlanes(hkArray<int>* planesRemapTableOut);

		/// Removes all planes set in the bit-field.
		void removePlanes(const hkBitField& planesToRemove, hkArray<int>* planeRemapOut);

		/// Creates a new collection containing the welded planes of both source collections
		static hkcdPlanarGeometryPlanesCollection* HK_CALL createMergedCollection(	const hkcdPlanarGeometryPlanesCollection* planesCollectionA,
																					const hkcdPlanarGeometryPlanesCollection* planesCollectionB,
																					hkArray<int>* planesRemapTableOut);

		/// Computes a mapping between two plane collection. The first plane set provided is assumed to be included in the second plane collection.
		static void HK_CALL computeMappingBetweenPlaneSets(	const hkcdPlanarGeometryPlanesCollection* planedIncluded, 
															const hkcdPlanarGeometryPlanesCollection* planesGlobal, 
															hkArray<int>& remapTableOut);

	public:

		/// Returns the given plane
		HK_FORCE_INLINE void getPlane(PlaneId planeId, Plane& planeOut) const;

		/// Advanced use. Accesses the plane having the given Id.
		HK_FORCE_INLINE Plane& accessPlane(PlaneId planeId);

		/// Adds a new plane
		HK_FORCE_INLINE PlaneId addPlane(const Plane& plane);

		/// Allocates a new plane
		HK_FORCE_INLINE PlaneId allocPlane();

		/// Returns the number of planes stored in the collection
		HK_FORCE_INLINE int getNumPlanes() const;

		/// Removes all planes from the collection
		HK_FORCE_INLINE void clear();

		/// Gets the requested world boundary plane
		HK_FORCE_INLINE const Plane& getBoundaryPlane(Bounds b) const;

		/// Returns a valid orientation cache for this plane collection
		HK_FORCE_INLINE OrientationCache* getOrientationCache() const;

		/// Clears all the caches
		HK_FORCE_INLINE void clearCaches();

		/// Locks the plane collection for thread safe access
		HK_FORCE_INLINE void lock() const;

		/// Unlocks the plane collection
		HK_FORCE_INLINE void unlock() const;

	public:

		/// Gets / sets the offset that has been applied to all coordinates
		HK_FORCE_INLINE const hkVector4& getPositionOffset() const;
		HK_FORCE_INLINE void setPositionOffset(hkVector4Parameter vOffset);

		/// Gets / sets the scale that has been applied to all coordinates
		HK_FORCE_INLINE const hkSimdReal getPositionScale() const;
		HK_FORCE_INLINE void setPositionScale(hkSimdRealParameter scale);

		/// Converts a vertex from / to float to / from fixed-precision
		HK_FORCE_INLINE void convertWorldPosition(hkVector4Parameter vSrc, hkIntVector& vDst) const;
		HK_FORCE_INLINE void convertFixedPosition(hkIntVectorParameter vSrc, hkVector4& vDst) const;

		/// Converts a direction from world to fixed-precision
		HK_FORCE_INLINE void convertWorldDirection(hkVector4Parameter vSrc, hkIntVector& vDst) const;

	protected:

		/// Appends the world boundary planes to the collection. These 6 planes are used by various other
		/// algorithms and will always be present in the first 6 slots of any planes collection.
		void createBoundaryPlanes();

	protected:

		/// Offset that needs to be added to all points stored in the mesh. The scale is encoded in the .w component.
		hkVector4 m_offsetAndScale;

		/// The planes
		hkArray<Plane> m_planes;

		/// The orientation cache
		mutable OrientationCache* m_cache;				//+nosave

		/// For multithreaded accesses
		mutable hkCriticalSection* m_criticalAccess;	//+nosave
};

#include <Geometry/Collide/DataStructures/Planar/Memory/hkcdPlanarGeometryPlanesCollection.inl>

#endif	//	HKCD_PLANE_COLLECTION_H

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
