/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#define INV_2_POW_24		0.000000059604644775390625f
#define TOL_DET_3_WYZ		19.0f
#define TOL_DET_3_XWZ		19.0f
#define TOL_DET_3_XYW		19.0f
#define TOL_DET_3_XYZ		(TOL_DET_3_XYW * INV_2_POW_24)
#define TOL_DET_4			1.0e-7f	/*97.0f*/
#define FAST_PREDICATE_LOG_TOLERANCE	(2)
#define TOL_FAST_PREDICATE	(1 << FAST_PREDICATE_LOG_TOLERANCE)

//
//	Debug flags

#define HKND_ENABLE_DEBUG_ORIENTATION_CACHE_INCONSISTENCIES		(0)
#define HKND_ENABLE_DEBUG_FAST_PREDICATE_CHECK					(0)

//
//	Returns true if the given planes are coplanar (i.e. coincident)
//	Must compute all 2x2 determinants of:
//		| ax ay az aw |
//		| bx by bz bw |

inline hkcdPlanarGeometryPredicates::Coplanarity HK_CALL hkcdPlanarGeometryPredicates::coplanar(PlaneParam planeA, PlaneParam planeB)
{
	// All planes are fully simplified, so any two coplanar planes must match identically
	hkVector4d dEqnA;	dEqnA.setAbs(planeA.getApproxEquation());
	hkVector4d dEqnB;	dEqnB.setAbs(planeB.getApproxEquation());

	if ( dEqnA.equal(dEqnB).allAreSet() )
	{	
		// We can't be sure, check with exact arithmetic!
		// Check if the two planes are identical
		if ( planeA.isEqual(planeB) )
		{
			return COINCIDENT;
		} 

		// Check if the flipped plane is equal, in which case the two plane are still coplanar
		Plane flippedA; flippedA.setOpposite(planeA);
		if ( flippedA.isEqual(planeB) )
		{
			return OPPOSITE;
		}
	}

	// Approx normals are not equal
	return NOT_COPLANAR;
}

//
//	Tests for same orientation. Should be preceded by a coincident test

HK_FORCE_INLINE int HK_CALL hkcdPlanarGeometryPredicates::sameOrientation(PlaneParam planeA, PlaneParam planeB)
{
	const hkVector4d& dNrmA		= planeA.getApproxEquation();
	const hkVector4d& dNrmB		= planeB.getApproxEquation();
	hkSimdInt<128> iOffsetA;	planeA.getExactOffset(iOffsetA);
	hkSimdInt<128> iOffsetB;	planeB.getExactOffset(iOffsetB);

	hkVector4dComparison pA;	pA.setSelect<hkVector4ComparisonMask::MASK_XYZ>(dNrmA.lessZero(),	iOffsetA.lessZero<hkVector4dComparison>());	// [ax < 0, ay < 0, az < 0, aw < 0]
	hkVector4dComparison nA;	nA.setSelect<hkVector4ComparisonMask::MASK_XYZ>(dNrmA.equalZero(),	iOffsetA.equalZero<hkVector4dComparison>());// [ax == 0, ay == 0, az == 0, aw == 0]
								nA.setOr(nA, pA);												// [ax <= 0, ay <= 0, az <= 0, aw <= 0]
								pA.setNot(pA);													// [ax >= 0, ay >= 0, az >= 0, aw >= 0]

	hkVector4dComparison pB;	pB.setSelect<hkVector4ComparisonMask::MASK_XYZ>(dNrmB.lessZero(),	iOffsetB.lessZero<hkVector4dComparison>());	// [bx < 0, by < 0, bz < 0, bw < 0]
	hkVector4dComparison nB;	nB.setSelect<hkVector4ComparisonMask::MASK_XYZ>(dNrmB.equalZero(),	iOffsetB.equalZero<hkVector4dComparison>());// [bx == 0, by == 0, bz == 0, bw == 0]
								nB.setOr(nB, pB);												// [bx <= 0, by <= 0, bz <= 0, bw <= 0]
								pB.setNot(pB);													// [bx >= 0, by >= 0, bz >= 0, bw >= 0]
	
	hkVector4dComparison nAB;	nAB.setAnd(nA, nB);		// [ax, bx <= 0, ay, by <= 0, az, bz <= 0, aw, bw <= 0]
	hkVector4dComparison pAB;	pAB.setAnd(pA, pB);		// [ax, bx >= 0, ay, by >= 0, az, bz >= 0, aw, bw >= 0]
								pAB.setOr(nAB, pAB);	// [axbx >= 0, ayby >= 0, azbz >= 0, awbw >= 0]
	return pAB.allAreSet();
}

//
//	Computes the orientation of the point v with respect to the plane p

