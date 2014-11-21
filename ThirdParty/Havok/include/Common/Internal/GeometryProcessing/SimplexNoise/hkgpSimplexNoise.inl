/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

namespace	hkgpSimplexNoise
{
	// Jenkins hash.
	HK_FORCE_INLINE hkUint32	hash(hkUint32 x)
	{
		x = (x+0x7ed55d16) + (x<<12);
		x = (x^0xc761c23c) ^ (x>>19);
		x = (x+0x165667b1) + (x<<5);
		x = (x+0xd3a2646c) ^ (x<<9);
		x = (x+0xfd7046c5) + (x<<3);
		x = (x^0xb55a4f09) ^ (x>>16);
		return x;
	}
	
	//
	template <int N>
	HK_FORCE_INLINE hkUint32	hash(const hkUint32* x)
	{
		hkUint32	h = 0;
		for(int i=0; i<N; ++i)
		{
			h ^= x[i] << (i * 8);
		}
		return hash(h);
	}
	
	//
	template <int N> struct Pow2 { enum { VALUE = 2 * Pow2<N-1>::VALUE }; };

	//
	template <> struct Pow2<0> { enum { VALUE = 1 }; };

	//
	template <int INDEX>
	struct ComputeOrigin
	{
		static HK_FORCE_INLINE void unroll(const hkReal* p, int* o, hkReal s)
		{
			ComputeOrigin<INDEX-1>::unroll(p,o,s);

			const hkReal	x = p[INDEX] + s;
			o[INDEX]	=	int(x) - (hkMath::signBitSet(x) ? 1 : 0);
		}
	};

	//
	template <> struct ComputeOrigin<-1> { static HK_FORCE_INLINE void unroll(const hkReal*, int*, hkReal) {} };

};

//
template <int N, bool FIRST_DER, bool SECOND_DER>
inline hkReal	hkgpSimplexNoise::evaluate(const hkReal* positions, hkReal* der1, hkReal* der2)
{
	HK_COMPILE_TIME_ASSERT(0 < N);
	// Contants.
	const int		bitsPerAxis = 32 / (N+1);
	const hkUint32	bitMask = (1 << bitsPerAxis) - 1;
	const hkReal	bitHalf = bitMask / 2.0f;
	const hkReal	bitHalfInv = 1 / bitHalf;
	const hkReal	denBase = hkMath::sqrt(hkReal(N+1)) + 1;
	const hkReal	skewFactor = 1 / denBase;
	const hkReal	unskewFactor = 1 / (N + denBase);
	const hkReal	normalizationFactor = hkReal(1.9f) * bitHalfInv * 2;
	
	// Reset derivatives.
	if(FIRST_DER)	for(int i=0; i<N; ++i) der1[i] = 0;
	if(SECOND_DER)	for(int i=0; i<((N*(1+N))/2); ++i) der2[i] = 0;

	// Compute skew offset.
	hkReal	skewOffset = 0;
	for(int i=0; i<N; ++i) skewOffset += positions[i];
	skewOffset *= skewFactor;

	// Compute origin.
	int		origins[N];
	ComputeOrigin<N-1>::unroll(positions,origins,skewOffset);
		
	// Compute value and derivatives.
	hkReal	value = 0;
	for(int cornerIndex = 0; cornerIndex < Pow2<N>::VALUE; ++cornerIndex)
	{
		int		c[N];
		hkReal	uso=0;
		for(int i=0; i<N; ++i)
		{
			c[i]	=	origins[i] + ((cornerIndex >> i) & 1);
			uso		+=	c[i];
		}
		uso *= unskewFactor;
			
		hkReal		f[N];
		hkReal		k(0.5f);
		for(int i=0; i<N; ++i)
		{
			f[i]	=	positions[i] - (c[i] - uso);
			k		-=	f[i] * f[i];
		}
			
		if(k > 0)
		{
			hkReal		g[N];
			hkReal		d = 0;
			hkUint32	h = hash<N>((const hkUint32*)c);
				
			for(int i=0; i<N; ++i, h >>= bitsPerAxis)
			{
				const hkReal	a = (hkReal(h & bitMask) - bitHalf) * normalizationFactor;
				if(FIRST_DER | SECOND_DER) g[i] = a * k;
				d += f[i] * a;
			}

			// Value.
			value	+=	hkMath::pow<4>(k * 2) * d;

			// First derivative.
			if(FIRST_DER)
			{
				const hkReal	factor = hkMath::pow<3>(k) * 16;
				const hkReal	d8 = 8 * d;
				hkReal*			dOut = der1;
				for(int i=0; i<N; ++i)
				{
					*dOut++ += factor * (g[i] - d8 * f[i]);
				}
			}

			// Second derivative.
			if(SECOND_DER)
			{
				const hkReal	factor = -8 * hkMath::pow<2>(k) * 16;
				const hkReal	d6 = 6 * d;
				hkReal*			dOut = der2;
				for(int i=0; i<N; ++i)
				{
					for(int j=0; j<=i; ++j)
					{
						if(i == j)
							*dOut++ += factor * (2 * g[i] * f[i] + d * (k - 6 * f[i] * f[i]));
						else
							*dOut++ += factor * (g[j] * f[i] + g[i] * f[j] - d6 * f[i] * f[j]);
					}
				}
			}
		}
	}
	return value;
}

//
template <int N>
inline hkReal	hkgpSimplexNoise::fBm(const hkVector4& x, int octaves, hkReal offset, hkReal persistence)
{
	hkReal sum = 0;
	hkReal a = 1;
	for(int i=0, o=1; i<octaves; ++i, o<<=1, a*=persistence)
	{
		hkVector4		p; p.setMul(x, hkSimdReal::fromInt32(o));
		const hkReal	n = hkgpSimplexNoise::evaluate<N,false,false>(&p(0));
		sum += hkMath::square(offset - hkMath::abs(n)) * a;
	}
	return sum;		
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
