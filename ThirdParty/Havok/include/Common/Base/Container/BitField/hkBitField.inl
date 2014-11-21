/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

//
//	Constructor

template <class Storage>
HK_FORCE_INLINE hkBitFieldBase<Storage>::hkBitFieldBase()
:	m_storage()
{}

//
//	Constructor

template <class Storage>
HK_FORCE_INLINE hkBitFieldBase<Storage>::hkBitFieldBase( int numBits, hkBitFieldValue::Uninitialized )
:	m_storage(0, numBits)
{}

//
//	Constructor

template <class Storage>
HK_FORCE_INLINE hkBitFieldBase<Storage>::hkBitFieldBase( int numBits, hkBitFieldValue::Initialized initialValue )
	:	m_storage(0, numBits)
{
	assignAll(initialValue);
}

//
//	Constructor

template <class Storage>
HK_FORCE_INLINE hkBitFieldBase<Storage>::hkBitFieldBase(hkUint32* ptr, int startBit, int numBits)
:	m_storage(ptr, startBit, numBits)
{}

//
//	Copy constructor

template <class Storage>
HK_FORCE_INLINE hkBitFieldBase<Storage>::hkBitFieldBase(const hkBitFieldBase& other)
:	m_storage(other.getStartBit(), other.getSize())
{
	copy(other);
}

//
//	Conversion constructor

template <class Storage>
template <class T>
HK_FORCE_INLINE hkBitFieldBase<Storage>::hkBitFieldBase(const hkBitFieldBase<T>& other)
:	m_storage(other.getStartBit(), other.getSize())
{
	copy(other);
}

//
//	Destructor

template <class Storage>
inline hkBitFieldBase<Storage>::~hkBitFieldBase()
{}

//
//	Set all the bits to the given value.

template <class Storage>
HK_FORCE_INLINE void hkBitFieldBase<Storage>::assignAll(int bitVal)
{
	HK_ASSERT( 0xa59289bb, bitVal >= 0 && bitVal <= 1 );
	hkString::memSet4(m_storage.m_words.begin(), -bitVal, m_storage.m_words.getSize());
}

//
//	Set all the bits to the given value

template <class Storage>
template <int bitVal>
HK_FORCE_INLINE void hkBitFieldBase<Storage>::assignAll()
{
	hkString::memSet4(m_storage.m_words.begin(), -bitVal, m_storage.m_words.getSize());
}

//
//	Set all the bits between start and start+numBits-1 to the given value

template <class Storage>
HK_FORCE_INLINE void hkBitFieldBase<Storage>::assignRange(int startBit, int numBits, int bitVal)
{
	HK_ASSERT(0x59d3c48a, m_storage.isBitInRange(startBit) );
	HK_ASSERT(0x59d3c48b, (numBits == 0) || m_storage.isBitInRange(startBit + numBits - 1) );

	const int endBit	= startBit + numBits;
	const int sWord		= (startBit >> 5) - m_storage.getOffset();
	const int eWord		= (endBit >> 5) - m_storage.getOffset();
	const int sMask		= (-1 << (startBit & 31));
	const int eMask		= ~(-1 << (endBit & 31));
	const hkUint32 c	= (hkUint32)-bitVal;

	hkUint32* HK_RESTRICT words = m_storage.m_words.begin();
	if ( sWord != eWord )
	{
		words[sWord]		= (words[sWord] & (~sMask)) | (c & sMask);
		if ( eMask )
		{
			words[eWord]	= (words[eWord] & (~eMask)) | (c & eMask);
		}

		hkString::memSet4(&words[sWord + 1], -bitVal, eWord - sWord - 1);
	}
	else
	{
		const int mask = sMask & eMask;
		if ( mask )
		{
			words[sWord]	= (words[sWord] & (~mask)) | (c & mask);
		}
	}
}

//
//	Returns the number of bits

template <class Storage>
HK_FORCE_INLINE int hkBitFieldBase<Storage>::getSize() const
{
	return m_storage.getSize();
}

//
//	Returns the start bit

template <class Storage>
HK_FORCE_INLINE int hkBitFieldBase<Storage>::getStartBit() const
{
	return m_storage.getOffset() << 5;
}

//
//	Returns (in the lowest bit position) the bit at the given index.