HK_FORCE_INLINE hkcdPlanarGeometryPredicates::Orientation HK_CALL hkcdPlanarGeometryPredicates::orientation(hkIntVectorParameter v, PlaneParam p)
{
	hkInt64Vector4 iN;	p.getExactNormal(iN);
	hkSimdInt<128> iO;	p.getExactOffset(iO);
	iO.setAdd(iO, iN.dot<3>(v));

	const hkVector4fComparison cmpLt = iO.lessZero();
	const hkVector4fComparison cmpEq = iO.equalZero();
	return cmpLt.anyIsSet() ? BEHIND : (cmpEq.anyIsSet() ? ON_PLANE : IN_FRONT_OF);
}

//
//	Approximates the intersection (i.e. in fixed coordinates) of the 3 given planes

inline void HK_CALL hkcdPlanarGeometryPredicates::approximateIntersection(const Plane (&planes)[3], hkIntVector& intersectionOut)
{
	hkSimdInt<256> detX, detY, detZ, detW;
	computeIntersectionDeterminants(planes, &detX, &detY, &detZ, &detW);

	// Divide by DW to get the points
	const int px = hkSimdInt<256>::computeDiv32(detX, detW);
	const int py = hkSimdInt<256>::computeDiv32(detY, detW);
	const int pz = hkSimdInt<256>::computeDiv32(detZ, detW);

	intersectionOut.set(px, py, pz, pz);
}

//
//	Approximates the intersection (in floating point precision) of the 3 given planes. Faster but less accurate then the floating point version

inline void HK_CALL hkcdPlanarGeometryPredicates::approximateIntersectionFast(const Plane (&planes)[3], hkVector4d& intersectionOut)
{
	typedef hkcdMathErrorBoundsCalculator::Vector	Vec;
	typedef hkcdMathErrorBoundsCalculator::Scalar	Num;

	ApproxVertex dets;
	computeIntersectionDeterminants(planes[0].getApproxEquation(), planes[1].getApproxEquation(), planes[2].getApproxEquation(), dets);

	// Divide by DW to get the points
	Num dx;	dets.getComponent<0>(dx);
	Num dy;	dets.getComponent<1>(dy);
	Num dz;	dets.getComponent<2>(dz);
	Num dw;	dets.getComponent<3>(dw);
	dx.setDiv(dx, dw);
	dy.setDiv(dy, dw);
	dz.setDiv(dz, dw);

	// Check precision. If too imprecise, fall back to the fixed-point implementation
	hkVector4d err;	err.set(dx.m_err, dy.m_err, dz.m_err, dz.m_err);
	hkVector4d tol;	tol.setAll(1.0f);
	if ( err.less(tol).anyIsSet() )
	{
		intersectionOut.set(dx.m_val, dy.m_val, dz.m_val, dz.m_val);
	}
	else
	{
		hkIntVector iI;
		approximateIntersection(planes, iI);
		intersectionOut.set((hkDouble64)iI.getComponent<0>(), (hkDouble64)iI.getComponent<1>(), (hkDouble64)iI.getComponent<2>(), (hkDouble64)iI.getComponent<3>());
	}
}

inline void HK_CALL hkcdPlanarGeometryPredicates::computeIntersectionDeterminants(hkVector4dParameter planeEqnA, hkVector4dParameter planeEqnB, hkVector4dParameter planeEqnC, ApproxVertex& determinantsOut)
{
	typedef hkcdMathErrorBoundsCalculator::Vector	Vec;
	typedef hkcdMathErrorBoundsCalculator::Scalar	Num;

	Vec eqnA;	eqnA.set(planeEqnA);
	Vec eqnB;	eqnB.set(planeEqnB);
	Vec eqnC;	eqnC.set(planeEqnC);

	// Compute components
	Vec xA, xB, temp;
	{
		xA.setPermutation<hkVectorPermutation::WYZX>(eqnA);		// [aw, ay, az]
		xB.setPermutation<hkVectorPermutation::WYZX>(eqnB);		// [bw, by, bz]
		temp.setPermutation<hkVectorPermutation::WYZX>(eqnC);	// [cw, cy, cz]
		xB.setCross(xB, temp);
	}
	Vec yA, yB;
	{
		yA.setPermutation<hkVectorPermutation::XWZY>(eqnA);		// [ax, aw, az]
		yB.setPermutation<hkVectorPermutation::XWZY>(eqnB);		// [ay, bw, bz]
		temp.setPermutation<hkVectorPermutation::XWZY>(eqnC);	// [az, cw, cz]
		yB.setCross(yB, temp);
	}
	Vec zA, zB;	
	{
		zA.setPermutation<hkVectorPermutation::XYWZ>(eqnA);		// [ax, ay, aw]
		zB.setPermutation<hkVectorPermutation::XYWZ>(eqnB);		// [ay, by, bw]
		temp.setPermutation<hkVectorPermutation::XYWZ>(eqnC);	// [az, cy, cw]
		zB.setCross(zB, temp);
	}

	temp.setCross(eqnB, eqnC);

	{
		Num dx;	Vec::dot<3>(xA, xB, dx);
		Num dy;	Vec::dot<3>(yA, yB, dy);
		Num dz;	Vec::dot<3>(zA, zB, dz);
		Num dw;	Vec::dot<3>(eqnA, temp, dw);
	
		temp.set(dx, dy, dz, dw);
	}

	hkVector4dComparison maskXYZ;	maskXYZ.set<hkVector4ComparisonMask::MASK_XYZ>();
	determinantsOut.setFlipSign(temp, maskXYZ);
}

