/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_GEOMETRY_PROCESSING_H
#define HK_GEOMETRY_PROCESSING_H
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#include <Common/Base/Config/hkProductFeatures.h>
#include <Common/Base/System/Stopwatch/hkStopwatch.h>
#include <Common/Base/Types/Geometry/Aabb/hkAabb.h>
#include <Common/Base/Container/LocalArray/hkLocalArray.h>
#include <Common/Base/Math/Vector/hkFourTransposedPoints.h>
#include <Geometry/Internal/Algorithms/Intersect/hkcdIntersectTriangleTriangle.h>

/// Control inlining to HKGP related code.
	#define HK_COMPILE_ENABLE_GP_FULL_INLINING 1
	#ifdef HK_DYNAMIC_DLL
		#pragma warning(disable:4714) // will not be always inlined for dll
	#endif

/// If HKGP_FORCE_INLINE is not defined, set it to HK_FORCE_INLINE
#if !defined(HKGP_FORCE_INLINE)
	#if HK_COMPILE_ENABLE_GP_FULL_INLINING
		#define HKGP_FORCE_INLINE HK_FORCE_INLINE
	#else
		#define HKGP_FORCE_INLINE inline
	#endif
#endif

struct hkGeometry;

/// Tools for geometry processing
struct  hkGeometryProcessing
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE,hkGeometryProcessing);
	
	//	
	// Types
	//	
	
	/// Some prime numbers
	enum Primes
	{
		NEXT_PRIME_AFTER_8		=	11,
		NEXT_PRIME_AFTER_16		=	17,
		NEXT_PRIME_AFTER_32		=	37,
		NEXT_PRIME_AFTER_64		=	67,
		NEXT_PRIME_AFTER_128	=	131,
		NEXT_PRIME_AFTER_256	=	257,
		NEXT_PRIME_AFTER_512	=	521,
		NEXT_PRIME_AFTER_1024	=	1031,
		NEXT_PRIME_AFTER_2048	=	2053,
		NEXT_PRIME_AFTER_4096	=	4099,
		NEXT_PRIME_AFTER_8192	=	8209
	};

	/// A simple hash table providing fast value lookup
	template <typename VALUE,typename ALLOCATOR=hkContainerHeapAllocator>
	class HashTable
	{
	public:
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_MAP,HashTable);

		/// Iterator
		struct Iterator
		{			
		private:
			friend class HashTable;
			inline					Iterator() {}
			inline					Iterator(HashTable* hashTable) : m_table(hashTable),m_bucket(-1),m_item(-1) { next(); }
			
			HashTable*		m_table;
			int				m_bucket;
			int				m_item;
		public:
			Iterator&				operator++()						{ next(); return *this; }
			Iterator				operator++(int)						{ const Iterator i(*this); operator++(); return i; }
			const VALUE&			operator()() const					{ return m_table->m_buckets[m_bucket][m_item]; }
			VALUE&					operator()()						{ return m_table->m_buckets[m_bucket][m_item]; }
									operator const Iterator*() const	{ return(m_bucket<m_table->m_buckets.getSize()?this:0); }
		private:
			HKGP_FORCE_INLINE void	next();
		};
		
		/// Create an empty hash table with zero buckets
		HKGP_FORCE_INLINE							HashTable() : m_numItems(0) {}
		
		/// Create an empty hash table with 'numBuckets' buckets
		HKGP_FORCE_INLINE							HashTable(int numBuckets) : m_numItems(0) { setBucketsCount(numBuckets); }
		
		/// Destructor
		HKGP_FORCE_INLINE							~HashTable() {}
		
		/// remove all items and set the number of buckets
		HKGP_FORCE_INLINE	void					setBucketsCount(int numBuckets);
		
		/// remove all items and set bucket size to zero.
		HKGP_FORCE_INLINE void						clear() { m_buckets.clear();m_numItems=0; }

		/// remove all items.
		HKGP_FORCE_INLINE void						removeAll() { for(int i=0;i<m_buckets.getSize();++i) { m_buckets[i].clear(); } m_numItems=0; }

		/// reserve items in buckets
		HKGP_FORCE_INLINE void						reserve(int numItems) { for(int i=0;i<m_buckets.getSize();++i) { m_buckets[i].reserve(m_buckets[i].getSize()+numItems); } }
		
		/// return the number of items stored in the hash table
		HKGP_FORCE_INLINE int						getSize() const { return(m_numItems); }

		/// get an iterator
		HKGP_FORCE_INLINE Iterator					getIterator() { return Iterator(this); }
		
		/// lookup a bucket given an hash
		HKGP_FORCE_INLINE hkArray<VALUE,ALLOCATOR>&	lookupBucket(int hash) { HK_ASSERT2(0x545415,m_buckets.getSize()>0,"Hash table not initialized"); return(m_buckets[((unsigned)hash)%m_buckets.getSize()]); }

		/// lookup a bucket given an hash
		HKGP_FORCE_INLINE const hkArray<VALUE,ALLOCATOR>&	lookupBucket(int hash) const { HK_ASSERT2(0x545415,m_buckets.getSize()>0,"Hash table not initialized"); return(m_buckets[((unsigned)hash)%m_buckets.getSize()]); }
		
		/// find an item given an hash and a value
		HKGP_FORCE_INLINE const VALUE*				find(int hash,const VALUE& value) const;

		/// find an item given an hash and a value
		HKGP_FORCE_INLINE	VALUE*					find(int hash,const VALUE& value);
		
		/// insert an item given an hash and a value
		HKGP_FORCE_INLINE	VALUE*					insert(int hash,const VALUE& value);
		
		/// remove an item given an hash and a value
		HKGP_FORCE_INLINE void						remove(int hash,const VALUE& value);
		
		/// shorthand for find
		HKGP_FORCE_INLINE	const VALUE*			find(const VALUE& value) const { return(find((int)value.getHash(),value)); }

		/// shorthand for find
		HKGP_FORCE_INLINE	VALUE*					find(const VALUE& value) { return(find((int)value.getHash(),value)); }
		
		/// shorthand for insert
		HKGP_FORCE_INLINE	VALUE*					insert(const VALUE& value) { return(insert((int)value.getHash(),value)); }
		
		/// shorthand for remove
		HKGP_FORCE_INLINE void						remove(const VALUE& value) { return(remove((int)value.getHash(),value)); }

		/// append another hashtable to this, rehash items only if m_buckets.getSize() != other.m_buckets.getSize()
		inline void									append(const HashTable& other);
	public:
		hkArray<hkArray<VALUE,ALLOCATOR>,ALLOCATOR >	m_buckets;
		int												m_numItems;
	};

	/// Pool base allocator policy.
	/// \warning If object are still allocated when a pool is destroyed, their destructors will NOT be called.
	template <typename T,const int N,typename ALLOCATOR=hkContainerHeapAllocator>
	struct PoolAllocator
	{		
		struct Item
		{
			HK_ALIGN_REAL(hkUint8				m_data[sizeof(T)]);
			HK_ALIGN16(void*	m_pool);
		};
		struct Pool
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_GEOMETRY,Pool);
			Item	m_items[N];
			Item*	m_free;
			Pool*	m_links[2];
			int		m_used;
		};
		inline					PoolAllocator() : m_firstPool(HK_NULL) {}
		inline					~PoolAllocator();
		HKGP_FORCE_INLINE T*	allocate()						{ return(new(allocateItem()) T()); }
		HKGP_FORCE_INLINE T*	allocate(const T& value)		{ return(new(allocateItem()) T(value)); }
		inline void				release(T* item);
		HKGP_FORCE_INLINE bool	needRelease() const				{ return(false); }
		HKGP_FORCE_INLINE void	clear();
	private:
		inline Item*			allocateItem();
		inline Pool*			allocateNewPool();
		inline void				releasePool(Pool* pool);
		inline					PoolAllocator(const PoolAllocator&)	{}
		inline					void operator=(const PoolAllocator&) {}
	private:
		Pool*					m_firstPool;
	};

	/// Local array allocator
	template <typename T, int CAPACITY>
	struct LocalArrayAllocator
	{
		inline					LocalArrayAllocator();
		inline					~LocalArrayAllocator();
	
		HK_FORCE_INLINE T*		allocate(const T& value);
		HK_FORCE_INLINE T*		allocate();
		
		inline void				release(T* item) { HK_ASSERT(0x12a7f7e1, false); }
		HK_FORCE_INLINE bool	needRelease() const				{ return(false); }
		HK_FORCE_INLINE void	clear();
	private:
		LocalArrayAllocator(const LocalArrayAllocator&);
		void operator=(const LocalArrayAllocator&);
	private:
		HK_PAD_ON_SPU( T* )		m_data;
		HK_PAD_ON_SPU( T* )		m_next;
		HK_PAD_ON_SPU( const T* ) m_end;
	};

	/// IFunction
	template <typename IN_TYPE,typename OUT_TYPE>
	struct IFunction
	{
		typedef IN_TYPE		typeIn;
		typedef OUT_TYPE	typeOut;
		
		virtual ~IFunction() {}
		virtual typeOut		evaluate(const typeIn&) const=0;
	};

	/// ConstFunction
	template <typename FUNCTION_TYPE>
	struct ConstFunction : public FUNCTION_TYPE
	{
										ConstFunction(const typename FUNCTION_TYPE::typeOut& value) : m_value(value) {}
		typename FUNCTION_TYPE::typeOut	evaluate(const typename FUNCTION_TYPE::typeIn&) const { return(m_value); }
		typename FUNCTION_TYPE::typeOut	m_value;
	};

	/// IFunction_4_1 : map hkVector4 to hkReal
	typedef IFunction<hkVector4,hkReal>		IFunction_4_1;
	
	/// Span
	template <typename T>
	struct Span
	{
		typedef T						type;

		HKGP_FORCE_INLINE void			setFromVertices(const hkVector4& direction, const hkVector4* vertices,int numVertices);		
		static HKGP_FORCE_INLINE hkBool32	intersect(const Span& a,const Span& b);

		T								m_bounds[2];
		
	};

	typedef Span<hkReal>				RealSpan;
	typedef Span<hkSimdReal>			SimdRealSpan;

	/// IsoVertex
	struct IsoVertex
	{
		//+hk.MemoryTracker(ignore=True)
		inline							IsoVertex() : m_edge(-1),m_solution(0) {}
		inline							IsoVertex(int e,hkReal s) : m_edge(e),m_solution(s) {}
		int								m_edge;
		hkReal							m_solution;

		static int HK_CALL				solveTriangle(const hkReal values[3],IsoVertex verticesOut[2],hkReal orientation = 1.0f);
	};

	/// KISS Based PRNG (http://www.cs.ucl.ac.uk/staff/d.jones/GoodPracticeRNG.pdf)
	struct HK_EXPORT_COMMON Prng
	{
		/// Ctor.
		HK_FORCE_INLINE Prng(hkUint32 seed = 123456789) : m_x(seed), m_y(234567891), m_z(345678912), m_w(456789123), m_c(0) {}
				
		/// Return the next unsigned int, range: [0,4294967295]
		HK_FORCE_INLINE hkUint32	nextUint32()
		{
			m_y ^= (m_y<<5);
			m_y ^= (m_y>>7);
			m_y ^= (m_y<<22);
			const hkInt32 t = (hkInt32) (m_z + m_w + m_c);
			m_z =	m_w;
			m_c =	t < 0 ? 1 : 0;
			m_w =	(hkUint32) (t & 2147483647);
			m_x +=	1411392427;

			return m_x + m_y + m_w;
		}

		/// Return the next signed int, range: [0,2147483647]
		HK_FORCE_INLINE hkInt32		nextInt32()
		{
			return (hkInt32) (nextUint32() >> 1);
		}

		/// Return the next hkReal, range: [0,1]
		HK_FORCE_INLINE hkReal		nextReal()
		{
			return nextUint32() / 4294967296.0f;
		}

		/// Return the next vector, range: [0,1] x N
		template <int N>
		HK_FORCE_INLINE void		nextVector(hkVector4& v)
		{
			v.setZero();
			for(int i=0; i<N; ++i) v(i) = nextReal();
		}

		/// Return the next normal vector.
		HK_FORCE_INLINE void		nextUnitVector3(hkVector4& v, const hkVector4& normal = hkVector4::getZero())
		{
			const hkReal	x = nextReal() * 2 * HK_REAL_PI;
			const hkReal	y = hkMath::acos(1 - 2 * nextReal());
			v.set( hkMath::sin(y) * hkMath::cos(x), hkMath::sin(y) * hkMath::sin(x), hkMath::cos(y), hkReal(0));
			if(v.dot<3>(normal).isLessZero()) v.mul(hkSimdReal_Minus1);
		}

		/// Return the next 3d bary-center.
		HK_FORCE_INLINE void		nextBaryCenter3D(hkVector4& bc)
		{
			const hkSimdReal	x = hkSimdReal::fromFloat(nextReal()).sqrt<HK_ACC_FULL,HK_SQRT_SET_ZERO>();
			const hkSimdReal	y = hkSimdReal::fromFloat(nextReal());
			bc.set( hkSimdReal_1 - x, x * (hkSimdReal_1 - y), x * y, hkSimdReal_0);
		}

		/// Returns a new PRNG.
		inline Prng		nextPrng()
		{
			Prng prng(nextUint32());
			for(int i=0,n=int(nextUint32() % NEXT_PRIME_AFTER_64); i<n; ++i) prng.nextUint32();
			return prng;
		}

		hkUint32	m_x, m_y, m_z, m_w, m_c;
	};

	/// Uniform triangulated surface sampler.
	struct HK_EXPORT_COMMON SurfaceSampler
	{
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_GEOMETRY,SurfaceSampler);
		
		struct Element
		{
			HK_DECLARE_POD_TYPE();

			hkReal	m_value;
			int		m_index;
		};

				SurfaceSampler() { clear(); }

		void	clear();
		void	addGeometry(const hkGeometry& geometry, int baseIndex = 0);
		void	addElement(hkVector4Parameter a, hkVector4Parameter b, hkVector4Parameter c, int index);
		int		findElement(int index) const;
		int		searchElement(hkReal value) const;

		/// Pick a random sample, returns the index of the element and set baryCenter to the barymetric coordinates of the sample.
		int		getSample(Prng& prng, hkVector4& baryCenter) const;
			
		hkArray<Element>	m_elements;
		hkReal				m_domain;
	};

	/// Online mean and variance accumulator.
	/// T must implement the following 'hkVector4' like methods: setZero, setSub, setMul, addMul, add.
	template <typename T>
	struct MeanVariance
	{
		HK_FORCE_INLINE MeanVariance()
		{
			setZero();
		}
	
		HK_FORCE_INLINE void setZero()
		{
			m_sum.setZero();
			m_sum2.setZero();
			m_weight.setZero();
			m_n = 0;
		}

		HK_FORCE_INLINE void	add(const T& x, hkSimdRealParameter w)
		{
			T	value; value.setMul(x,w);
			T	squared; squared.setMul(value,value);
			m_sum.add(value);
			m_sum2.add(squared);
			m_weight.add(w);
			m_n++;
		}

		HK_FORCE_INLINE void	add(const MeanVariance& other)
		{
			m_sum.add(other.m_sum);
			m_sum2.add(other.m_sum2);
			m_weight.add(other.m_weight);
			m_n += other.m_n;
		}

		HK_FORCE_INLINE void	computeMeanAndVariance(T& meanOut, T& varianceOut) const
		{
			hkSimdReal	invW; invW.setReciprocal<HK_ACC_FULL,HK_DIV_SET_ZERO>(m_weight);
			meanOut.setMul(m_sum, invW);

			hkSimdReal	invN; invN.setReciprocal<HK_ACC_FULL,HK_DIV_SET_ZERO>(hkSimdReal::fromInt32(m_n-1));
			T			prod; prod.setMul(m_sum, meanOut);
			T			diff; diff.setSub(m_sum2, prod);
			varianceOut.setMul(diff, invN);
		}
	
		T			m_sum,m_sum2;	///< Sum and sum squared of the samples.
		hkSimdReal	m_weight;		///< Sum of the weights.
		int			m_n;			///< Number of samples.
	};
	
	//
	// Methods
	//

	/// evaluate (a-o) x (b-o)
	static HK_EXPORT_COMMON HKGP_FORCE_INLINE void HK_CALL		crossOffset(hkVector4Parameter o, hkVector4Parameter a, hkVector4Parameter b, hkVector4& ret);

	/// evaluate (a1-a0) x (b1-b0)
	static HK_EXPORT_COMMON HKGP_FORCE_INLINE hkVector4			crossEdges(const hkVector4& a0, const hkVector4& a1, const hkVector4& b0, const hkVector4& b1);

	/// Compare two plane for equality
	static HK_EXPORT_COMMON HKGP_FORCE_INLINE bool				comparePlanes(const hkVector4& a, const hkVector4& b, hkReal maxDistance, hkReal minCosAngle);

	/// Decompose a vector into parallel and perpendicular components, return vector/axis dot product.
	static HK_EXPORT_COMMON HKGP_FORCE_INLINE hkSimdReal		decomposeVector(const hkVector4& vector, const hkVector4& axis, hkVector4& para, hkVector4& perp);

	/// Project vector on plane
	static HK_EXPORT_COMMON HKGP_FORCE_INLINE hkVector4			projectOnPlane(const hkVector4& vector,const hkVector4& axis);

	/// Project vector on axis
	static HK_EXPORT_COMMON HKGP_FORCE_INLINE hkVector4			projectOnAxis(const hkVector4& vector,const hkVector4& axis);

	/// calculate triangle (area * 2)^2
	static HK_EXPORT_COMMON HKGP_FORCE_INLINE hkSimdReal		triangleArea2Squared(hkVector4Parameter a, hkVector4Parameter b);

	/// calculate triangle area * 2
	static HK_EXPORT_COMMON HKGP_FORCE_INLINE hkSimdReal		triangleArea2(hkVector4Parameter a, hkVector4Parameter b, hkVector4Parameter c);	

	/// calculate tetrahedron (signed) volume * 6
	static HK_EXPORT_COMMON HKGP_FORCE_INLINE hkSimdReal		tetrahedronVolume6(hkVector4Parameter a, hkVector4Parameter b, hkVector4Parameter c, hkVector4Parameter d);

	/// apply a transform to a plane.
	static HK_EXPORT_COMMON HKGP_FORCE_INLINE hkVector4		transformPlaneToWorld(const hkTransform& transform,const hkVector4& plane);

	/// apply the inverse of a transform to a plane.
	static HK_EXPORT_COMMON HKGP_FORCE_INLINE hkVector4		transformPlaneToLocal(const hkTransform& transform,const hkVector4& plane);

	/// compute the circum-center of a triangle.
	static HK_EXPORT_COMMON HKGP_FORCE_INLINE hkBool32		circumCenter(hkVector4Parameter a, hkVector4Parameter b, hkVector4Parameter c, hkVector4& centerOut);

	/// compute the circum-center of a tetrahedron.
	static HK_EXPORT_COMMON HKGP_FORCE_INLINE hkBool32		circumCenter(hkVector4Parameter a, hkVector4Parameter b, hkVector4Parameter c, hkVector4Parameter d, hkVector4& centerOut);

	/// intersect 3 planes
	static HK_EXPORT_COMMON bool	HK_CALL					intersectPlanes(hkVector4Parameter p0, hkVector4Parameter p1, hkVector4Parameter p2, hkVector4& intersection);
	
	/// intersect a line with a plane
	static HK_EXPORT_COMMON bool	HK_CALL					intersectLineWithPlane(hkVector4Parameter x0, hkVector4Parameter x1, hkVector4Parameter plane, hkSimdReal& toi);

	/// check intersection between two triangles. Thin wrapper, calls the implementation in hkcdCollide 
	static HK_EXPORT_COMMON HK_FORCE_INLINE hkBool32 HK_CALL	checkTrianglesIntersection(const hkVector4* triangleA,const hkVector4* triangleB);

	/// distance from a point to a line
	static HK_EXPORT_COMMON hkSimdReal HK_CALL				squaredDistanceFromPointToLine(hkVector4Parameter p, hkVector4Parameter p0, hkVector4Parameter p1, hkSimdReal& toi);
	
	/// distance from a point to a line
	static HK_EXPORT_COMMON hkSimdReal HK_CALL				squaredDistanceFromPointToLine(hkVector4Parameter p, hkVector4Parameter p0, hkVector4Parameter p1, hkVector4& normalOut, hkReal* baryOut=HK_NULL);	

	/// distance from a point to a triangle
	static HK_EXPORT_COMMON hkSimdReal HK_CALL				squaredDistanceFromPointToTriangle(hkVector4Parameter p, hkVector4Parameter p0, hkVector4Parameter p1, hkVector4Parameter p2, hkVector4& normalOut, hkVector4* baryOut=HK_NULL);

	/// nearest distance between two 3d lines
	static HK_EXPORT_COMMON hkSimdReal HK_CALL				nearestDistanceBetweenLines(hkVector4Parameter a0, hkVector4Parameter a1, hkVector4Parameter b0, hkVector4Parameter b1, hkSimdReal& u, hkSimdReal& v);
	
	/// check if a point is inside a triangle
	static HK_EXPORT_COMMON bool HK_CALL					checkPointInsideTriangle(hkVector4Parameter p, hkVector4Parameter a, hkVector4Parameter b, hkVector4Parameter c, hkSimdRealParameter epsilon);

	/// build a transposed array of hkVector4
	static HK_EXPORT_COMMON void HK_CALL					buildTransposedArray(const hkArray<hkVector4>& vertices, hkArray<hkFourTransposedPoints>& output);

	/// get supporting vertex (index stored in W)
	static HK_EXPORT_COMMON void	HK_CALL					getSupportingVertex(const hkArrayBase<hkFourTransposedPoints>& transposedVertices,const hkVector4& direction, hkVector4& vertexOut);
		
	/// generate random points distribution inside a geometry
	static HK_EXPORT_COMMON bool HK_CALL					generateRandomDistribution(const hkGeometry& geometry,int numPoints,hkArray<hkVector4>& points,int seed=180673);

	/// generate a density controlled points distribution inside a geometry, if densityFunction is not set, uniform density is assumed.
	static HK_EXPORT_COMMON bool HK_CALL					generateUniformDistribution(const hkGeometry& geometry,int numPoints,hkArray<hkVector4>& points,int maxIterations=256,int seed=180673,const IFunction_4_1* densityFunction=HK_NULL);

	/// make sure the aspect ratio of an AABB is one.
	static HK_EXPORT_COMMON void HK_CALL					normalizeAspectRatio(hkAabb& box);

	/// take a regular sample of an AABB.
	static HK_EXPORT_COMMON hkVector4 HK_CALL				sampleAabb(const hkAabb& box, hkVector4Parameter unitLocation);
	
	/// get one the AABB vertex.
	static HK_EXPORT_COMMON HKGP_FORCE_INLINE void			getVertex(const hkAabb& box, int index, hkVector4& vertexOut);
	
	/// create an hash code based on two pointer size values, with makeHash(0,0)==0
	template <typename A,typename B>
	static HKGP_FORCE_INLINE hkUlong						makeHash(A a,B b);

	/// create a symmetric hash code based on two pointer size values, with makeSymmetricHash(0,0)==0 and makeSymmetricHash(a,b)==makeSymmetricHash(b,a)
	template <typename A,typename B>
	static HKGP_FORCE_INLINE hkUlong						makeSymmetricHash(A a,B b);

	/// Evaluate tri-linear barycentric coordinates on hkVector4
	static HK_EXPORT_COMMON HK_FORCE_INLINE hkVector4		evaluateBarycentricCoordinates(hkVector4Parameter baryCenter, hkVector4Parameter a, hkVector4Parameter b, hkVector4Parameter c);
	
	/// Choose N from M with N <= M , count permutations.
	static HK_EXPORT_COMMON HKGP_FORCE_INLINE int			chooseMN_count(int m,int n);
	
	/// Choose N from M with N <= M , get a permutation.
	static HK_EXPORT_COMMON inline void						chooseMN_pick(int m,int n,int i,int* set);

	/// Map unfold octahedron coordinates to unit normal.
	static HK_EXPORT_COMMON void	HK_CALL					octahedronToNormal(const hkVector4& uv, hkVector4& normal);

	/// Map unit normal to unfold octahedron coordinates.
	static HK_EXPORT_COMMON void	HK_CALL					normalToOctahedron(const hkVector4& normal, hkVector4& uv);

	/// Wrap unfold octahedron coordinates.
	static HK_EXPORT_COMMON void	HK_CALL					wrapOctahedronCoordinates(hkVector4& uv);

	/// Compute triangle quality.
	static HK_EXPORT_COMMON hkSimdReal HK_CALL				computeTriangleQuality(hkVector4Parameter p0, hkVector4Parameter p1, hkVector4Parameter p2);

	/// Compute the median of two vectors
	static HK_EXPORT_COMMON hkVector4 HK_CALL				computeMedian(hkVector4Parameter a, hkVector4Parameter b);
	
	/// Compute the median of three vectors
	static HK_EXPORT_COMMON hkVector4 HK_CALL				computeMedian(hkVector4Parameter a, hkVector4Parameter b, hkVector4Parameter c);

	/// Compute the median of four vectors
	static HK_EXPORT_COMMON hkVector4 HK_CALL				computeMedian(hkVector4Parameter a, hkVector4Parameter b, hkVector4Parameter c, hkVector4Parameter d);

	/// Weld duplicated vertices in an hkGeometry.
	static HK_EXPORT_COMMON void HK_CALL					weldVertices(hkGeometry& geometry);

	/// Return true if the geometry is a closed mesh. Many algorithms require the input mesh to be closed.
	static HK_EXPORT_COMMON hkBool HK_CALL					isGeometryClosed(const hkGeometry& geometry);

	/// Return the surface area of a given geometry.
	static HK_EXPORT_COMMON hkReal HK_CALL					computeSurfaceArea(const hkGeometry& geometry);

	/// Generate clusters from hkVector4 data points.
	/// Note: weights be can set to HK_NULL, in which case 1.0 will be used for all data points.
	static HK_EXPORT_COMMON void HK_CALL					generateClusters(const hkArray<hkVector4>& data, const hkArray<hkSimdReal>* weights, int numClusters, hkArray<int>& clusterIds, int maxIterations = 512);

	/// Generate clusters from hkReal data points.
	/// Note: weights be can set to HK_NULL, in which case 1.0 will be used for all data points.
	static HK_EXPORT_COMMON void HK_CALL					generateClusters(const hkArray<hkReal>& data, const hkArray<hkSimdReal>* weights, int numClusters, hkArray<int>& clusterIds, int maxIterations = 512);

	/// Generate clusters from a set of hkAabb.
	/// On return, the 'clusterRoots' array contains the first AABB index of each cluster and 'clusterNexts' contains the next AABB index in the cluster or -1.
	static HK_EXPORT_COMMON void HK_CALL					generateClusters(const hkAabb* aabbs, int numAabbs, int maxClusters, hkArray<int>& clusterRoots, hkArray<int>& clusterNexts);

	/// Stores max curvature in the W component of the vertices.
	static HK_EXPORT_COMMON void HK_CALL					computeCurvature(hkGeometry& geometry, hkSimdReal& maxCurvature);

	/// Resolve T-junctions in geometry.
	static HK_EXPORT_COMMON void	HK_CALL					fixTJunctions(hkGeometry& geometry, hkReal maxDistance);

	/// Subdivide geometry, increases the number of triangles by 4.
	static void HK_CALL					subdivideGeometry(hkGeometry& geometry);

	/// Detach triangles by preventing triangles from sharing vertices.
	static void HK_CALL					detachTriangles(hkGeometry& geometry);

	/// Laplacian smoothing.
	static void HK_CALL					laplacianSmoothing(hkGeometry& geometry, int iterations = 1, hkReal factor = 1);

	/// Minimize a scalar function of a normalized vector.
	/// Returns the normal that minimize the function as well as the value in its W component.
	template <typename FUNCTION>
	static inline hkVector4				minimizeN_R(int steps, int maxDepth, hkReal minConvergence, const FUNCTION& function);
		
	//
	// Macros
	//
	
	// Performance scope
	#define HK_PERF_SCOPE_EX(_name_,_ID_,_SILENT_)	hkGeometryProcessing::PerformanceScope performance_scope_##_ID_(_name_,_SILENT_)
	#define HK_PERF_SCOPE(_name_)					hkGeometryProcessing::PerformanceScope performance_scope(_name_,false)
	struct HK_EXPORT_COMMON PerformanceScope
	{
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE,hkGeometryProcessing::PerformanceScope);
		HKGP_FORCE_INLINE PerformanceScope(const char* name,bool silent) : m_name(name),m_silent(silent)
			{
				//if(!m_silent) HK_REPORT("=> "<<name<<"...");
				m_stopWatch.start();
			}
		HKGP_FORCE_INLINE ~PerformanceScope()
			{
				m_stopWatch.stop();
				const hkReal	esecs=m_stopWatch.getElapsedSeconds();
				if(!m_silent)
				{
					if(esecs<=1)
					{ HK_TRACE("=> "<<m_name<<" : "<<(esecs*1000)<<" ms"); }
					else
					{ HK_TRACE("=> "<<m_name<<" : "<<(esecs*1000)<<" ms ("<<(esecs/60)<<" minutes)"); }
				}
			}
		hkStopwatch	m_stopWatch;
		const char*	m_name;
		bool		m_silent;
	};
	// Accumulator scope
	#define HK_ACC_SCOPE_EX(_storage_,_ID_)	hkGeometryProcessing::AccumulatorScope accumulator_scope_##_ID_(_storage_)
	#define HK_ACC_SCOPE(_storage_)			hkGeometryProcessing::AccumulatorScope accumulator_scope(_storage_)
	struct HK_EXPORT_COMMON AccumulatorScope
	{
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE,hkGeometryProcessing::AccumulatorScope);
		struct Item
		{
			//+hk.MemoryTracker(ignore=True)
			Item() { reset(); } void reset() { m_time=0;m_count=0; } hkReal m_time;int m_count;
		};
		HKGP_FORCE_INLINE AccumulatorScope(Item& storage) : m_storage(&storage) { ++storage.m_count;m_stopWatch.start(); }
		HKGP_FORCE_INLINE ~AccumulatorScope()	{ m_stopWatch.stop();m_storage->m_time+=m_stopWatch.getElapsedSeconds(); }
		hkStopwatch	m_stopWatch;
		Item*		m_storage;
	};

};
#include <Common/Internal/GeometryProcessing/hkGeometryProcessing.inl>

#endif

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
