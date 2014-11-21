/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKX_SCENE_UTILS_H
#define HKX_SCENE_UTILS_H

#include <Common/Base/Container/StringMap/hkStringMap.h>

/// Scene utilities
class hkxSceneUtils
{
	public:
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE,hkxSceneUtils);
			/// Options taken by "hkxSceneUtils::transformScene"
		struct HK_EXPORT_COMMON SceneTransformOptions
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_SCENE_DATA, hkxSceneUtils::SceneTransformOptions );

				/// Should we apply this transformation to scene graph nodes
			hkBool m_applyToNodes;

				/// Should we apply this transformation to vertex buffers
			hkBool m_applyToBuffers;

				/// Should we apply this transformation to float channels
			hkBool m_applyToFloatChannels;

				/// Should we apply this transformation to lights
			hkBool m_applyToLights;

				/// Should we apply this transformation to cameras
			hkBool m_applyToCameras;

				/// Should we flip index buffer winding
			hkBool m_flipWinding;

				/// The transform to apply
			hkMatrix3 m_transformMatrix;
		};

			/// Given a scene and the options specified in the SceneTransformOption struct, it goes
			/// through nodes, attributes, meshes, etc., applying the specified transform to the scene.
			/// Useful for scaling scenes as well as for transforming coordinate systems
		static HK_EXPORT_COMMON void HK_CALL transformScene( class hkxScene& scene, const SceneTransformOptions& opts );

			/// Extracts environment data from an hkxScene; used mostly for backwards compatibility as previously
			/// environment information was stored in the hkxScene object. The variables extracted are:
			/// "asset" (ex: "car"),
			/// "assetPath" (ex: "c:/temp/car.max"),
			/// "assetFolder" (ex: "c:/temp/"),
			/// "modeller" (ex: "3ds max 8.0.0"),
			/// "selected" (ex: "chassis")
		static HK_EXPORT_COMMON void HK_CALL fillEnvironmentFromScene (const class hkxScene& scene, class hkxEnvironment& environment);

			/// Reorders the nodes in an hkxScene by their names. It does so alphabetically, regardless of case.
		static HK_EXPORT_COMMON void HK_CALL reorderNodesAlphabetically ( class hkxScene& scene );

			/// Checks the contents of the node, and if it's a mesh it returns it, or if it's a skin binding, it returns the mesh associated
			/// with it.
		static HK_EXPORT_COMMON class hkxMesh* HK_CALL getMeshFromNode (const class hkxNode* aNode);

			// Reverse lookup. Handy to get a name for a mesh
		static HK_EXPORT_COMMON const hkxNode* HK_CALL findFirstNodeUsingMesh(const hkxNode* rootNode, const class hkxMesh* aMesh);

			/// finds the first mesh in the scene
		static HK_EXPORT_COMMON hkxNode* HK_CALL findFirstMeshNode(hkxScene* scene);

		struct HK_EXPORT_COMMON GraphicsNode
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE,hkxSceneUtils::GraphicsNode);
			hkxNode* m_node;
			const char* m_name;
		};

			/// finds all nodes under node, which have a mesh attached, which is probably visible in the Havok demos.
			/// Also if the mesh name can be found in extraNodesToFind, the node will be returned.
		static HK_EXPORT_COMMON void HK_CALL findAllGraphicsNodes(bool collectShapes, bool ignorePShapes, const hkStringMap<int>& extraNodesToFind, hkxNode* node, hkArray<GraphicsNode>& nodesOut);

			/// finds all nodes under node
		static HK_EXPORT_COMMON void HK_CALL findAllNodes(hkxNode* node, hkArray< hkRefPtr<hkxNode> >& nodes );

			/// Finds all nodes under node, which have a mesh attached and optionally compute its corresponding worldFromLocal transform.
			/// This function gets called recursively and hence for the root we need to pass in the identity for the rootTransform.
		static HK_EXPORT_COMMON void HK_CALL findAllMeshNodes(	hkxScene* scene, 
												hkxNode* node, 
												hkArray< hkRefPtr<hkxNode> >& nodes, 
												hkMatrix4* rootTransform = HK_NULL,
												hkArray<hkMatrix4>* worldFromLocalTransforms = HK_NULL);

			// Helper function used by the createskin filter which allows for *translations* as well as rotations
		static HK_EXPORT_COMMON void HK_CALL transformVertexBuffer( const hkTransform& tr, class hkxVertexBuffer& vbuffer);

		/// Merges the source scene into the destination scene
		static HK_EXPORT_COMMON void HK_CALL mergeScenes(hkxScene* dstScene, hkxScene* srcScene);

		/// Removes all unused skin bindings
		static HK_EXPORT_COMMON void HK_CALL removeUnusedSkinBindings(hkxScene* scene);

		/// Removes all unused meshes
		static HK_EXPORT_COMMON void HK_CALL removeUnusedMeshes(hkxScene* scene);

		/// Removes all duplicate materials
		static HK_EXPORT_COMMON void HK_CALL removeDuplicateMaterials(hkxScene* scene);

		/// Removes all unused materials
		static HK_EXPORT_COMMON void HK_CALL removeUnusedMaterials(hkxScene* scene);

		/// Removes all duplicate textures
		static HK_EXPORT_COMMON void HK_CALL removeDuplicateTextures(hkxScene* scene);

		/// Removes all unused textures
		static HK_EXPORT_COMMON void HK_CALL removeUnusedTextures(hkxScene* scene);

		// Flips the winding of the triangles in the index buffer.
		static HK_EXPORT_COMMON void HK_CALL flipWinding( class hkxIndexBuffer &ibuffer );

	public:

			// Contains useful information about the transform
		struct HK_EXPORT_COMMON TransformInfo
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_SCENE_DATA, hkxSceneUtils::TransformInfo );

				// The transform as a Matrix4
			hkMatrix3 m_transform;

				// The inverse of the transform
			hkMatrix3 m_inverse;

				// The inverse of the transform, transposed
			hkMatrix3 m_inverseTranspose;

				// The transform decomposed
			hkMatrixDecomposition::Decomposition m_decomposition;
		};

	private:

			// Transforms a node and its children. It also transform node attributes
		static HK_EXPORT_COMMON void HK_CALL transformNode( const TransformInfo& transformInfo, class hkxNode& node);

		static HK_EXPORT_COMMON void HK_CALL transformSkinBinding( const TransformInfo& transformInfo, class hkxSkinBinding& skinBinding);

		static HK_EXPORT_COMMON void HK_CALL transformVertexBuffer( const TransformInfo& transformInfo, class hkxVertexBuffer& vbuffer);

		static HK_EXPORT_COMMON void HK_CALL transformFloatChannel( const TransformInfo& transformInfo, class hkxVertexFloatDataChannel& floatChannel);

		static HK_EXPORT_COMMON void HK_CALL transformLight( const TransformInfo& transformInfo, class hkxLight& light);

		static HK_EXPORT_COMMON void HK_CALL transformCamera( const TransformInfo& transformInfo, class hkxCamera& camera);

		static HK_EXPORT_COMMON void HK_CALL transformSpline( const TransformInfo& transformInfo, class hkxSpline& spline);

			// Called by transformNode
		static HK_EXPORT_COMMON void HK_CALL transformAttributeGroup ( const TransformInfo& transformInfo, struct hkxAttributeGroup& attributeGroup);

			// Called by transformAttributeGroup
		static HK_EXPORT_COMMON void HK_CALL transformAnimatedFloat (const TransformInfo& transformInfo, class hkxAnimatedFloat& animatedFloat);
		static HK_EXPORT_COMMON void HK_CALL transformAnimatedQuaternion (const TransformInfo& transformInfo, class hkxAnimatedQuaternion& animatedQuaternion);
		static HK_EXPORT_COMMON void HK_CALL transformAnimatedMatrix (const TransformInfo& transformInfo, class hkxAnimatedMatrix& animatedMatrix);
		static HK_EXPORT_COMMON void HK_CALL transformAnimatedVector (const TransformInfo& transformInfo, class hkxAnimatedVector& animatedVector);

			// Transforms a fullMatrix4, reused in different places
		static HK_EXPORT_COMMON void HK_CALL transformMatrix4 (const TransformInfo& transformInfo, hkMatrix4& matrix4);

};

#endif // HK_SCENE_UTILS_H

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