HK_FORCE_INLINE int HK_CALL hkcdPlanarGeometryPredicates::mulSigns(hkVector4dComparisonParameter negA, hkVector4dComparisonParameter zeroA, hkVector4dComparisonParameter negB, hkVector4dComparisonParameter zeroB)
{
	hkVector4dComparison posA;			posA.setOr(negA, zeroA);				// (a <= 0)
	hkVector4dComparison posB;			posB.setOr(negB, zeroB);				// (b <= 0)

	hkVector4dComparison negA_posB;		negA_posB.setAndNot(negA, posB);		// (a < 0) && (b > 0)
	hkVector4dComparison posA_negB;		posA_negB.setAndNot(negB, posA);		// (a > 0) && (b < 0)
	hkVector4dComparison negAB;			negAB.setOr(negA_posB, posA_negB);		// (ab < 0)
	hkVector4dComparison zeroAB;		zeroAB.setOr(zeroA, zeroB);				// (ab == 0)			

	return negAB.anyIsSet() ? -1 : (zeroAB.anyIsSet() ? 0 : 1);
}

//
//	Computes the orientation of the point (ptPlaneA, ptPlaneB, ptPlaneC) with respect to the planeD

HK_FORCE_INLINE hkcdPlanarGeometryPredicates::Orientation HK_CALL hkcdPlanarGeometryPredicates::approximateOrientation(PlaneParam ptPlaneA, PlaneParam ptPlaneB, PlaneParam ptPlaneC, PlaneParam planeD)
{
	HK_ON_DEBUG(m_numApproxCalls++);

	const hkVector4d fEqnA	= ptPlaneA.getApproxEquation();
	const hkVector4d fEqnB	= ptPlaneB.getApproxEquation();
	const hkVector4d fEqnC	= ptPlaneC.getApproxEquation();
	const hkVector4d fEqnD	= planeD.getApproxEquation();

	hkVector4d nAB;		nAB.setCross(fEqnA, fEqnB);
	hkVector4d nBC;		nBC.setCross(fEqnB, fEqnC);
	hkVector4d nCD;		nCD.setCross(fEqnC, fEqnD);
	hkVector4d nA;		nA.setMul(fEqnB.getComponent<3>(),	fEqnA);
						nA.subMul(fEqnA.getComponent<3>(),	fEqnB);
	hkVector4d nC;		nC.setMul(fEqnD.getComponent<3>(),	fEqnC);
						nC.subMul(fEqnC.getComponent<3>(),	fEqnD);


	const hkSimdDouble64 detLeft	= nAB.dot<3>(nC);
	const hkSimdDouble64 detRight	= nCD.dot<3>(nA);
	const hkSimdDouble64 det3		= nBC.dot<3>(fEqnA);
	hkSimdDouble64 det4;			det4.setAdd(detLeft, detRight);

	// Check signs, return proper orientation
	{
		const int sign = mulSigns(det3.lessZero(), det3.equalZero(), det4.lessZero(), det4.equalZero());
		return (sign < 0) ? BEHIND : ((sign > 0) ? IN_FRONT_OF : ON_PLANE);
	}
}

//
//	Computes the orientation of the point (ptPlaneA, ptPlaneB, ptPlaneC) with respect to the planeD

HK_FORCE_INLINE hkcdPlanarGeometryPredicates::Orientation HK_CALL hkcdPlanarGeometryPredicates::approximateOrientation(hkVector4dParameter p, PlaneParam plane)
{
	const hkVector4d& planeEqn		= plane.getApproxEquation();
	hkVector4d pc;					pc.setXYZ_W(p, hkSimdDouble64_1);
	const hkSimdDouble64 dotRes		= pc.dot<4>(planeEqn);
	hkSimdDouble64 absDotRes;		absDotRes.setAbs(dotRes);
	return ( dotRes.isLessZero() ) ? BEHIND : (( dotRes.isEqualZero() ) ? ON_PLANE : IN_FRONT_OF);
}