template <class Storage>
HK_FORCE_INLINE int hkBitFieldBase<Storage>::get(int index) const
{
	HK_ASSERT(0x5c19b563, m_storage.isBitInRange(index) );
	const int wordIdx = (index >> 5) - m_storage.getOffset();
	return ((m_storage.m_words[wordIdx] >> (index & 31)) & 1);
}

//
//	Set the bit at the given index to 1.

template <class Storage>
HK_FORCE_INLINE void hkBitFieldBase<Storage>::assign(int index, int bitVal)
{
	HK_ASSERT(0x59d3c48a, m_storage.isBitInRange(index) );
	const int wordIdx	= (index >> 5) - m_storage.getOffset();
	const hkUint32 mask = 1 << (index & 31);
	const int v			= -bitVal;

	HK_ASSERT(0x33723f73, (bitVal >= 0) && (bitVal <= 1));
	m_storage.m_words[wordIdx] = (m_storage.m_words[wordIdx] & (~mask)) | (mask & v);
}

//
//	Sets the bit at the given index to 1.

template <class Storage>
HK_FORCE_INLINE void hkBitFieldBase<Storage>::set(int index)
{
	HK_ASSERT(0x149f6efb, m_storage.isBitInRange(index) );
	const int wordIdx = (index >> 5) - m_storage.getOffset();
	m_storage.m_words[wordIdx] |= (1 << (index & 31));
}

//
//	Sets the bit at the given index to 0.

template <class Storage>
HK_FORCE_INLINE void hkBitFieldBase<Storage>::clear(int index)
{
	HK_ASSERT(0x59d3c48a, m_storage.isBitInRange(index) );
	const int wordIdx = (index >> 5) - m_storage.getOffset();
	m_storage.m_words[wordIdx] &= ~(1 << (index & 31));	
}

//
//	Utility functions

namespace hkBitFieldImpl
{
	// Operators
	static HK_FORCE_INLINE hkUint32 HK_CALL	op_and_not	(hkUint32 a, hkUint32 b)	{	return a & (~b);	}
	static HK_FORCE_INLINE hkUint32 HK_CALL	op_and		(hkUint32 a, hkUint32 b)	{	return a & b;		}
	static HK_FORCE_INLINE hkUint32 HK_CALL	op_xor		(hkUint32 a, hkUint32 b)	{	return a ^ b;		}
	static HK_FORCE_INLINE hkUint32 HK_CALL	op_or		(hkUint32 a, hkUint32 b)	{	return a | b;		}
	static HK_FORCE_INLINE hkUint32 HK_CALL op_not_b	(hkUint32 a, hkUint32 b)	{	return ~b;			}

	// Generic inplace operation on two bit-fields, i.e. ret = (ret) op (a)
	template <class T, class U, class Op>
	static HK_FORCE_INLINE void HK_CALL inplaceBitwiseOp(hkBitFieldBase<U>& ret, const hkBitFieldBase<T>& a, Op op)
	{
		const int deltaOffset = a.getOffset() - ret.getOffset();
		HK_ASSERT(0xb19c4ba, (deltaOffset >= 0) && (a.getNumWords() <= ret.getNumWords()));

		hkUint32* HK_RESTRICT		wThis	= &ret.accessWords()[deltaOffset];
		const hkUint32* HK_RESTRICT wOther	= a.getWords();

		int len = a.getNumWords() - a.getOffset();
		while ( len-- )
		{
			wThis[len] = op(wThis[len], wOther[len]);
		}
	}

	// Generic operation on two bit-fields, i.e. ret = (a) op (b)
	template <class S, class T, class U, class Op>
	static HK_FORCE_INLINE void HK_CALL bitwiseOp(hkBitFieldBase<U>& ret, const hkBitFieldBase<S>& a, const hkBitFieldBase<T>& b, Op op)
	{
		// Start indices
		const int st	= ret.getOffset();
		const int sa	= a.getOffset();
		const int sb	= b.getOffset();
		const int s		= hkMath::max2(hkMath::max2(sa, sb), st);

		// End index
		const int e	= hkMath::min2(hkMath::min2(a.getNumWords(), b.getNumWords()), ret.getNumWords());
		int	len		= e - s;

		// Run operation
		hkUint32* HK_RESTRICT		wThis	= &ret.accessWords()[s - st];
		const hkUint32* HK_RESTRICT wA		= &a.getWords()[s - sa];
		const hkUint32* HK_RESTRICT wB		= &b.getWords()[s - sb];
		HK_ASSERT(0x35490ef6, len >= 0);
		while ( len-- )
		{
			wThis[len] = op(wA[len], wB[len]);
		}
	}
}

