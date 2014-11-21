/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_HAVOK_ASSEMBLY_EXCLUDE_FILE

#ifndef HKCD_VERTEX_GEOMETRY_H
#define HKCD_VERTEX_GEOMETRY_H

#include <Geometry/Collide/DataStructures/Planar/hkcdPlanarEntity.h>
#include <Geometry/Collide/DataStructures/Planar/Geometry/hkcdPlanarGeometry.h>

/// A vertex-based representation of a polygon soup, where vertices are defined as intersections of 3 planes.
class HK_EXPORT_COMMON hkcdVertexGeometry : public hkcdPlanarEntity
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_GEOMETRY);

	public:

		/// A vertex is defined as the intersection of 3 planes.
		/// Its position approximates the intersection point, i.e. x falls within [posX, posX + 1), y falls within [posY, posY + 1), etc.
		struct Vertex
		{
			public:

				HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_GEOMETRY, hkcdVertexGeometry::Vertex);

			public:

				/// Sets the planes defining this vertex
				HK_FORCE_INLINE void setPlanesAndId(PlaneId planeIdA, PlaneId planeIdB, PlaneId planeIdC, int vertexId);

				/// Returns the vector of planes
				HK_FORCE_INLINE hkIntVector& accessPlanes()				{	return m_planes;	}
				HK_FORCE_INLINE const hkIntVector& getPlanes() const	{	return m_planes;	}

				/// Returns the position
				HK_FORCE_INLINE hkIntVector& accessPosition()			{	return m_pos;	}
				HK_FORCE_INLINE const hkIntVector& getPosition() const	{	return m_pos;	}

			protected:

				hkIntVector m_planes;	///< The plane Ids are encoded in the .x, .y, and .z components. The .w component stores the vertex Id.
				hkIntVector m_pos;		///< The vertex position, approximates the real intersection point.
		};

		/// Line Id
		HK_DECLARE_HANDLE(LineId, hkUint32, 0xFFFFFFFFU);

		/// A line is defined as the intersection of 2 planes.
		struct Line
		{
			public:

				HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_GEOMETRY, hkcdVertexGeometry::Line);

			public:

				/// Sets the planes
				HK_FORCE_INLINE void set(PlaneId planeIdA, PlaneId planeIdB, LineId lineId);

				/// Returns the planes as the .xy components of the returned vector.
				HK_FORCE_INLINE const hkIntVector& getPlanes() const	{	return m_data;	}

				/// Returns the I-th plane
				template <int I>
				HK_FORCE_INLINE PlaneId getPlaneId() const				{	return PlaneId(m_data.getComponent<I>());	}

				/// Sets the line Id
				HK_FORCE_INLINE void setId(LineId lineId);

			protected:

				hkIntVector m_data;		///< [PlaneIdA, PlaneIdB, 0, Id]
		};

		// Edge Id constants
		enum EdgeIdConstants
		{
			NUM_BITS_EDGE_ID	= 28,								///< An edge Id cannot have more than 28 bits
			FLIPPED_EDGE_BIT	= NUM_BITS_EDGE_ID,
			FLIPPED_EDGE_FLAG	= 1 << FLIPPED_EDGE_BIT,			///< An edge with opposite orientation is marked by having this flag set in its Id.
			INVALID_EDGE_ID		= (1 << NUM_BITS_EDGE_ID) - 1,		///< We'll reserve this value for invalid edge Ids
			EDGE_ID_MASK		= ~(-1 << (FLIPPED_EDGE_BIT + 1)),	///< Mask for selecting only the valid bits in an edge Id.
		};

		/// Edge Id
		HK_DECLARE_HANDLE(EdgeId, hkUint32, 0xFFFFFFFFU);

		/// An edge is defined as the line segment between two vertices.
		struct Edge
		{
			public:

				HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_GEOMETRY, hkcdVertexGeometry::Edge);

			public:

				/// Sets the edge data
				HK_FORCE_INLINE void set(int vtxA, int vtxB, LineId lineId, EdgeId edgeId);

				/// Returns the start and end vertices
				HK_FORCE_INLINE int getStartVertex() const				{	return m_data.getComponent<0>();	}
				HK_FORCE_INLINE int getEndVertex() const				{	return m_data.getComponent<1>();	}
				HK_FORCE_INLINE int getVertex(int I) const				{	return m_data.getComponent(I);		}

				/// Returns true if the edge contains the given vertex
				HK_FORCE_INLINE bool hasVertex(int vertexId) const;

				/// Gets / sets the line Id
				HK_FORCE_INLINE void setLineId(LineId lineId)			{	m_data.setComponent<2>(lineId.valueUnchecked());	}
				HK_FORCE_INLINE LineId getLineId() const				{	return LineId(m_data.getComponent<2>());			}

				/// Returns the vertices
				HK_FORCE_INLINE const hkIntVector& getVertices() const	{	return m_data;	}
				HK_FORCE_INLINE hkIntVector& accessVertices()			{	return m_data;	}

			protected:

				hkIntVector m_data;	// [Start vertex, End vertex, Line Id, Edge Id]
		};

		/// The base class for a collection of polygons
		class VPolygonCollectionBase : public hkcdPlanarGeometryPrimitives::Collection<hkcdPlanarGeometryPrimitives::FLIPPED_PLANE_BIT>
		{
			public:
					
				HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_GEOMETRY);

				/// Polygon Id
				HK_DECLARE_HANDLE(VPolygonId, hkUint32, INVALID_BLOCK_ADDR);

			public:

				/// Constructor
				VPolygonCollectionBase();

				/// Copy constructor
				VPolygonCollectionBase(const VPolygonCollectionBase& other);

				// Allocates a polygon having the given number of boundary edges
				HK_FORCE_INLINE VPolygonId alloc(hkUint32 materialId, hkUint32 userData, int numEdges);

				/// Frees the given polygon
				HK_FORCE_INLINE void free(VPolygonId polyId);
		};

		/// A polygon is a collection of boundary edges
		struct VPolygon
		{
			public:

				HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_GEOMETRY, hkcdVertexGeometry::VPolygon);
				friend class VPolygonCollectionBase;

				enum
				{
					MATERIAL_ID_OFFSET		= 0,
					USER_DATA_OFFSET		= 1,
					BOUNDARY_EDGES_OFFSET	= 2,
				};

			public:

				/// Gets / sets the material Id
				HK_FORCE_INLINE hkUint32 getMaterialId() const;
				HK_FORCE_INLINE void setMaterialId(int mtlId);

				/// Gets / sets the user data
				HK_FORCE_INLINE hkUint32 getUserData() const;
				HK_FORCE_INLINE void setUserData(hkUint32 pid);

				/// Gets / sets the i-th boundary edge Id
				HK_FORCE_INLINE EdgeId getBoundaryEdgeId(int i) const;
				HK_FORCE_INLINE void setBoundaryEdgeId(int i, EdgeId pid);

			protected:

				hkUint32 m_materialId;
				hkUint32 m_userData;
		};

		/// A collection of polygons
		struct VPolygonCollection : public VPolygonCollectionBase
		{
			HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_GEOMETRY);

			/// Retrieves the polygon at the given Id.
			HK_FORCE_INLINE const VPolygon& getPolygon(VPolygonId polyId) const;
			HK_FORCE_INLINE VPolygon& accessPolygon(VPolygonId polyId);

			/// Returns the first valid polygon Id
			HK_FORCE_INLINE VPolygonId getFirstPolygonId() const;

			/// Returns the last valid polygon Id
			HK_FORCE_INLINE VPolygonId getLastPolygonId() const;

			/// Returns the next valid polygon Id
			HK_FORCE_INLINE VPolygonId getNextPolygonId(VPolygonId polyId) const;

			/// Returns the previous valid polygon Id
			HK_FORCE_INLINE VPolygonId getPrevPolygonId(VPolygonId polyId) const;

			/// Returns the number of valid polygon Ids stored
			HK_FORCE_INLINE int getNumPolygons() const;

			/// Computes the number of boundary edges
			HK_FORCE_INLINE int getNumBoundaryEdges(VPolygonId polyId) const;
		};

		typedef VPolygonCollection::VPolygonId VPolygonId;

	public:

		/// Constructor
		hkcdVertexGeometry(PlanesCollection* planesCollection, hkcdPlanarEntityDebugger* debugger = HK_NULL);

		/// Destructor
		virtual ~hkcdVertexGeometry();

	public:

		/// Creates a vertex geometry from the given subset of polygons in the planar geometry
		static hkcdVertexGeometry* HK_CALL createFromPlanarGeometry(const hkcdPlanarGeometry* planarGeometryIn, const hkArray<PolygonId>& polygnIdsIn);

		/// Creates a vertex geometry from the given planar geometry
		static hkcdVertexGeometry* HK_CALL createFromPlanarGeometry(const hkcdPlanarGeometry* planarGeometryIn);

		/// Welds vertices having identical plane ids
		void weldIdenticalVertices();

		/// Welds all vertices
		void weldVertices();

		/// Welds lines having identical plane ids
		void weldIdenticalLines();

		/// Welds all lines
		void weldLines();

		/// Collapses all duplicate edges
		void weldIdenticalEdges();

		/// Repairs the T-junctions
		void repairTJunctions();

		/// Remaps the vertex indices using the given remap table
		void remapVertices(const hkArray<int>& remapTable);

		/// Remaps the line indices using the given remap table
		void remapLines(const hkArray<int>& remapTable);

		/// Remaps the edge indices using the given remap table
		void remapEdges(const hkArray<int>& remapTable);

		/// Returns all the polygon ids in the collection
		void getAllPolygonIds(hkArray<VPolygonId>& vPolyIdsOut);

	public:

		/// Returns the collection of planes
		HK_FORCE_INLINE const PlanesCollection* getPlanesCollection() const;
		HK_FORCE_INLINE PlanesCollection* accessPlanesCollection();

		/// Returns the vertices
		HK_FORCE_INLINE const hkArray<Vertex>& getVertices() const;
		HK_FORCE_INLINE hkArray<Vertex>& accessVertices();

		/// Returns the edge associated with the given Id
		HK_FORCE_INLINE const Edge& getEdge(EdgeId edgeId) const;
		HK_FORCE_INLINE Edge& accessEdge(EdgeId edgeId);

		/// Returns the line associated with the given Id
		HK_FORCE_INLINE const Line& getLine(LineId lineId) const;
		HK_FORCE_INLINE Line& accessLine(LineId lineId);

		/// Returns the collection of polygons
		HK_FORCE_INLINE const VPolygonCollection& getPolygons() const;
		HK_FORCE_INLINE VPolygonCollection& accessPolygons();

		/// Returns the I-th vertex of the given edge
		template <int I>
		HK_FORCE_INLINE int getEdgeVertex(EdgeId edgeId) const;

	protected:

		/// The collection of planes
		hkRefPtr<PlanesCollection> m_planes;

		/// The vertices
		hkArray<Vertex> m_vertices;

		/// The lines
		hkArray<Line> m_lines;

		/// The edges
		hkArray<Edge> m_edges;

		/// The polygons
		VPolygonCollection m_polys;
};

#include <Geometry/Collide/DataStructures/Planar/Geometry/hkcdVertexGeometry.inl>

#endif	// HKCD_VERTEX_GEOMETRY_H

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
