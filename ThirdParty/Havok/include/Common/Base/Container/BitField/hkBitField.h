/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKBASE_HKBITFIELD_H
#define HKBASE_HKBITFIELD_H

extern HK_EXPORT_COMMON const hkClass hkBitFieldClass;

#include <Common/Base/Container/LocalArray/hkLocalArray.h>

/// Loop type for bit field 
struct HK_EXPORT_COMMON hkBitFieldLoop
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_ARRAY, hkBitFieldLoop);

	enum Dir
	{
		ASCENDING,
		DESCENDING,
	};
};

/// Bit type for bit field
struct HK_EXPORT_COMMON hkBitFieldBit
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_ARRAY, hkBitFieldBit);

	enum Type
	{
		CLEARED	= 0,
		SET		= 1,
	};
};

/// A bit-field storage type where all bits are represented
template <class Storage>
struct hkBitFieldStorage
{
	public:

		HK_DECLARE_PLACEMENT_ALLOCATOR();
		HK_DECLARE_REFLECTION();

	public:

		/// Constructor
		HK_FORCE_INLINE hkBitFieldStorage()
		:	m_words(0)
		,	m_numBits(0)
		{}

		/// Constructor
		HK_FORCE_INLINE hkBitFieldStorage(int startBit, int numBits)
		:	m_words((numBits + 31 ) >> 5)
		,	m_numBits(numBits)
		{
			m_words.setSize((numBits + 31 ) >> 5);
		}

		/// Constructor
		HK_FORCE_INLINE hkBitFieldStorage(hkUint32* ptr, int startBit, int numBits)
		:	m_words(ptr, (numBits + 31 ) >> 5, (numBits + 31 ) >> 5)
		,	m_numBits(numBits)
		{}

		/// Serialization constructor
		hkBitFieldStorage(hkFinishLoadedObjectFlag flag)
		:	m_words(flag)
		{}

		/// Gets / sets the first bit represented in the storage
		HK_FORCE_INLINE int getOffset() const	{	return 0;	}
		HK_FORCE_INLINE void setOffset(int o)	{}

		/// Debug check to make sure bit is in range
		HK_FORCE_INLINE bool isBitInRange( int index ) const { return index >=0 && index < m_numBits; }

		/// Returns the number of bits in the storage
		HK_FORCE_INLINE int getSize() const		{	return m_numBits;	}

		/// Resizes the storage
		HK_FORCE_INLINE void resize(int startBit, int numBits)
		{
			m_numBits = numBits;
			const int numWords = ((numBits + 31 ) >> 5);
			m_words.setSize(numWords);
		}

		/// Deallocates the storage
		HK_FORCE_INLINE void deallocate()
		{
			m_numBits = 0;
			m_words.clearAndDeallocate();
		}

		/// Clears the storage (but doesn't deallocate it)
		HK_FORCE_INLINE void clearStorage()
		{
			m_numBits = 0;
			m_words.clear();
		}

	public:

		Storage m_words;	///< Storage (in hkUint32 words).
		int m_numBits;		///< The number of valid bits
};

/// A bit-field storage type where the first m_offset bits are assumed to be 0 and thus not represented.
template <class Storage>
struct hkOffsetBitFieldStorage
{
	public:

		HK_DECLARE_PLACEMENT_ALLOCATOR();
		HK_DECLARE_REFLECTION();

	public:

		/// Constructor
		HK_FORCE_INLINE hkOffsetBitFieldStorage()
		:	m_words(0)
		,	m_offset(0)
		{}

		/// Constructor
		HK_FORCE_INLINE hkOffsetBitFieldStorage(int startBit, int numBits)
		:	m_words(((numBits + 31 ) >> 5) - (startBit >> 5))
		,	m_offset(startBit >> 5)
		{
			m_words.setSize(((numBits + 31 ) >> 5) - m_offset);
		}

		/// Constructor
		HK_FORCE_INLINE hkOffsetBitFieldStorage(hkUint32* ptr, int startBit, int numBits)
		:	m_words(ptr, ((numBits + 31 ) >> 5) - (startBit >> 5), ((numBits + 31 ) >> 5) - (startBit >> 5))
		,	m_offset(startBit >> 5)
		{}