//
//	Sets this &= ~other

template <class Storage>
template <class S>
HK_FORCE_INLINE void hkBitFieldBase<Storage>::andNot(const hkBitFieldBase<S>& other)
{
	hkBitFieldImpl::inplaceBitwiseOp(*this, other, hkBitFieldImpl::op_and_not);
}

//
//	Sets this = a & (~b)

template <class Storage>
template <class S, class T>
HK_FORCE_INLINE void hkBitFieldBase<Storage>::setAndNot(const hkBitFieldBase<S>& a, const hkBitFieldBase<T>& b)
{
	hkBitFieldImpl::bitwiseOp(*this, a, b, hkBitFieldImpl::op_and_not);
}

//
//	Sets this |= other

template <class Storage>
template <class S>
HK_FORCE_INLINE void hkBitFieldBase<Storage>::orWith(const hkBitFieldBase<S>& other)
{
	hkBitFieldImpl::inplaceBitwiseOp(*this, other, hkBitFieldImpl::op_or);
}

//
//	Sets this = a | b

template <class Storage>
template <class S, class T>
HK_FORCE_INLINE void hkBitFieldBase<Storage>::setOr(const hkBitFieldBase<S>& a, const hkBitFieldBase<T>& b)
{
	hkBitFieldImpl::bitwiseOp(*this, a, b, hkBitFieldImpl::op_or);
}

//
//	Sets this &= other

template <class Storage>
template <class S>
HK_FORCE_INLINE void hkBitFieldBase<Storage>::andWith(const hkBitFieldBase<S>& other)
{
	hkBitFieldImpl::inplaceBitwiseOp(*this, other, hkBitFieldImpl::op_and);
}

//
//	Sets this = a & b

template <class Storage>
template <class S, class T>
HK_FORCE_INLINE void hkBitFieldBase<Storage>::setAnd(const hkBitFieldBase<S>& a, const hkBitFieldBase<T>& b)
{
	hkBitFieldImpl::bitwiseOp(*this, a, b, hkBitFieldImpl::op_and);
}

//
//	Sets this ^= other

template <class Storage>
template <class S>
HK_FORCE_INLINE void hkBitFieldBase<Storage>::xorWith(const hkBitFieldBase<S>& other)
{
	hkBitFieldImpl::inplaceBitwiseOp(*this, other, hkBitFieldImpl::op_xor);
}

//
//	Sets this = ~a

template <class Storage>
template <class S>
HK_FORCE_INLINE void hkBitFieldBase<Storage>::setNot(const hkBitFieldBase<S>& a)
{
	hkBitFieldImpl::inplaceBitwiseOp(*this, a, hkBitFieldImpl::op_not_b);
}

//
//	Returns the number of words

template <class Storage>
HK_FORCE_INLINE int hkBitFieldBase<Storage>::getNumWords() const
{
	return m_storage.getOffset() + m_storage.m_words.getSize();
}

//
//	Returns the word capacity

template <class Storage>
HK_FORCE_INLINE int hkBitFieldBase<Storage>::getWordsCapacity() const
{
	return m_storage.getOffset() + m_storage.m_words.getCapacity();
}

//
//	Returns the word offset

template <class Storage>
HK_FORCE_INLINE int hkBitFieldBase<Storage>::getOffset() const
{
	return m_storage.getOffset();
}

//
//	Returns the words buffer

template <class Storage>
HK_FORCE_INLINE hkUint32* hkBitFieldBase<Storage>::accessWords()
{
	return m_storage.m_words.begin();
}

//
//	Returns the words buffer

template <class Storage>
HK_FORCE_INLINE const hkUint32* hkBitFieldBase<Storage>::getWords() const
{
	return m_storage.m_words.begin();
}

//
//	Returns the number of bits set