//
//	Computes the Det3

HK_FORCE_INLINE hkBool32 hkcdPlanarGeometryPredicates::computeApproxDet3(const Plane& planeA, const Plane& planeB, const Plane& planeC, hkVector4dComparison& det3LessZero, hkVector4dComparison& det3EqualZero)
{
	hkVector4d nBC;				nBC.setCross(planeB.getApproxEquation(), planeC.getApproxEquation());
	const hkSimdDouble64 det3	= nBC.dot<3>(planeA.getApproxEquation());
	hkSimdDouble64 absDet3;		absDet3.setAbs(det3);

	// Set output
	det3LessZero	= det3.lessZero();
	det3EqualZero	.set<hkVector4ComparisonMask::MASK_NONE>();	// Always false, as we switch to fixed precision if too close to zero!
	HK_ON_DEBUG(m_numApproxCalls++);
	HK_ON_DEBUG(m_numApproxDet3++);

	// As all normal components are <= 1, with a maximum error of e < 1/2^24,
	// the maximum error in computing the determinant is less than 16 * eps, where eps = 1/2^24
	// Error after cross product is: e (by + bz + cy + cz + 2 e) < e (4 + 2e) = 4e + 2e^2
	// Error after the whole dot3 is: e (4az + bcx + bcy + bcz + 12e + 2az e + 6 e^2 + 2 ax (2 + e) + 2 ay (2 + e)) < 19e

	// Return SUCCESS if the determinant is above the error threshold!
	return absDet3.isGreaterEqual(hkSimdDouble64::fromFloat(TOL_DET_3_XYZ));
}

HK_FORCE_INLINE void hkcdPlanarGeometryPredicates::computeExactDet3(const Plane& planeA, const Plane& planeB, const Plane& planeC, hkVector4dComparison& det3LessZero, hkVector4dComparison& det3EqualZero)
{
	hkInt64Vector4 iNrmA;	planeA.getExactNormal(iNrmA);
	hkInt64Vector4 iNrmB;	planeB.getExactNormal(iNrmB);
	hkInt64Vector4 iNrmC;	planeC.getExactNormal(iNrmC);

	hkInt128Vector4 nBC;	nBC.setCross(iNrmB, iNrmC);
	hkSimdInt<256> det3		= nBC.dot<3>(iNrmA);
	det3LessZero.set(det3.lessZero().getMask());
	det3EqualZero.set(det3.equalZero().getMask());
	HK_ON_DEBUG(m_numExactDet3++);
}

//
//	Computes the Det4
//	Let:
//	L_ij	=	| ai aj |,	H_ij =	| ci cj |
//				| bi bj |			| di dj |
//	The 2nd determinant is: (L12 * H_03 - L_02 * H_13 + L_01 * H_23) + (L_03 * H_12 - L_13 * H_02  + L_23 * H_01)

HK_FORCE_INLINE hkBool32 hkcdPlanarGeometryPredicates::computeApproxDet4(const Plane& planeA, const Plane& planeB, const Plane& planeC, const Plane& planeD, hkVector4dComparison& det4LessZero, hkVector4dComparison& det4EqualZero)
{
	const hkVector4d fEqnA	= planeA.getApproxEquation();
	const hkVector4d fEqnB	= planeB.getApproxEquation();
	const hkVector4d fEqnC	= planeC.getApproxEquation();
	const hkVector4d fEqnD	= planeD.getApproxEquation();

	hkVector4d nAB;		nAB.setCross(fEqnA, fEqnB);
	hkVector4d nCD;		nCD.setCross(fEqnC, fEqnD);
	hkVector4d nA;		nA.setMul(fEqnB.getComponent<3>(),	fEqnA);
	nA.subMul(fEqnA.getComponent<3>(),	fEqnB);
	hkVector4d nC;		nC.setMul(fEqnD.getComponent<3>(),	fEqnC);
	nC.subMul(fEqnC.getComponent<3>(),	fEqnD);

	// Error for normal components is e < 1/2^24
	// Error for plane offset is d < 1.
	// Error for nAB < 4e + 2e^2
	// Error for nA < 4 + 2e

	// Compute determinant
	const hkSimdDouble64 detLeft	= nAB.dot<3>(nC);
	const hkSimdDouble64 detRight	= nCD.dot<3>(nA);
	hkSimdDouble64 det4;			det4.setAdd(detLeft, detRight);
	hkSimdDouble64 absDet;			absDet.setAbs(det4);
	det4LessZero					= det4.lessZero();
	det4EqualZero.set<hkVector4ComparisonMask::MASK_NONE>();	// Always false, as we switch to fixed precision if too close to zero!
	HK_ON_DEBUG(m_numApproxCalls++);
	HK_ON_DEBUG(m_numApproxDet4++);

	// Return SUCCESS if the determinant is above the error threshold!
	return absDet.isGreaterEqual(hkSimdDouble64::fromFloat(TOL_DET_4));
}