		/// Serialization constructor
		hkOffsetBitFieldStorage(hkFinishLoadedObjectFlag flag)
		:	m_words(flag)
		{}

		/// Returns the first bit represented in the storage
		HK_FORCE_INLINE int getOffset() const	{	return m_offset;	}
		HK_FORCE_INLINE void setOffset(int o)	{	m_offset = o;		}
		
		/// Debug check to make sure bit is in range
		/// We don't have access to the bit offset or number of bits, but we can at least check the word index is valid.
		HK_FORCE_INLINE bool isBitInRange( int index ) const
		{ 
			const int wordIdx = (index >> 5) - getOffset();
			return (wordIdx >= 0) && (wordIdx < m_words.getSize()) ;
		}

		/// Returns the number of bits in the storage
		HK_FORCE_INLINE int getSize() const		{	return (m_offset + m_words.getSize()) << 5;	}

		/// Resizes the storage
		HK_FORCE_INLINE void resize(int startBit, int numBits)
		{
			m_offset = startBit >> 5;
			const int numWords = ((numBits + 31 ) >> 5) - m_offset;

			HK_ASSERT(0x9397fe0, (startBit <= numBits) && (numWords >= 0));
			m_words.setSize(numWords);
		}

		/// Deallocates the storage
		HK_FORCE_INLINE void deallocate()
		{
			m_offset = 0;
			m_words.clearAndDeallocate();
		}

		/// Clears the storage (but doesn't deallocate it)
		HK_FORCE_INLINE void clearStorage()
		{
			m_offset = 0;
			m_words.clear();
		}

	public:

		Storage m_words;	///< Storage (in hkUint32 words). The number of bits is always a multiple of words
		int m_offset;		///< Offset (in words) that will be decremented from all bit indices
};

/// Bit-field backed-up by an hkArray
typedef hkBitFieldStorage< hkArray<hkUint32> >				hkBitFieldArrayStorage;
typedef hkOffsetBitFieldStorage< hkArray<hkUint32> >		hkOffsetBitFieldArrayStorage;


/// Bit-field backed-up by a hkLocalArray
typedef hkBitFieldStorage< hkLocalArray<hkUint32> >			hkBitFieldLocalStorage;
typedef hkOffsetBitFieldStorage< hkLocalArray<hkUint32> >	hkOffsetBitFieldLocalStorage;

/// Bit-field backed-up by a hkInplaceArray
template <unsigned N>
struct hkBitFieldInplaceStorage : hkBitFieldStorage< hkInplaceArray<hkUint32, N> >
{
	/// Constructor
	HK_FORCE_INLINE hkBitFieldInplaceStorage(int startBit, int numBits)
	:	hkBitFieldStorage< hkInplaceArray<hkUint32, N> >(startBit, numBits)
	{}
};

struct hkBitFieldValue
{
	enum Initialized
	{
		ZERO = 0,	// implementation depends on the actual values of this enum
		ONE = 1
	};

	enum Uninitialized
	{
		UNINITIALIZED
	};
};