template <class Storage>
HK_FORCE_INLINE int hkBitFieldBase<Storage>::bitCount() const
{
	int count = 0;
	const hkUint32* HK_RESTRICT words = m_storage.m_words.begin();
	const int numWords	= m_storage.m_words.getSize();
	const int bitEnd	= getSize() - 1;
	hkUint32 endMask	= (~(-1 << (bitEnd & 31)) << 1) | 1;

	for (int ei = numWords - 1; ei >= 0; ei--, endMask = (hkUint32)-1)
	{
		count += hkMath::countBitsSet(words[ei] & endMask);
	}

	return count;
}

//
//	Counts the bits that are 1.

template <class Storage>
HK_FORCE_INLINE int hkBitFieldBase<Storage>::bitCount(int bitStart, int numBits) const
{
	// Clamp to interval
	const int maxLen	= getSize();
	numBits				= hkMath::clamp(numBits, 0, maxLen);
	const int bitEnd	= hkMath::min2(bitStart + numBits, maxLen) - 1;
	bitStart			= hkMath::max2(getStartBit(), bitStart);

	int count = 0;
	if ( bitEnd >= bitStart )
	{
		const int offset = (bitStart >> 5);
		HK_ASSERT(0x79383bbf, offset >= m_storage.getOffset());
		const hkUint32* HK_RESTRICT words = &m_storage.m_words.begin()[offset - m_storage.getOffset()];
		
		// Compute masks
		const hkUint32 startMask	= (-1 << (bitStart & 31));
		const hkUint32 endMask		= (~(-1 << (bitEnd & 31)) << 1) | 1;

		const int last = (bitEnd >> 5) - offset;
		int k = 0, it = (~(last >> 31)) & 1;	// it = (last >= 0) ? 1 : 0
		hkUint32 mask = startMask;
		do
		{
			for (; k < last; k++, mask = (hkUint32)(-1))
			{
				count += hkMath::countBitsSet(words[k] & mask);
			}

			// Force another go for the last word
			mask &= endMask;	k = last - 1;
			words++;
		} while ( it-- );
	}

	return count;
}

//
//	Counts the number of bits set

template <class Storage>
int HK_CALL hkBitFieldBase<Storage>::countOnes(const hkUint32* words, int numBits)
{
	HK_ASSERT( 0xaf14ee56, numBits > 0 );
	int count = 0;
	const int numWords	= getNumWordsRequired(numBits);
	const int bitEnd	= numBits - 1;
	hkUint32 endMask	= (~(-1 << (bitEnd & 31)) << 1) | 1;

	for (int ei = numWords - 1; ei >= 0; ei--, endMask = (hkUint32)-1)
	{
		count += hkMath::countBitsSet(words[ei] & endMask);
	}

	return count;
}

//
//	Locates the first set bit. If all bits are 0, returns -1

template <class Storage>
HK_FORCE_INLINE int hkBitFieldBase<Storage>::findFirstSet() const
{
	const hkUint32* HK_RESTRICT words = m_storage.m_words.begin();
	const int numWords = m_storage.m_words.getSize();

	for (int k = 0; k < numWords - 1; k++)
	{
		if ( words[k] )
		{
			// Found a non zero word, get its first set bit
			return ((getOffset() + k) << 5) + hkMath::countTrailingZeros(words[k]);
		}
	}

	if ( numWords )
	{
		const int bitEnd		= getSize() - 1;
		const hkUint32 endMask	= (~(-1 << (bitEnd & 31)) << 1) | 1;
		const hkUint32 w		= words[numWords - 1] & endMask;

		if ( w )
		{
			// Found a non zero word, get its first set bit
			return ((getOffset() + (numWords - 1)) << 5) + hkMath::countTrailingZeros(w);
		}
	}

	// Nothing found!
	return -1;
}

//
//	Locates the last set bit. If all bits are 0, returns -1

