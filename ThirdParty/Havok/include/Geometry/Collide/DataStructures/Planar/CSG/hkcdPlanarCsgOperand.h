/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_HAVOK_ASSEMBLY_EXCLUDE_FILE

#ifndef HKCD_PLANAR_CSG_OPERAND_H
#define HKCD_PLANAR_CSG_OPERAND_H

#include <Geometry/Collide/DataStructures/Planar/ConvexCellsTree/hkcdConvexCellsTree3D.h>
#include <Geometry/Collide/DataStructures/Planar/Memory/hkcdPlanarGeometryPrimitivesCollectionManager.h>

/// CSG Operand
class HK_EXPORT_COMMON hkcdPlanarCsgOperand : public hkReferencedObject
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_GEOMETRY);
		HK_DECLARE_REFLECTION();

		// Types
		typedef hkcdPlanarGeometryPlanesCollection	PlanesCollection;
		typedef hkcdPlanarGeometryPrimitives::CollectionManager<hkcdPlanarGeometryPolygonCollection>	PolyCollManager;
		typedef hkcdPlanarGeometryPrimitives::CollectionManager<hkcdConvexCellsCollection>				CellCollManager;
		typedef hkcdPlanarGeometryPrimitives::CollectionManager<hkcdPlanarSolid::ArrayMgr>				ArrayCollManager;

		/// Holder for geometry source
		struct GeomSource
		{
			public:

				HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_GEOMETRY, hkcdPlanarCsgOperand::GeomSource);
				HK_DECLARE_REFLECTION();

			public:

				/// Constructor
				GeomSource();

				/// Constructor
				GeomSource(const hkcdPlanarCsgOperand& operand, const int nbMatIds);

				/// Serialization constructor
				GeomSource(class hkFinishLoadedObjectFlag flag);

				/// Destructor
				~GeomSource();

			public:

				hkRefPtr<hkcdPlanarGeometry> m_geometry;	///< Source geometry
				hkInt32 m_materialOffset;					///< Offset for material remapping
				hkInt32 m_numMaterialIds;					///< For material remapping
				hkBool32 m_flipPolygons;					///< True if the flipped version of the geometry should be used
		};

	public:

		/// Constructor
		hkcdPlanarCsgOperand();

		/// Serialization constructor
		hkcdPlanarCsgOperand(class hkFinishLoadedObjectFlag flag);

		/// Destructor
		virtual ~hkcdPlanarCsgOperand();

	public:

		/// Returns the convex cell tree corresponding to this solid planar geom. Build it if necessary.
		hkcdConvexCellsTree3D* getOrCreateConvexCellTree(bool withConnectivity = false, bool rebuildIfConnectivityDoesntMatch = true);

		/// Retrieves the planes collection
		HK_FORCE_INLINE PlanesCollection* accessPlanesCollection();
		const PlanesCollection* getPlanesCollection() const;

		/// Sets a new planes collection. If the plane remapping table is non-null, the plane Ids on all nodes will be re-set as well (i.e. to match the plane Ids in the new collection)
		void setPlanesCollection(const PlanesCollection* newPlanes, const int* HK_RESTRICT planeRemapTable);

		/// Shift all plane ids of the operand elements
		void shiftPlaneIds(int offsetValue);

		/// Simplifies this operand by rebuilding the solid BSP tree from its boundaries
		void simplifyFromBoundaries();

		/// Build the planar geometry from its geometry sources
		void buildGeometryFromGeomSources(bool useStandardClassify, bool intersectCoplanarPolygons);

		/// Fast version of buildGeometryFromGeomSources when only 2 geometry sources are present
		void buildGeometryFrom2GeomSources(PolyCollManager* polysCollManager, ArrayCollManager* arraysCollManager, hkcdPlanarSolid* cutoutSolid, int numMat);

		/// Builds dangling geometry form input operand and bool operation
		void buildDanglingGeometry(bool split, bool negPart, hkcdPlanarSolid* cutoutSolid);

		/// Builds the geometry as the union of the solid geom plus dangling geom
		void buildFinalGeometry(hkRefPtr<hkcdPlanarGeometry>& geomOut);

		/// Create a unique temporary instance of the ith geom source matching the operand planes collection
		void createGeometryFromGeometrySource(int geomSourceId, hkcdPlanarGeometry* geomDest, hkUint32 maxPlaneIdValue, hkArray<hkcdConvexCellsTree3D::PolygonId>& polyIds, hkArray<int>& remapTable);

		/// Removes all planes not used by the entities
		void removeUnusedPlanes();

		/// Copy the desired data from another operand
		void copyData(const hkcdPlanarCsgOperand& operandSrc, bool copySolid, bool copyRegions, bool copyGeometry = false, bool copySources = false);

		/// Copy the desired data from another operand, using provided collection managers
		void copyData(	const hkcdPlanarCsgOperand& operandSrc, hkcdPlanarGeometryPlanesCollection* dstPlaneCollection,
						PolyCollManager* polysCollManager, CellCollManager* cellsCollManager, bool copyRegions = true, bool copyGeometry = false, bool copySources = false);

		/// Create an operand with the same data, but a duplicated plane collection
		static void HK_CALL createOperandWithSharedDataAndClonedPlanes(const hkcdPlanarCsgOperand* operandSrc, hkRefPtr<hkcdPlanarCsgOperand>& operandDst);

	protected:

		/// Collects a bit-field of plane Ids used by the operand
		void collectUsedPlaneIds(hkBitField& usedPlaneIdsOut) const;

	public:

		/// Gets / sets the geometry
		HK_FORCE_INLINE const hkcdPlanarGeometry* getGeometry() const;
		HK_FORCE_INLINE hkcdPlanarGeometry* accessGeometry();
		HK_FORCE_INLINE void setGeometry(hkcdPlanarGeometry* geom);

		/// Gets / sets the dangling geometry
		HK_FORCE_INLINE const hkcdPlanarGeometry* getDanglingGeometry() const;
		HK_FORCE_INLINE hkcdPlanarGeometry* accessDanglingGeometry();
		HK_FORCE_INLINE void setDanglingGeometry(hkcdPlanarGeometry* geom);

		/// Gets / sets the solid
		HK_FORCE_INLINE const hkcdPlanarSolid* getSolid() const;
		HK_FORCE_INLINE hkcdPlanarSolid* accessSolid();
		HK_FORCE_INLINE void setSolid(hkcdPlanarSolid* solid);

		/// Gets / sets the regions
		HK_FORCE_INLINE const hkcdConvexCellsTree3D* getRegions() const;
		HK_FORCE_INLINE hkcdConvexCellsTree3D* accessRegions();
		HK_FORCE_INLINE void setRegions(hkcdConvexCellsTree3D* regions);

		/// Gets / sets the geometry sources
		GeomSource* addGeometrySource(const GeomSource& geomSource);
		HK_FORCE_INLINE void appendGeometrySources(const hkArray<GeomSource>& geomSources, bool flipGeoms);
		HK_FORCE_INLINE const hkArray<GeomSource>& getGeometrySources() const;
		HK_FORCE_INLINE hkArray<GeomSource>& accessGeometrySources();
		HK_FORCE_INLINE void removeGeometrySources();

	protected:

		/// Geometry associated with the fracture piece (The geometry can be entirely deduced from the sources, having the to data at the same time is redundant)
		hkRefPtr<hkcdPlanarGeometry> m_geometry;

		/// "Dangling" part of the geometry
		hkRefPtr<hkcdPlanarGeometry> m_danglingGeometry;

		/// Solid boundary representation of the fracture piece
		hkRefPtr<hkcdPlanarSolid> m_solid;

		/// List of geometry sources
		hkArray<GeomSource> m_geomSources;

		/// A tree of convex regions matching the solid
		hkRefPtr<hkcdConvexCellsTree3D> m_regions;				//+nosave
};

#include <Geometry/Collide/DataStructures/Planar/CSG/hkcdPlanarCsgOperand.inl>

#endif	// HKCD_PLANAR_CSG_OPERAND_H

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