/// Bit-field taking a generic hkUint32 storage
template <class Storage>
class hkBitFieldBase
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_ARRAY, hkBitFieldBase );
		HK_DECLARE_REFLECTION();

	public:

		/// Construct a bit field of size 0.
		HK_FORCE_INLINE hkBitFieldBase();


		/// Construct a bit field of size numBits, with uninitialized values
		HK_FORCE_INLINE hkBitFieldBase(int numBits, hkBitFieldValue::Uninitialized);

		/// Construct a bit field of size numBits, with specified initial value
		HK_FORCE_INLINE hkBitFieldBase(int numBits, hkBitFieldValue::Initialized initialValue);

		/// Non copying initialization from an memory buffer.
		/// Note this does not copy but uses it in place.
		/// Care needs to be taken that the data pointer points to is valid for the scope
		/// of this bitField. Pointer will not be deallocated on destruction.
		HK_FORCE_INLINE hkBitFieldBase(hkUint32* ptr, int startBit, int numBits);

		/// Copy constructor
		HK_FORCE_INLINE hkBitFieldBase(const hkBitFieldBase& other);

		/// Conversion constructor
		template <class T>
		HK_FORCE_INLINE hkBitFieldBase(const hkBitFieldBase<T>& other);

		/// Serialization constructor
		hkBitFieldBase(hkFinishLoadedObjectFlag flag)
		:	m_storage(flag)
		{}

		/// Destructor.
		inline ~hkBitFieldBase();

	public:

		/// Set all the bits to the given value.
		HK_FORCE_INLINE void assignAll(int bitVal);

		/// Set all the bits to the given value
		template <int bitVal>
		HK_FORCE_INLINE void assignAll();

		/// Set all the bits between start and start+numBits-1 to the given value
		HK_FORCE_INLINE void assignRange(int startBit, int numBits, int bitVal);

		/// Get the number of bits the bit field is set to.
		HK_FORCE_INLINE int getSize() const;

		/// Returns the start bit
		HK_FORCE_INLINE int getStartBit() const;

		/// Returns (in the lowest bit position) the bit at the given index.
		HK_FORCE_INLINE int get(int index) const;

		/// Sets the bit at the given index to bitVal.
		HK_FORCE_INLINE void assign(int index, int bitVal);

		/// Sets the bit at the given index to 0.
		HK_FORCE_INLINE void clear(int index);

		/// Sets the bit at the given index to 1.
		HK_FORCE_INLINE void set(int index);

		/// Returns the number of words
		HK_FORCE_INLINE int getNumWords() const;

		/// Returns the word capacity
		HK_FORCE_INLINE int getWordsCapacity() const;

		/// Returns the word offset
		HK_FORCE_INLINE int getOffset() const;

		/// Returns the words buffer
		HK_FORCE_INLINE hkUint32* accessWords();
		HK_FORCE_INLINE const hkUint32* getWords() const;

	public:

		/// Sets this &= ~other
		template <class S>
		HK_FORCE_INLINE void andNot(const hkBitFieldBase<S>& other);

		/// Sets this = a & (~b)
		template <class S, class T>
		HK_FORCE_INLINE void setAndNot(const hkBitFieldBase<S>& a, const hkBitFieldBase<T>& b);

		/// Perform bit-wise or with another bit field.
		template <class S>
		HK_FORCE_INLINE void orWith(const hkBitFieldBase<S>& other);

		/// Sets this = a | b
		template <class S, class T>
		HK_FORCE_INLINE void setOr(const hkBitFieldBase<S>& a, const hkBitFieldBase<T>& b);

		/// Perform bit-wise and with another bit field.
		template <class S>
		HK_FORCE_INLINE void andWith(const hkBitFieldBase<S>& other);

		/// Sets this = a & b
		template <class S, class T>
		HK_FORCE_INLINE void setAnd(const hkBitFieldBase<S>& a, const hkBitFieldBase<T>& b);

		/// Perform bit-wise xor with another bit field.
		template <class S>
		HK_FORCE_INLINE void xorWith(const hkBitFieldBase<S>& other);

		/// Sets this = ~a
		template <class S>
		HK_FORCE_INLINE void setNot(const hkBitFieldBase<S>& other);

	public:

		/// Counts the bits that are 1.
		HK_FORCE_INLINE int bitCount() const;

		/// Counts the bits that are 1.
		HK_FORCE_INLINE int bitCount(int startBit, int numBits) const;

		/// Count the number of 1 bits
		static int HK_CALL countOnes(const hkUint32* words, int numBits);

		/// Returns true if any of the bits are set
		HK_FORCE_INLINE bool anyIsSet() const;

		/// Locates the first set bit. If all bits are 0, returns -1
		HK_FORCE_INLINE int findFirstSet() const;

		/// Locates the last set bit. If all bits are 0, returns -1
		HK_FORCE_INLINE int findLastSet() const;

	public:

		/// Copies other into this (i.e. this = other)
		template <class S>
		HK_FORCE_INLINE void copy(const hkBitFieldBase<S>& other);

		/// Copies from other into this
		HK_FORCE_INLINE void copy(const hkUint32* HK_RESTRICT wOther, int otherOffset, int otherNumWords);

		/// Resize the bit field
		HK_FORCE_INLINE void resize(int startBit, int numBits);

		/// Resize the bit field, new elements initialized with 'value'.
		void setSizeAndFill(int startBit, int numBits, int fillValue);

		/// Resize the bit field, new elements initialized with 'value'.
		/// Returns HK_FAILURE if memory allocation failed, HK_SUCCESS otherwise.
		hkResult trySetSize(int startBit, int numBits, int fillValue);

		/// Deallocates the bit-field storage
		HK_FORCE_INLINE void deallocate();

		/// Clear the bit-field storage
		HK_FORCE_INLINE void clearStorage();

		/// Gets the number of words required to store the specified number of bits
		static HK_FORCE_INLINE int HK_CALL getNumWordsRequired(int numBits);

		/// Assignment operator.
		template <class S>
		HK_FORCE_INLINE void operator = ( const hkBitFieldBase<S>& bitField );

	public:

		/// Executes the given functor for each bit == t in the range {bitStart... bitStart + numBits - 1} inclusive.
		/// If the number of bits is negative, forEach will iterate up to the end of the bit-field.
		template <hkBitFieldLoop::Dir d, hkBitFieldBit::Type t, typename FUN>
		HK_FORCE_INLINE void forEach(int bitStart, int numBits, FUN& f) const;

		/// Executes the given functor for each bit set
		template <typename FUN>
		HK_FORCE_INLINE void forEachBitSet(FUN& f) const;

		// DEPRECATED. Iterator for an hkBitFieldBase - avoid variable shifts by storing the current word,
		// and shifting that by one bit each time the iterator is incremented.
		class Iterator
		{
			public:

				HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_ARRAY, hkBitFieldBase::Iterator );

				HK_FORCE_INLINE Iterator(const hkBitFieldBase& bf);

				/// Returns whether the current iterator is still valid.
				HK_FORCE_INLINE bool isValid( const hkBitFieldBase& bf ) const;

				/// Move the iterator to the next bit.
				HK_FORCE_INLINE void getNext( const hkBitFieldBase& bf) HK_RESTRICT;

				/// Returns the value of the current bit.
				HK_FORCE_INLINE bool isCurrentBitSet() const;

				/// Returns the index of the current bit.
				HK_FORCE_INLINE int getCurrentBit() const;
			
				/// Sets the index of the current bit.
				HK_FORCE_INLINE void setPosition( const hkBitFieldBase& bf, int index);
			
			protected:

				/// The current word from the bitfield, shifted down so that the active bit is the bottom one.
				hkUint32 m_currentWord;

				/// The index of the current bit.
				int m_currentBitIndex;
		};

	private:
		
		// Fills the bits that are beyond m_numBits but within m_numWords
		void fillUnusedBits(int fillValue);

	protected:

		Storage m_storage;		///< The bits storage
};