template <class Storage>
HK_FORCE_INLINE int hkBitFieldBase<Storage>::findLastSet() const
{
	const hkUint32* HK_RESTRICT words = m_storage.m_words.begin();
	const int numWords	= m_storage.m_words.getSize();
	const int bitEnd	= getSize() - 1;
	hkUint32 endMask	= (~(-1 << (bitEnd & 31)) << 1) | 1;

	for (int k = numWords - 1; k >= 0; k--, endMask = (hkUint32)-1)
	{
		const hkUint32 w = endMask & words[k];
		if ( w )
		{
			// Found a non zero word, get its first set bit
			return ((getOffset() + k) << 5) + 31 - hkMath::countLeadingZeros(w);
		}
	}

	// Nothing found!
	return -1;
}

//
//	Returns true if any bits are set to 1

template <class Storage>
HK_FORCE_INLINE bool hkBitFieldBase<Storage>::anyIsSet() const
{
	const int bitEnd = getSize() - 1;
	hkUint32 endMask = (~(-1 << (bitEnd & 31)) << 1) | 1;

	for (int k = m_storage.m_words.getSize() - 1; k >= 0; k--, endMask = (hkUint32)-1)
	{
		if ( m_storage.m_words[k] & endMask )
		{
			return true;
		}
	}

	return false;
}

//
//	Deallocates the bit-field

template <class Storage>
HK_FORCE_INLINE void hkBitFieldBase<Storage>::deallocate()
{
	m_storage.deallocate();
}

template <class Storage>
HK_FORCE_INLINE void hkBitFieldBase<Storage>::clearStorage()
{
	m_storage.clearStorage();
}

//
//	Copies from other into this

template <class Storage>
HK_FORCE_INLINE void hkBitFieldBase<Storage>::copy(const hkUint32* HK_RESTRICT ptrOther, int otherOffset, int otherNumWords)
{
	// Start indices
	const int s0	= getOffset();
	const int s		= hkMath::max2(s0, otherOffset);

	// End index
	const int e		= hkMath::min2(getNumWords(), otherOffset + otherNumWords);
	const int len	= e - s;
	HK_ASSERT(0x2f685ddd, (len >= 0));

	// Copy
	hkUint32* HK_RESTRICT		wThis	= &accessWords()[s - s0];
	const hkUint32* HK_RESTRICT wOther	= &ptrOther[s - otherOffset];
	hkString::memCpy4(wThis, wOther, len);
}

//
//	Copies other into this (i.e. this = other)

template <class Storage>
template <class S>
HK_FORCE_INLINE void hkBitFieldBase<Storage>::copy(const hkBitFieldBase<S>& other)
{
	copy(other.getWords(), other.getOffset(), other.getNumWords() - other.getOffset());
}

//
//	Returns the number of words required to store the given number of bits

template <class Storage>
HK_FORCE_INLINE int HK_CALL hkBitFieldBase<Storage>::getNumWordsRequired(int numBits)
{
	return (numBits + 31) >> 5;
}

//
//	Resize the bit field, new elements initialized with 'value'.

template <class Storage>
HK_FORCE_INLINE void hkBitFieldBase<Storage>::resize(int startBit, int numBits)
{
	m_storage.resize(startBit, numBits);
}

//
//	Resize the bit field, new elements initialized with 'value'.

template <class Storage>
void hkBitFieldBase<Storage>::setSizeAndFill(int startBit, int numNewBits, int fillValue)
{
	HK_ASSERT( 0xa59289bc, fillValue >= 0 && fillValue <= 1 );
	const int numOrigBits = getSize();
	if( (numOrigBits > 0) && (numOrigBits < numNewBits) )
	{
		fillUnusedBits( fillValue );
	}

	resize(startBit, numNewBits);
	if ( numNewBits > numOrigBits )
	{
		assignRange(numOrigBits, numNewBits - numOrigBits, fillValue);
	}
}

//
//	Fills the bits that are beyond m_numBits but within m_numWords

template <class Storage>
void hkBitFieldBase<Storage>::fillUnusedBits(int fillValue)
{
	HK_ASSERT( 0xf25ad34b, getSize() > 0 );

	int arrayIndex = (getSize() - 1) >> 5;
	hkUint32& word = m_storage.m_words[arrayIndex];

	int usedBitsInLastWord = getSize() - (arrayIndex << 5);

	if( usedBitsInLastWord < 32 )
	{
		int a = 0xffffffff;
		a <<= usedBitsInLastWord;

		if( fillValue == 0 )
		{
			a = ~a;
			word &= a;
		}
		else
		{
			word |= a;
		}
	}
}