HK_FORCE_INLINE void hkcdPlanarGeometryPredicates::computeExactDet4(const Plane& planeA, const Plane& planeB, const Plane& planeC, const Plane& planeD, hkVector4dComparison& det4LessZero, hkVector4dComparison& det4EqualZero)
{
	hkInt64Vector4 iNrmA, iNrmB, iNrmC, iNrmD;	
	hkSimdInt<128> iOffsetA, iOffsetB, iOffsetC, iOffsetD;

	planeA.getExactNormal(iNrmA);	planeA.getExactOffset(iOffsetA);
	planeB.getExactNormal(iNrmB);	planeB.getExactOffset(iOffsetB);
	planeC.getExactNormal(iNrmC);	planeC.getExactOffset(iOffsetC);
	planeD.getExactNormal(iNrmD);	planeD.getExactOffset(iOffsetD);

	hkInt128Vector4 nAB;	nAB.setCross(iNrmA, iNrmB);		// [L_12, -L_02, L_01]
	hkInt128Vector4 nCD;	nCD.setCross(iNrmC, iNrmD);		// [H_12, -H_02, H_01]
	hkInt128Vector4 nA;		nA.setMul<3>(iOffsetB,	iNrmA);
	nA.subMul<3>(iOffsetA,	iNrmB);		// [ax bw - aw bx, ay bw - aw by, az bw - aw bz] = [L_03, L_13, L_23]
	hkInt128Vector4 nC;		nC.setMul<3>(iOffsetD,	iNrmC);
	nC.subMul<3>(iOffsetC,	iNrmD);		// [cx dw - dx cw, cy dw - dy cw, cz dw - dz cw] = [H_03, H_13, H_23]

	// Compute determinant
	const hkSimdInt<256> detLeft	= nAB.dot<3>(nC);			// (L_12 * H_03 - L_02 * H_13 + L_01 * H_23)
	const hkSimdInt<256> detRight	= nCD.dot<3>(nA);			// (L_03 * H_12 - L_13 * H_02 + L_23 * H_01)
	hkSimdInt<256> det4;			det4.setAdd(detLeft, detRight);
	det4LessZero.set(det4.lessZero().getMask());
	det4EqualZero.set(det4.equalZero().getMask());
	HK_ON_DEBUG(m_numExactDet4++);
}

//
//	Computes the winding of the 3 given vertices w.r.t. the given triangle normal.

HK_FORCE_INLINE hkcdPlanarGeometryPredicates::Winding HK_CALL hkcdPlanarGeometryPredicates::triangleWinding(const Plane (&planesA)[3], const Plane (&planesB)[3], const Plane (&planesC)[3], PlaneParam supportPlane)
{
	// Project everything on a single plane, as it will be much easier to compute the exact stuff. Pick the largest component of the normal as the projection plane
	int axisX, axisY, axisZ;
	{
		hkInt64Vector4 absN;	supportPlane.getExactNormal(absN);
								absN.setAbs(absN);
		axisZ	= absN.getIndexOfMaxComponent<3>();
		axisX	= ((1 << axisZ) & 3);
		axisY	= ((1 << axisX) & 3);
	}

	// Use floating point first
	HK_ON_DEBUG(m_numApproxCalls++);
	const Winding winding = estimateTriangleWinding(planesA, planesB, planesC, supportPlane, axisX, axisY, axisZ);
	if ( winding != WINDING_UNKNOWN )
	{
		return winding;
	}

	HK_ON_DEBUG(m_numExactCalls++);
	return computeExactTriangleWinding(planesA, planesB, planesC, supportPlane, axisX, axisY, axisZ);
}

//
//	Orientation cache Constructor. Initializes the multiplier with 4 large prime numbers.

template <int N>
HK_FORCE_INLINE hkcdPlanarGeometryPredicates::OrientationCacheBase<N>::OrientationCacheBase()
#ifdef HK_DEBUG
:	m_numCacheHits(0)
,	m_numCacheAccesses(0)
#endif
{
	m_mul.set(73856093, 19349663, 83492791, 52448047);

	hkIntVector iv;	iv.setAll(-1);
	m_data.setSize((1 << N), iv);
}

#ifdef HK_DEBUG
//
//	Gets the ratio of cache hit