/// Bit-field backed-up by an hkArray
class hkBitField : public hkBitFieldBase< hkBitFieldArrayStorage >
{
	//+version(2)
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_ARRAY, hkBitField );
		HK_DECLARE_REFLECTION();

		typedef hkBitFieldBase< hkBitFieldArrayStorage > Base;

	public:

		HK_FORCE_INLINE hkBitField()														:	Base()											{}
		HK_FORCE_INLINE hkBitField(int numBits, hkBitFieldValue::Uninitialized)				:	Base(numBits, hkBitFieldValue::UNINITIALIZED)	{}
		HK_FORCE_INLINE hkBitField(int numBits, hkBitFieldValue::Initialized initialValue)	:	Base(numBits, initialValue)						{}
		HK_FORCE_INLINE hkBitField(hkUint32* ptr, int startBit, int numBits)				:	Base(ptr, startBit, numBits)					{}
		HK_FORCE_INLINE hkBitField(const hkBitField& other)									:	Base(other)										{}					
		template <class T>
		HK_FORCE_INLINE hkBitField(const hkBitFieldBase<T>& other)							:	Base(other)										{}
		hkBitField(hkFinishLoadedObjectFlag flag)											:	Base(flag)										{}
};

/// Offset bit-field backed-up by an hkArray
class hkOffsetBitField : public hkBitFieldBase< hkOffsetBitFieldArrayStorage >
{
public:

	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_ARRAY, hkOffsetBitField );
	HK_DECLARE_REFLECTION();

	typedef hkBitFieldBase< hkOffsetBitFieldArrayStorage > Base;