//
//	Resize the bit field, new elements initialized with 'value'.

template <class Storage>
hkResult hkBitFieldBase<Storage>::trySetSize(int startBit, int numBits, int fillValue)
{
	int numWords = ( numBits + 31 ) >> 5;
	hkResult reserveRes = m_storage.m_words.reserve(numWords);
	if (reserveRes != HK_SUCCESS)
	{
		return HK_FAILURE;
	}

	setSizeAndFill(startBit, numBits, fillValue);
	return HK_SUCCESS;
}

//
//	Assignment operator

template <class Storage>
template <class S>
HK_FORCE_INLINE void hkBitFieldBase<Storage>::operator = ( const hkBitFieldBase<S>& other )
{
	resize(other.getStartBit(), other.getSize());
	copy(other);
}

//
//	Name-space for partial template declarations

namespace hkBitFieldOps
{
	// Types for yes / no
	typedef hkUint8 TypeYes;
	typedef hkUint32 TypeNo;

	// Checks whether a type is a class
	template <typename T>
	struct IsClass
	{
		template <class S> static TypeYes	test(void(S::*)(void));
		template <class S> static TypeNo	test(...);
		enum	{	Value = (sizeof(test<T>(0)) == sizeof(TypeYes)),	};
	};

	// Checks whether a function returns int
	template <typename Fun, bool isClass> struct ReturnsInt{};
	template <typename Fun> struct ReturnsInt<Fun, true>
	{
		template <class C, typename Arg1>	static TypeYes	returnsInt(int (C::*)(Arg1));
		template <class C, typename Arg1>	static TypeYes	returnsInt(int (C::*)(Arg1) const);
		template <class C, typename Arg1>	static TypeYes	returnsInt(bool (C::*)(Arg1));
		template <class C, typename Arg1>	static TypeYes	returnsInt(bool (C::*)(Arg1) const);
		template <class C, typename Arg1>	static TypeYes	returnsInt(hkBool32 (C::*)(Arg1));
		template <class C, typename Arg1>	static TypeYes	returnsInt(hkBool32 (C::*)(Arg1) const);
		static TypeNo returnsInt(...);

		enum	{	Value = (sizeof(returnsInt(&Fun::operator())) == sizeof(TypeYes)),	};
	};

	// Returns either the given word or its negation, based on the given template parameter
	template <hkBitFieldBit::Type t> static HK_FORCE_INLINE hkUint32 HK_CALL wordToBits(hkUint32 word);
	template <> HK_FORCE_INLINE hkUint32 HK_CALL wordToBits<hkBitFieldBit::SET>(hkUint32 word)			{	return word;	}
	template <> HK_FORCE_INLINE hkUint32 HK_CALL wordToBits<hkBitFieldBit::CLEARED>(hkUint32 word)		{	return ~word;	}

	// Base template for ForEach
	template <hkBitFieldLoop::Dir d, bool CanAbortLoop, hkBitFieldBit::Type T, typename FUN>
	struct ForEach
	{};

	// Partial specialization: ASCENDING forEach
	template <hkBitFieldBit::Type T, typename FUN>
	struct ForEach<hkBitFieldLoop::ASCENDING, true, T, FUN>
	{
		static HK_FORCE_INLINE void HK_CALL execute(const hkUint32* HK_RESTRICT words, int bitStart, int bitEnd, FUN& f)
		{
			// Compute masks
			const hkUint32 startMask	= (-1 << (bitStart & 31));
			const hkUint32 endMask		= (~(-1 << (bitEnd & 31)) << 1) | 1;

			int offset = (bitStart >> 5);
			const int last = (bitEnd >> 5) - offset;
			int k = 0, it = (~(last >> 31)) & 1;	// it = (last >= 0) ? 1 : 0
			hkUint32 mask = startMask;
			do
			{
				for (; k < last; k++, mask = (hkUint32)(-1))
				{
					hkUint32 workingMask = mask;
					while ( wordToBits<T>(words[k]) & workingMask )
					{
						const int idx = hkMath::countTrailingZeros(wordToBits<T>(words[k]) & workingMask);
						workingMask &= (-1 << idx) << 1;	// Prevent shifting with 32
						const int bitIdx = ((offset + k) << 5) + idx;
						if ( !f(bitIdx) )
						{
							return;
						}
					}
				}

				// Force another go for the last word
				mask &= endMask;	k = last - 1;
				offset++;			words++;
			} while ( it-- );
		}
	};

