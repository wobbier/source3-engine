/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_SERIALIZE_CONTENT_PREDICATE_H
#define HK_SERIALIZE_CONTENT_PREDICATE_H


/// This class represents a predicate that will be applied to data being serialized.
/// This is used in order to be able to peek at the content of a file without having
/// deserialize its content.
/// A predicate is a function matching the prototype: "bool pred(hkVariant obj)" and
/// which returns true if the predicate is valid for obj, false otherwise.
/// The predicate functions are registered through static constructors and the lists
/// are merged on DLL init through mergePredicateList().
class hkContentPredicate
{
public:
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SERIALIZE, hkContentPredicate);

	// This enum must be complete (no holes). Don't change the values since
	// this would break all existing assets.
	enum PredicateIdEnum
	{
		NO_PREDICATE = 0,

		// Some placeholder entries that can be used by code external to Havok
		USER_PREDICATE_1 = 1,
		USER_PREDICATE_2 = 2,
		USER_PREDICATE_3 = 3,
		USER_PREDICATE_4 = 4,
		USER_PREDICATE_5 = 5,
		USER_PREDICATE_6 = 6,
		USER_PREDICATE_7 = 7,
		USER_PREDICATE_8 = 8,
		USER_PREDICATE_9 = 9,
		USER_PREDICATE_10 = 10,
		USER_PREDICATE_11 = 11,
		USER_PREDICATE_12 = 12,
		USER_PREDICATE_13 = 13,
		USER_PREDICATE_14 = 14,
		USER_PREDICATE_15 = 15,
		USER_PREDICATE_16 = 16,
		USER_PREDICATE_17 = 17,
		USER_PREDICATE_18 = 18,
		USER_PREDICATE_19 = 19,

		// Havok internal predicates
		HAS_ROOT_LEVEL_CONTAINER = 20,

		// If you add a predicate ID here, please do it first on the Head to avoid having two different branches
		// using the same ID for different predicates.

		MAX_PREDICATE_ID
	};

	// At most 2^16 predicates.
	HK_COMPILE_TIME_ASSERT(MAX_PREDICATE_ID <= 0xFFFF);

	typedef hkEnum<PredicateIdEnum, hkUint16> PredicateId;
	typedef bool (*PredicateFunctionType)(hkVariant obj);

	/// Creating a hkContentPredicate registers it in the static linked list. This should only be called through
	/// the HK_REGISTER_FILE_PREDICATE macro. The predicateName is purely cosmetic and is used to generate
	/// human-readable comments in XML files.
	hkContentPredicate(PredicateId id, const char* predicateName, PredicateFunctionType func);

	/// Returns the head of the static linked list of predicates
	static hkContentPredicate* getListHead() { return m_head; }

	/// Performs a linear search through the static linked list for a specific predicate.
	static hkContentPredicate* findPredicate(PredicateId id);
	static hkContentPredicate* findPredicate(hkUint16 id) { return findPredicate(PredicateId(static_cast<PredicateIdEnum>(id))); }

	/// Merges the elements from otherListHead into this static list.
	static void mergePredicateList(hkContentPredicate* otherListHead);

	/// Applies the predicate function to v and returns the result.
	bool applyPredicate(hkVariant v) const { return m_predicate(v); }

	/// Get the next predicate in the list.
	hkContentPredicate* getNext() const { return m_next; }

	/// Get the ID of this predicate.
	PredicateId getId() const { return m_id; }

	/// Get the name of this predicate.
	const char* getName() const { return m_predicateName; }

private:

	PredicateId m_id;
	const char* m_predicateName;
	PredicateFunctionType m_predicate;
	hkContentPredicate* m_next;

	static hkContentPredicate* m_head;
};

/// Macro used to register a predicate. It should be placed in a .cpp file.
/// The first argument is an ID from the PredicateIdEnum enum and the second is the name of a C++ function to be used as predicate.
#define HK_REGISTER_FILE_PREDICATE(ID, PREDICATE_FUNCTION) \
	static const hkContentPredicate register_ ## PREDICATE_FUNCTION(hkContentPredicate::ID, #PREDICATE_FUNCTION, &PREDICATE_FUNCTION)

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
