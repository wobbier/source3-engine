/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE
#ifndef	HKCD_TYPES_RAY
#define HKCD_TYPES_RAY

#include <Common/Base/hkBase.h>
#include <Common/Base/Types/hkHandle.h>

#if defined(HK_REAL_IS_DOUBLE)
#	define HK_ACC_RAYCAST HK_ACC_FULL
#else
#	define HK_ACC_RAYCAST HK_ACC_MID
#endif


/// Represents the origin, direction and length of a ray.
/// Additionally, a fraction (default 1.0f) is stored in the direction W component.
/// Note that m_origin:W is free for user data.
struct HK_EXPORT_COMMON hkcdRay
{
	/// Set from start and end points.
	HK_FORCE_INLINE	void setEndPoints(
		hkVector4Parameter start, hkVector4Parameter end,
		hkSimdRealParameter fraction = hkSimdReal::getConstant(HK_QUADREAL_1) );

	/// Set from origin and direction.
	HK_FORCE_INLINE	void setOriginDirection(
		hkVector4Parameter origin, hkVector4Parameter direction,
		hkSimdRealParameter fraction = hkSimdReal::getConstant(HK_QUADREAL_1) );

	/// Computes the ray end point.
	HK_FORCE_INLINE void getEndPoint( hkVector4& vEndPoint ) const;

	/// Get direction.
	HK_FORCE_INLINE const hkVector4& getDirection() const { return m_direction; }

	/// Get inverse direction.
	HK_FORCE_INLINE const hkVector4& getInverseDirection() const { return m_invDirection; }

	/// Get fraction.
	HK_FORCE_INLINE hkSimdReal getFraction() const { return m_direction.getComponent<3>(); }

	/// Set fraction.
	HK_FORCE_INLINE void setFraction( hkSimdRealParameter fraction ) { m_direction.setComponent<3>(fraction); }


	/// Origin of the ray.
	hkVector4 m_origin;

	/// Direction of the ray. Effectively the (endPoint - startPoint) vector (and length as |direction|).
	hkVector4 m_direction;

	/// Precomputed direction reciprocal with +/-Inf == 0.
	/// In addition, the mask of the following comparison is stored in the W component via setInt24W: m_direction >= [0,0,0].
	hkVector4 m_invDirection;
};


/// A set of flags used to customize ray casting behavior.
struct HK_EXPORT_COMMON hkcdRayQueryFlags
{
	enum Enum
	{
		/// No flags. Implies default behavior:
		///  - Triangles are treated as two sided.
		///  - No inside hits are reported.
		NO_FLAGS = 0,

		/// If set: In triangle based shapes (e.g: mesh, height field), rays will not hit triangle back faces.
		/// Back faces are considered to be those with clockwise vertex winding.
		DISABLE_BACK_FACING_TRIANGLE_HITS	= 1 << 0,

		/// If set: In triangle based shapes (e.g: mesh, height field), rays will not hit triangle front faces.
		/// Front faces are considered to be those with counter-clockwise vertex winding.
		DISABLE_FRONT_FACING_TRIANGLE_HITS	= 1 << 1,

		/// Rays starting inside convex shapes will by default not hit the shape,
		/// this flag can enable these 'inside' hits.
		/// The normal returned for inside hits will be outward facing and
		/// hkcdRayCastResult::BACK_FACE_HIT | hkcdRayCastResult::INSIDE_HIT returned.
		/// Note: For shapes created using hknpConvexShape::createFromVertices(), this flag only works when
		/// hknpConvexShape::BuildConfig.m_buildFaces is set to true.
		ENABLE_INSIDE_HITS = 1 << 2,

		/// When we cast a ray against a triangle, the triangle edges might be expanded by
		/// hkcdRayCastTriangle::s_tolerance + 'dynamic tolerance' to compensate for numerical inaccuracies.
		/// However if a triangle corner gets very sharp (as seen from the ray origin), the ray might hit the triangle
		/// outside the triangle.
		/// If you set this flag, the ray-triangle intersection will check for sharp triangle corners and insert
		/// optional bevel edges. This flag is off by default.
		/// Example: If you have a mesh made of 0.5-1.0 meter sized triangles and the ray length is shorter than 1km,
		/// you really don't need this flag, even with a ray length of 10km the artifacts should be minimal.
		/// With a ray length of 100km small artifacts become visible without the flag, so turning it on is advised.
		ENABLE_EXTRA_TRIANGLE_BEVELPLANES = 1 << 3,
	};

	/// Sets out to true if a given flag is set.
	static HK_FORCE_INLINE void isFlagSet( hkFlags<Enum,hkUint32> flags, Enum flag, hkVector4Comparison& out );
};


/// The result of a raycast (synchronized with hkcdRayQueryFlags).
struct HK_EXPORT_COMMON hkcdRayCastResult
{
	enum Enum
	{
		/// No hit.
		NO_HIT = 0,

		/// Back face hit.
		/// In this case the shape normal points towards the ray origin.
		BACK_FACE_HIT	= 1 << 0,

		/// Front face/outside hit.
		/// In this case the normal points towards the ray origin.
		FRONT_FACE_HIT	= 1 << 1,

		/// A convex shape is hit from the inside.
		/// In this case the normal points *away* from the ray origin.
		INSIDE_HIT		= 1 << 2
	};

	// Constructors
	HK_FORCE_INLINE hkcdRayCastResult() {}
	HK_FORCE_INLINE hkcdRayCastResult(Enum e) { m_value = (hkUint32)e; }
	explicit HK_FORCE_INLINE hkcdRayCastResult(int i) { m_value = (hkUint32)i; }

	// Queries
	HK_FORCE_INLINE hkBool32 isHit() const			{ return m_value; }
	HK_FORCE_INLINE hkBool32 isInsideHit() const	{ return m_value & INSIDE_HIT; }
	HK_FORCE_INLINE hkBool32 isOutsideHit() const	{ return INSIDE_HIT ^ (m_value & INSIDE_HIT); }
	HK_FORCE_INLINE hkBool32 isFrontSideHit() const	{ return m_value & FRONT_FACE_HIT; }
	HK_FORCE_INLINE hkBool32 isBackSideHit() const	{ return m_value & BACK_FACE_HIT; }

	HK_FORCE_INLINE hkBool32 operator ==(const hkcdRayCastResult other) const { return m_value == other.m_value; }
	HK_FORCE_INLINE hkBool32 operator !=(const hkcdRayCastResult other) const { return m_value != other.m_value; }

	HK_FORCE_INLINE hkBool32 operator ==(const hkcdRayCastResult::Enum other) const { return m_value == (hkUint32)other; }
	HK_FORCE_INLINE hkBool32 operator !=(const hkcdRayCastResult::Enum other) const { return m_value != (hkUint32)other; }

	hkUint32 m_value;
};

HK_FORCE_INLINE hkBool32 operator ==(const hkcdRayCastResult::Enum lhs, const hkcdRayCastResult rhs) { return rhs.m_value == (hkUint32)lhs; }
HK_FORCE_INLINE hkBool32 operator !=(const hkcdRayCastResult::Enum lhs, const hkcdRayCastResult rhs) { return rhs.m_value != (hkUint32)lhs; }

HK_FORCE_INLINE hkOstream& operator<<(hkOstream& stream, const hkcdRayCastResult result);


#include <Geometry/Internal/Types/hkcdRay.inl>

#endif // HKCD_TYPES_RAY

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