public:

	HK_FORCE_INLINE hkOffsetBitField()															:	Base()											{}
	HK_FORCE_INLINE hkOffsetBitField(int numBits, hkBitFieldValue::Uninitialized)				:	Base(numBits, hkBitFieldValue::UNINITIALIZED)	{}
	HK_FORCE_INLINE hkOffsetBitField(int numBits, hkBitFieldValue::Initialized initialValue)	:	Base(numBits, initialValue)						{}
	HK_FORCE_INLINE hkOffsetBitField(int startBit, int numBits, hkBitFieldValue::Uninitialized)	:	Base(numBits - ((startBit >> 5) << 5), hkBitFieldValue::UNINITIALIZED)
	{
		// the call to the Base constructor above ensures that an actual resize of the underlying storage doesn't happen in this call to resize
		resize(startBit, numBits);
	}
	HK_FORCE_INLINE hkOffsetBitField(int startBit, int numBits, hkBitFieldValue::Initialized initialValue)	:	Base(numBits - ((startBit >> 5) << 5), initialValue)
	{
		// the call to the Base constructor above ensures that an actual resize of the underlying storage doesn't happen in this call to resize
		resize(startBit, numBits);
	}
	HK_FORCE_INLINE hkOffsetBitField(hkUint32* ptr, int startBit, int numBits)					:	Base(ptr, startBit, numBits)					{}
	HK_FORCE_INLINE hkOffsetBitField(const hkOffsetBitField& other)								:	Base(other)										{}					
	template <class T>
	HK_FORCE_INLINE hkOffsetBitField(const hkBitFieldBase<T>& other)							:	Base(other)										{}
	hkOffsetBitField(hkFinishLoadedObjectFlag flag)												:	Base(flag)										{}
};

/// Offset bit-field backed-up by an hkLocalArray
class hkOffsetBitFieldLocal : public hkBitFieldBase< hkOffsetBitFieldLocalStorage >
{
public:

	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_ARRAY, hkOffsetBitFieldLocal );

	typedef hkBitFieldBase< hkOffsetBitFieldLocalStorage > Base;

public:

	HK_FORCE_INLINE hkOffsetBitFieldLocal()																		:	Base()											{}
	HK_FORCE_INLINE hkOffsetBitFieldLocal(int numBits, hkBitFieldValue::Uninitialized)							:	Base(numBits, hkBitFieldValue::UNINITIALIZED)	{}
	HK_FORCE_INLINE hkOffsetBitFieldLocal(int numBits, hkBitFieldValue::Initialized initialValue)				:	Base(numBits, initialValue)						{}
	HK_FORCE_INLINE hkOffsetBitFieldLocal(int startBit, int numBits, hkBitFieldValue::Uninitialized)			:	Base(numBits - ((startBit >> 5) << 5), hkBitFieldValue::UNINITIALIZED)
	{
		// the call to the Base constructor above ensures that an actual resize of the underlying storage doesn't happen in this call to resize
		resize(startBit, numBits);
	}
	HK_FORCE_INLINE hkOffsetBitFieldLocal(int startBit, int numBits, hkBitFieldValue::Initialized initialValue)	:	Base(numBits - ((startBit >> 5) << 5), initialValue)
	{
		// the call to the Base constructor above ensures that an actual resize of the underlying storage doesn't happen in this call to resize
		resize(startBit, numBits);
	}
	HK_FORCE_INLINE hkOffsetBitFieldLocal(const hkOffsetBitField& other)										:	Base(other)										{}					
	template <class T>
	HK_FORCE_INLINE hkOffsetBitFieldLocal(const hkBitFieldBase<T>& other)										:	Base(other)										{}
};

/// Bit-field backed-up by a hkLocalArray
typedef hkBitFieldBase< hkBitFieldLocalStorage >		hkLocalBitField;

/// Bit-field backed-up by a hkInplaceArray
template <int NBITS>
class hkInplaceBitField : public hkBitFieldBase< hkBitFieldInplaceStorage<(NBITS+31)/32> >
{
	public:

		enum { NUM_INT32 = (NBITS+31)/32 };

		/// Constructor
		hkInplaceBitField()
		:	hkBitFieldBase< hkBitFieldInplaceStorage<NUM_INT32> >(NBITS, hkBitFieldValue::ZERO)
		{}
};

#include <Common/Base/Container/BitField/hkBitField.inl>

#endif // HKBASE_HKBITFIELD_H

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
