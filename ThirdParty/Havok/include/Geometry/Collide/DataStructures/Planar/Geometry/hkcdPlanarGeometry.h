/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_HAVOK_ASSEMBLY_EXCLUDE_FILE

#ifndef HKCD_PLANAR_GEOMETRY_H
#define HKCD_PLANAR_GEOMETRY_H

#include <Geometry/Collide/DataStructures/Planar/hkcdPlanarEntity.h>
#include <Geometry/Collide/DataStructures/Planar/Predicates/hkcdPlanarGeometryPredicates.h>
#include <Geometry/Collide/DataStructures/Planar/Memory/hkcdPlanarGeometryPlanesCollection.h>

/// Geometry representation where vertices are stored implicitly as intersections of 3 planes.
class HK_EXPORT_COMMON hkcdPlanarGeometry : public hkcdPlanarEntity
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_GEOMETRY);
		HK_DECLARE_REFLECTION();

		/// Constants
		enum
		{
			INVALID_MATERIAL_ID	= 0x0FFFFFFF,	///< Material Ids cannot be greater than or equal to INVALID_MATERIAL_ID.
		};

		typedef hkcdPlanarGeometryPolygonCollection::VertexId		VertexId;

		struct VertexStorage : public hkReferencedObject, public hkArray<hkVector4d>
		{
			HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_GEOMETRY);
		
			virtual ~VertexStorage()
			{}
		};

	public:

		/// Constructor
		hkcdPlanarGeometry(PlanesCollection* planesCollection = HK_NULL, int initialPolyCapacity = 0, hkcdPlanarEntityDebugger* debugger = HK_NULL);

		/// Constructor with polygon collection
		hkcdPlanarGeometry(PlanesCollection* planesCollection, hkcdPlanarGeometryPolygonCollection* polygonCollection, hkcdPlanarEntityDebugger* debugger = HK_NULL);

		/// Copy constructor
		hkcdPlanarGeometry(const hkcdPlanarGeometry& other);

		/// Serialization constructor
		hkcdPlanarGeometry(class hkFinishLoadedObjectFlag flag);

		/// Destructor
		virtual ~hkcdPlanarGeometry();

	public:

		/// Retrieves all valid polygon Ids
		void getAllPolygons(hkArray<PolygonId>& polygonsOut) const;

		/// Collects all planes used by the given polygons
		void getAllPolygonsPlanes(const hkArray<PolygonId>& polygonsIn, hkArray<PlaneId>& planesOut, bool collectBoundaryPlanes) const;

		/// Classifies a triangle w.r.t. a plane. The result is approximative, as it uses floating-point operations
		hkcdPlanarGeometryPredicates::Orientation approxClassify(PolygonId polygonId, PlaneId planeId) const;

		/// Classifies a triangle w.r.t. a plane
		hkcdPlanarGeometryPredicates::Orientation classify(PolygonId polygonId, PlaneId planeId) const;

		/// Splits a polygon with the given splitting plane. Returns the part of the polygon inside the given plane
		void split(PolygonId polygonId, PlaneId splitPlaneId, PolygonId& insidePolygonIdOut, PolygonId& outsidePolygonIdOut);

		/// Returns true if two given polygon on the same support plane potentially overlap. False means that the surfaces of the two polygon do not overlap.
		bool check2dIntersection(const PolygonId& polygonA, const PolygonId& polygonB) const;
		static bool HK_CALL check2dIntersection(const hkcdPlanarGeometry& geomA, const PolygonId& polygonIdA,
												const hkcdPlanarGeometry& geomB, const PolygonId& polygonIdB);

		/// Clips a polygon with the given planes. Returns the number of boundary planes.
		hkUint32 clipPolygon(PlaneId supportPlaneId, PlaneId*& boundsIn, PlaneId*& boundsOut, int numBounds, const PlaneId* clippingPlanesIn, int numClippingPlanesIn);

		/// Removes the given polygons from the mesh
		void removePolygons(const hkArray<PolygonId>& polygonIds);

		/// Removes all polygons that are not present in the given list. The given list of polygon Ids must be sorted ascending!
		void keepPolygons(const hkArray<PolygonId>& polygonIds);

		/// Remaps the material ids of the polygons given a remap table
		void remapPolygonMaterialIds(hkArray<hkUint32>& remapTable);

		/// Builds a vertex-based geometry representation from this entity.
		virtual void extractGeometry(hkGeometry& geomOut) const HK_OVERRIDE;

		/// Builds a vertex-based geometry representation for the given polygon
		void extractPolygonGeometry(PolygonId polyId, hkGeometry& geomOut) const;

		/// Builds a vertex-based geometry representation for the given polygon
		void extractPolygonsGeometry(const hkArray<PolygonId>& polyIds, hkGeometry& geomOut) const;

		/// Welds the planes so that all planes are unique
		void weldPlanes(hkArray<int>* planeRemapTable = HK_NULL);

		/// Weld polygon vertices to save memory
		void weldPolygonVertices();

		/// Adds all polygons from the given geometry to this geometry. The planes are assumed to be already present in this geometry,
		/// and a mapping from other to this geometry planes is expected as input
		void appendGeometryPolygons(const hkcdPlanarGeometry& srcGeom, int* HK_RESTRICT planeRemapTable, hkUint32 maxPlaneIdValue, const hkArray<PolygonId>& polygonIdsToAdd, hkArray<PolygonId>& addedPolygonIdsOut, bool flipWinding = false, int materialOffset = 0);

		/// Adds the given polygons to this geometry and returns the newly added polygon Ids.
		void appendGeometryPolygons(const hkcdPlanarGeometry& srcGeom, const hkArray<PolygonId>& srcPolygonIds, bool flipWinding, hkArray<PolygonId>& dstPolygonIds, int materialOffset = 0);

		/// Collects a bit-field of plane Ids used by the polygons
		void collectUsedPlaneIds(hkBitField& usedPlaneIdsOut) const;

		/// Collects a bit-field of material Ids used by the polygons
		void collectUsedMaterialIds(hkBitField& usedMatIdsOut) const;

		/// Returns whether the geometry contains polygon with invalid material
		bool containsPolygonsWithInvalidMaterial() const;

	public:

		/// Sets a new planes collection. If the plane remapping table is non-null, the plane Ids on all nodes will be re-set as well (i.e. to match the plane Ids in the new collection)
		void setPlanesCollection(PlanesCollection* newPlanes, const int* HK_RESTRICT planeRemapTable);

		/// Shift all plane ids in the geom polygons
		void shiftPlaneIds(int offsetValue);

		/// Checks planes consistency within the geometry
		bool checkPlanesConsistency() const;

		/// Deduce the approximate vertex position for the given polygon using plane intersections
		void computePolygonApproxVertices(const PolygonId& polyId);

		/// (Debug only) check if the cached value at polygon vertices are valid
		void checkPolygonCachedValues(const PolygonId& polyId);

		/// (Debug only) check if the given polygon is convex
		void checkPolygonConvexity(const PolygonId& polyId);

		/// Recompute all the vertices pos given the current plane state. This assumes that all polygons have valid vertex ids
		void recomputeVerticesCache(int nbEstimatedVertices = 0);

		/// Transforms the vertex cache
		void transformVerticesCache(const hkQTransform& tranform, bool rotate);

		/// Reference the vertices cache from the given geometry
		void copyVerticesCacheFrom(const hkcdPlanarGeometry& other);

		/// Returns the plane collection associated with this geometry
		HK_FORCE_INLINE const PlanesCollection* getPlanesCollection() const;
		HK_FORCE_INLINE PlanesCollection* accessPlanesCollection();

		/// Adds a new polygon
		HK_FORCE_INLINE PolygonId addPolygon(PlaneId supportPlane, hkUint32 material, int numBounds);

		/// Returns the polygon at the given Id
		HK_FORCE_INLINE const Polygon& getPolygon(PolygonId polyId) const;
		HK_FORCE_INLINE Polygon& accessPolygon(PolygonId polyId);

		/// Computes the number of boundary planes
		HK_FORCE_INLINE int getNumBoundaryPlanes(PolygonId polyId) const;

		/// Returns the collection of polygons
		HK_FORCE_INLINE const hkcdPlanarGeometryPolygonCollection& getPolygons() const;
		HK_FORCE_INLINE hkcdPlanarGeometryPolygonCollection& accessPolygons();
		HK_FORCE_INLINE void setPolygons(hkcdPlanarGeometryPolygonCollection* polys);

	protected:

		/// The planes
		hkRefPtr<PlanesCollection> m_planes;

		/// The polygons
		hkRefPtr<hkcdPlanarGeometryPolygonCollection> m_polys;

		/// The vertices
		hkRefPtr<VertexStorage> m_vertices;						//+nosave
};

#include <Geometry/Collide/DataStructures/Planar/Geometry/hkcdPlanarGeometry.inl>

#endif	//	HKCD_PLANAR_GEOMETRY_H

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