	// Partial specialization: ASCENDING forEach
	template <hkBitFieldBit::Type T, typename FUN>
	struct ForEach<hkBitFieldLoop::ASCENDING, false, T, FUN>
	{
		static HK_FORCE_INLINE void HK_CALL execute(const hkUint32* HK_RESTRICT words, int bitStart, int bitEnd, FUN& f)
		{
			// Compute masks
			const hkUint32 startMask	= (-1 << (bitStart & 31));
			const hkUint32 endMask		= (~(-1 << (bitEnd & 31)) << 1) | 1;

			int offset = (bitStart >> 5);
			const int last = (bitEnd >> 5) - offset;
			int k = 0, it = (~(last >> 31)) & 1;	// it = (last >= 0) ? 1 : 0
			hkUint32 mask = startMask;
			do
			{
				for (; k < last; k++, mask = (hkUint32)(-1))
				{
					hkUint32 workingMask = mask;
					while ( wordToBits<T>(words[k]) & workingMask )
					{
						const int idx = hkMath::countTrailingZeros(wordToBits<T>(words[k]) & workingMask);
						workingMask &= (-1 << idx) << 1;	// Prevent shifting with 32
						const int bitIdx = ((offset + k) << 5) + idx;

						// Call functor
						f(bitIdx);
					}
				}

				// Force another go for the last word
				mask &= endMask;	k = last - 1;
				offset++;			words++;
			} while ( it-- );
		}
	};

	// Partial specialization: DESCENDING forEach
	template <hkBitFieldBit::Type T, typename FUN>
	struct ForEach<hkBitFieldLoop::DESCENDING, true, T, FUN>
	{
		static HK_FORCE_INLINE void HK_CALL execute(const hkUint32* HK_RESTRICT words, int bitStart, int bitEnd, FUN& f)
		{
			// Compute masks
			const hkUint32 startMask	= (-1 << (bitStart & 31));
			const hkUint32 endMask		= (~(-1 << (bitEnd & 31)) << 1) | 1;

			int offset = (bitStart >> 5);
			int k = (bitEnd >> 5) - offset, it = (~(k >> 31)) & 1;	// k = word length, it = (k >= 0) ? 1 : 0
			hkUint32 mask = endMask;
			do
			{
				for (; k > 0; k--, mask = (hkUint32)(-1))
				{
					hkUint32 workingMask = mask;
					while ( wordToBits<T>(words[k]) & workingMask )
					{
						const int idx = 31 - hkMath::countLeadingZeros(wordToBits<T>(words[k]) & workingMask);
						workingMask &= (1 << idx) - 1;

						const int bitIdx = ((offset + k) << 5) + idx;
						if ( !f(bitIdx) )
						{
							return;
						}
					}
				}

				// Force another go for the first word
				mask &= startMask;	k = 1;
				offset--;			words--;
			} while ( it-- );
		}
	};

	// Partial specialization: DESCENDING forEach
	template <hkBitFieldBit::Type T, typename FUN>
	struct ForEach<hkBitFieldLoop::DESCENDING, false, T, FUN>
	{
		static HK_FORCE_INLINE void HK_CALL execute(const hkUint32* HK_RESTRICT words, int bitStart, int bitEnd, FUN& f)
		{
			// Compute masks
			const hkUint32 startMask	= (-1 << (bitStart & 31));
			const hkUint32 endMask		= (~(-1 << (bitEnd & 31)) << 1) | 1;

			int offset = (bitStart >> 5);
			int k = (bitEnd >> 5) - offset, it = (~(k >> 31)) & 1;	// k = word length, it = (k >= 0) ? 1 : 0
			hkUint32 mask = endMask;
			do
			{
				for (; k > 0; k--, mask = (hkUint32)(-1))
				{
					hkUint32 workingMask = mask;
					while ( wordToBits<T>(words[k]) & workingMask )
					{
						const int idx = 31 - hkMath::countLeadingZeros(wordToBits<T>(words[k]) & workingMask);
						workingMask &= (1 << idx) - 1;

						const int bitIdx = ((offset + k) << 5) + idx;

						// Call functor
						f(bitIdx);
					}
				}

				// Force another go for the first word
				mask &= startMask;	k = 1;
				offset--;			words--;
			} while ( it-- );
		}
	};
}

