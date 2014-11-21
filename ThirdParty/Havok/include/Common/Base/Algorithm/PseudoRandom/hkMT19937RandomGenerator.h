/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_MATH_MT19937RANDOMGENERATOR_H
#define HK_MATH_MT19937RANDOMGENERATOR_H

/// This class implements a simple Mersenne Twister pseudo-random number generator.
/// Specifically this implements the Mersenne Twister 19937 with 32-bit word length.
/// It generates random values approximately uniformely distributed in the interval [0, 2^32-1].
/// It has a very long period of randomness, and it has very well distributed over the interval.
/// This is a high quality random number generator and thus a bit more expensive than the simple 
/// hkPseudoRandomGenerator.
/// Depending on what operation is performed on the returned value, the uniform distribution property
/// could be lost. Specifically the rand()%X operation to crop the interval between 0 and X-1 _doesn't_
/// preserve the uniform distribution.
class hkMT19937RandomGenerator
{
	public:
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, hkMT19937RandomGenerator);

		/// The random engine will not be usable until initialize is called with a given seed.
		hkMT19937RandomGenerator();

		/// Destructor to cleanup the state.
		~hkMT19937RandomGenerator();

		/// Sets the seed and initializes the engine (effectively resetting the generator).
		/// This is a relatively expensive process, the status of the generator is fully initialized and
		/// reinitialized when exhausted during generation. In the case of the MT19937 generator the status 
		/// is basically 624 32 bit words.
		void initialize(hkUint32 seed);

		/// Gets a new random value (thus updating the state of the generator).
		hkUint32 getRand();

	protected:
		/// Every 624 random numbers, this MT generator needs to regenerate the state numbers.
		void generateNumbers();

		hkUint16 m_index;
		hkUint32* m_state;

	private:
		// Hidden constructors and operators.
		hkMT19937RandomGenerator(const hkMT19937RandomGenerator& rhs);
		hkMT19937RandomGenerator& operator=(const hkMT19937RandomGenerator& rhs);
};

#endif // HK_MATH_MT19937RANDOMGENERATOR_H

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