template <int N>
HK_FORCE_INLINE hkReal hkcdPlanarGeometryPredicates::OrientationCacheBase<N>::getCacheHitRatio() const
{
	if ( m_numCacheAccesses == 0 )
	{
		return 0;
	}
	return (hkReal)m_numCacheHits/(hkReal)m_numCacheAccesses;
}

//
//	Resets cache hit counters

template <int N>
HK_FORCE_INLINE void hkcdPlanarGeometryPredicates::OrientationCacheBase<N>::resetCacheHitCounters()
{
	m_numCacheHits		= 0;
	m_numCacheAccesses	= 0;
}
#endif

//
//	Computes the orientation of the point p defined by (ptPlaneA, ptPlaneB, ptPlaneC) with respect to the planeD, using an orientation cache

template <int N>
inline hkcdPlanarGeometryPredicates::Orientation HK_CALL hkcdPlanarGeometryPredicates::orientation(hkVector4dParameter p, PlaneParam ptPlaneA, PlaneParam ptPlaneB, PlaneParam ptPlaneC, PlaneParam planeD, hkIntVectorParameter planeIds, OrientationCacheBase<N>* orientationCache)
{
	Orientation ori;
	HK_ON_DEBUG(m_numFastCalls++;)
#if ( HKND_ENABLE_DEBUG_FAST_PREDICATE_CHECK )
		double dRes = -1.0;
#endif

	// Fast on plane test
	const int mask	= ~hkcdPlanarGeometryPrimitives::FLIPPED_PLANE_FLAG;
	hkIntVector intMask;			intMask.setAll(mask);
	hkIntVector origPlaneIds;		origPlaneIds.setAnd(planeIds, intMask);
	hkIntVector compVec;			compVec.setAll(origPlaneIds.getComponent<3>());
	if ( origPlaneIds.equalS32(compVec).anyIsSet<hkVector4ComparisonMask::MASK_XYZ>() ) 
	{
		ori = ON_PLANE;
	}
	else
	{
#if ( HKND_ENABLE_DEBUG_FAST_PREDICATE_CHECK )
		Plane planes[3];
		planes[0] = ptPlaneA;	planes[1] = ptPlaneB;	planes[2] = ptPlaneC;
		hkVector4d vCheck;
		approximateIntersectionFast(planes, vCheck);
		if ( vCheck.distanceTo(p).isGreater(hkSimdDouble64::fromFloat(2.0f)) )
		{
			HK_REPORT("Input point bad cache value!!");
			HK_BREAKPOINT(0);
		}
#endif

		// Do a quick point/plane check 
		const hkVector4d& plane			= planeD.getApproxEquation();
		hkVector4d pc;					pc.setXYZ_W(p, hkSimdDouble64_1);
		const hkSimdDouble64 dotRes		= pc.dot<4>(plane);
		hkSimdDouble64 absDotRes;		absDotRes.setAbs(dotRes);
#if ( HKND_ENABLE_DEBUG_FAST_PREDICATE_CHECK )
		dRes = absDotRes.getReal();
#endif

		if ( absDotRes.isGreaterEqual(hkSimdDouble64::fromFloat(TOL_FAST_PREDICATE)) )
		{
			ori = ( dotRes.isLessZero() ) ? BEHIND : IN_FRONT_OF;
		}
		else
		{
			// Not reliable ? call the more involved, possibly exact arithmetic
			HK_ON_DEBUG(m_numFastCallsFailed++);
			ori = orientation(ptPlaneA, ptPlaneB, ptPlaneC, planeD, planeIds, orientationCache);
		}	
	}

#if ( HKND_ENABLE_DEBUG_FAST_PREDICATE_CHECK )
	const Orientation oriRef = orientation(ptPlaneA, ptPlaneB, ptPlaneC, planeD, planeIds, orientationCache);
	if ( ori != oriRef )
	{	
		hkStringBuf strb;

		{
			const hkUint32* buf = reinterpret_cast<const hkUint32*>(&p);
			strb.printf("Point: [%lf, %lf, %lf, %lf]. [0x%08X.%08X, 0x%08X.%08X, 0x%08X.%08X, 0x%08X.%08X]",
				p(0), p(1), p(2), p(3),
				buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7]);
			HK_REPORT(strb);
		}
		
		{
			hkInt64Vector4 iN;	ptPlaneA.getExactNormal(iN);
			hkSimdInt<128> iO;	ptPlaneA.getExactOffset(iO);
			hkVector4d deq		= ptPlaneA.getApproxEquation();
			const hkUint32* buf = reinterpret_cast<const hkUint32*>(&deq);

			strb.printf("ptPlaneA: [0x%08X.%08X, 0x%08X.%08X, 0x%08X.%08X, 0x%08X.%08X.%08X.%08X]. [%lf, %lf, %lf, %lf]. [0x%08X.%08X, 0x%08X.%08X, 0x%08X.%08X, 0x%08X.%08X]", 
				(iN.getComponent<0>() >> 32L) & 0xFFFFFFFF,	(iN.getComponent<0>() & 0xFFFFFFFF),
				(iN.getComponent<1>() >> 32L) & 0xFFFFFFFF,	(iN.getComponent<1>() & 0xFFFFFFFF),
				(iN.getComponent<2>() >> 32L) & 0xFFFFFFFF,	(iN.getComponent<2>() & 0xFFFFFFFF),
				iO.getWord<3>(), iO.getWord<2>(), iO.getWord<1>(), iO.getWord<0>(),
				deq(0), deq(1), deq(2), deq(3),
				buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7]);
			HK_REPORT(strb);
		}
		{
			hkInt64Vector4 iN;	ptPlaneB.getExactNormal(iN);
			hkSimdInt<128> iO;	ptPlaneB.getExactOffset(iO);
			hkVector4d deq		= ptPlaneB.getApproxEquation();
			const hkUint32* buf = reinterpret_cast<const hkUint32*>(&deq);

			strb.printf("ptPlaneB: [0x%08X.%08X, 0x%08X.%08X, 0x%08X.%08X, 0x%08X.%08X.%08X.%08X]. [%lf, %lf, %lf, %lf]. [0x%08X.%08X, 0x%08X.%08X, 0x%08X.%08X, 0x%08X.%08X]", 
				(iN.getComponent<0>() >> 32L) & 0xFFFFFFFF,	(iN.getComponent<0>() & 0xFFFFFFFF),
				(iN.getComponent<1>() >> 32L) & 0xFFFFFFFF,	(iN.getComponent<1>() & 0xFFFFFFFF),
				(iN.getComponent<2>() >> 32L) & 0xFFFFFFFF,	(iN.getComponent<2>() & 0xFFFFFFFF),
				iO.getWord<3>(), iO.getWord<2>(), iO.getWord<1>(), iO.getWord<0>(),
				deq(0), deq(1), deq(2), deq(3),
				buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7]);
			HK_REPORT(strb);
		}
		{
			hkInt64Vector4 iN;	ptPlaneC.getExactNormal(iN);
			hkSimdInt<128> iO;	ptPlaneC.getExactOffset(iO);
			hkVector4d deq		= ptPlaneC.getApproxEquation();
			const hkUint32* buf = reinterpret_cast<const hkUint32*>(&deq);

			strb.printf("ptPlaneC: [0x%08X.%08X, 0x%08X.%08X, 0x%08X.%08X, 0x%08X.%08X.%08X.%08X]. [%lf, %lf, %lf, %lf]. [0x%08X.%08X, 0x%08X.%08X, 0x%08X.%08X, 0x%08X.%08X]", 
				(iN.getComponent<0>() >> 32L) & 0xFFFFFFFF,	(iN.getComponent<0>() & 0xFFFFFFFF),
				(iN.getComponent<1>() >> 32L) & 0xFFFFFFFF,	(iN.getComponent<1>() & 0xFFFFFFFF),
				(iN.getComponent<2>() >> 32L) & 0xFFFFFFFF,	(iN.getComponent<2>() & 0xFFFFFFFF),
				iO.getWord<3>(), iO.getWord<2>(), iO.getWord<1>(), iO.getWord<0>(),
				deq(0), deq(1), deq(2), deq(3),
				buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7]);
			HK_REPORT(strb);
		}
		{
			hkInt64Vector4 iN;	planeD.getExactNormal(iN);
			hkSimdInt<128> iO;	planeD.getExactOffset(iO);
			hkVector4d deq		= planeD.getApproxEquation();
			const hkUint32* buf = reinterpret_cast<const hkUint32*>(&deq);

			strb.printf("planeD: [0x%08X.%08X, 0x%08X.%08X, 0x%08X.%08X, 0x%08X.%08X.%08X.%08X]. [%lf, %lf, %lf, %lf]. [0x%08X.%08X, 0x%08X.%08X, 0x%08X.%08X, 0x%08X.%08X]", 
				(iN.getComponent<0>() >> 32L) & 0xFFFFFFFF,	(iN.getComponent<0>() & 0xFFFFFFFF),
				(iN.getComponent<1>() >> 32L) & 0xFFFFFFFF,	(iN.getComponent<1>() & 0xFFFFFFFF),
				(iN.getComponent<2>() >> 32L) & 0xFFFFFFFF,	(iN.getComponent<2>() & 0xFFFFFFFF),
				iO.getWord<3>(), iO.getWord<2>(), iO.getWord<1>(), iO.getWord<0>(),
				deq(0), deq(1), deq(2), deq(3),
				buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7]);
			HK_REPORT(strb);
		}

		HK_REPORT("Plane Ids " << planeIds.getComponent<0>() << ", " << planeIds.getComponent<1>() << ", " << planeIds.getComponent<2>() << ", " << planeIds.getComponent<3>());

		HK_REPORT("Fast predicate check failure (returned " << ori << ", ref is " << oriRef << ". dist is " << dRes << "!!");
		HK_BREAKPOINT(0);
	}	