//
//	Executes the given functor for each bit set in the range {bitStart... bitEnd} inclusive.

template <class Storage>
template <hkBitFieldLoop::Dir d, hkBitFieldBit::Type t, typename FUN>
HK_FORCE_INLINE void hkBitFieldBase<Storage>::forEach(int bitStart, int numBits, FUN& f) const
{
	// Clamp to interval
	const int maxLen	= getSize();
	numBits				= hkMath::clamp(numBits, 0, maxLen);
	const int bitEnd	= hkMath::min2(bitStart + numBits, maxLen) - 1;
	bitStart			= hkMath::max2(getStartBit(), bitStart);

	if ( bitEnd >= bitStart )
	{
		const int offset	= (bitStart >> 5);
		HK_ASSERT(0x79383bbf, offset >= m_storage.getOffset());
		const hkUint32* HK_RESTRICT words = &m_storage.m_words.begin()[offset - m_storage.getOffset()];
		const bool canAbort	= hkBitFieldOps::ReturnsInt<FUN, hkBitFieldOps::IsClass<FUN>::Value>::Value;
		hkBitFieldOps::ForEach<d, canAbort, t, FUN>::execute(words, bitStart, bitEnd, f);
	}	
}

//
//	Executes the given functor for each bit set

template <class Storage>
template <typename FUN>
HK_FORCE_INLINE void hkBitFieldBase<Storage>::forEachBitSet(FUN& f) const
{
	if ( m_storage.m_words.getSize() )
	{
		const bool canAbort = hkBitFieldOps::ReturnsInt<FUN, hkBitFieldOps::IsClass<FUN>::Value>::Value;
		hkBitFieldOps::ForEach<hkBitFieldLoop::ASCENDING, canAbort, hkBitFieldBit::SET, FUN>::execute(m_storage.m_words.begin(), getStartBit(), getSize() - 1, f);
	}
}

//
// hkBitFieldBase::Iterator
//

template <class Storage>
HK_FORCE_INLINE hkBitFieldBase<Storage>::Iterator::Iterator(const hkBitFieldBase& bf)
{
	m_currentBitIndex = 0;
	if (bf.getSize() > 0)
	{
		m_currentWord = bf.m_storage.m_words[0];
	}
	else
	{
		m_currentWord = 0;
	}
}

template <class Storage>
HK_FORCE_INLINE bool hkBitFieldBase<Storage>::Iterator::isValid( const hkBitFieldBase& bf ) const 
{
	return m_currentBitIndex < bf.getSize();
}

template <class Storage>
HK_FORCE_INLINE void hkBitFieldBase<Storage>::Iterator::getNext( const hkBitFieldBase& bf) HK_RESTRICT
{
	// Don't update m_currentBitIndex until we need it, to avoid a LHS
	int nextBit = m_currentBitIndex + 1;

	if ( (nextBit & 31) || nextBit >= bf.getSize() )
	{
		m_currentWord = m_currentWord >> 1;
	}
	else
	{
		m_currentWord = bf.m_storage.m_words[nextBit >> 5];
	}
	m_currentBitIndex = nextBit;
}

template <class Storage>
HK_FORCE_INLINE bool hkBitFieldBase<Storage>::Iterator::isCurrentBitSet() const
{
	return (m_currentWord & 0x1) != 0;
}

template <class Storage>
HK_FORCE_INLINE int hkBitFieldBase<Storage>::Iterator::getCurrentBit() const
{
	return m_currentBitIndex;
}

template <class Storage>
HK_FORCE_INLINE void hkBitFieldBase<Storage>::Iterator::setPosition( const hkBitFieldBase& bf, int index)
{
	m_currentBitIndex = index;
	int wordIndex = index >> 5;
	int wordShift = index & 31;
	hkUint32 word = ( index < bf.getSize() ) ? bf.m_storage.m_words[wordIndex] : 0;
	m_currentWord = word >> wordShift;
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