#endif

	return ori;
}

//
//	Computes the orientation of the point (ptPlaneA, ptPlaneB, ptPlaneC) with respect to the planeD, using an orientation cache

template <int N>
inline hkcdPlanarGeometryPredicates::Orientation HK_CALL hkcdPlanarGeometryPredicates::orientation(PlaneParam ptPlaneA, PlaneParam ptPlaneB, PlaneParam ptPlaneC, PlaneParam planeD, hkIntVectorParameter planeIds, OrientationCacheBase<N>* orientationCache)
{
	Orientation retVal;

	// Evaluate Det3
	hkVector4dComparison det3LessZero, det3EqualZero;
	if ( !computeApproxDet3(ptPlaneA, ptPlaneB, ptPlaneC, det3LessZero, det3EqualZero) )
	{
		computeExactDet3(ptPlaneA, ptPlaneB, ptPlaneC, det3LessZero, det3EqualZero);
	}

	// Evaluate Det4
	hkVector4dComparison det4LessZero, det4EqualZero;
	if ( !computeApproxDet4(ptPlaneA, ptPlaneB, ptPlaneC, planeD, det4LessZero, det4EqualZero) )
	{
		if ( orientationCache )
		{
			// try to find orientation in cache, to avoid costly exact det4 computation
			const int shift = 32 - hkcdPlanarGeometryPrimitives::FLIPPED_PLANE_BIT;

			// Convert plane Ids to our internal format
			hkIntVector v;
			{
				v.setShiftLeft32(planeIds, shift);
				v.setShiftRight32(v, shift);
				v.setSelect<hkVector4ComparisonMask::MASK_XYZ>(v, planeIds);
				v.setSortS32<3, HK_SORT_ASCENDING>(v);
			}

			// Compute the hash, get the cached vector and compare with the given one
			hkIntVector vCache;	vCache.setMul(v, orientationCache->m_mul);
			const hkUint32 idx	= vCache.horizontalXorS32<4>() & ((1 << N) - 1);
			vCache = orientationCache->m_data[idx];
#ifdef HK_DEBUG
			orientationCache->m_numCacheAccesses++;
#endif

			retVal = (Orientation)(vCache.getComponent<3>() & 0x7);
			vCache.setShiftRight32(vCache, shift - 1);
			if ( vCache.compareEqualS32(v).allAreSet() )
			{
				// Value cached, save it and returns
#if ( HKND_ENABLE_DEBUG_ORIENTATION_CACHE_INCONSISTENCIES )
				{
					const Orientation oriRef = (Orientation)(hkcdPlanarGeometryPredicates::orientation(pA, pB, pC, pD) & hkcdPlanarGeometryPredicates::ORIENTATION_MASK);
					if ( oriRef != ori )
					{
						HK_REPORT("Cache inconsistency detected!!");
						HK_BREAKPOINT(0);
					}
				}
#endif
#ifdef HK_DEBUG
				orientationCache->m_numCacheHits++;
#endif
				return retVal;
			}

			// Not cached, compute and cache result
			computeExactDet4(ptPlaneA, ptPlaneB, ptPlaneC, planeD, det4LessZero, det4EqualZero);

			// Write result in the cache
			const int sign = mulSigns(det3LessZero, det3EqualZero, det4LessZero, det4EqualZero);
			retVal = (sign < 0) ? BEHIND : ((sign > 0) ? IN_FRONT_OF : ON_PLANE);

			vCache.setShiftLeft32(v, shift - 1);
			vCache.setComponent<3>(vCache.getComponent<3>() | retVal);
			orientationCache->m_data[idx] = vCache;

			return retVal;
		}
		else
		{
			// No orientation cache provided, compute orienation as normal
			computeExactDet4(ptPlaneA, ptPlaneB, ptPlaneC, planeD, det4LessZero, det4EqualZero);
		}
	}

	const int sign = mulSigns(det3LessZero, det3EqualZero, det4LessZero, det4EqualZero);
	retVal = (sign < 0) ? BEHIND : ((sign > 0) ? IN_FRONT_OF : ON_PLANE);

	return retVal;
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
