/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_SERIALIZE_UTIL_H
#define HK_SERIALIZE_UTIL_H

#include <Common/Base/Types/hkHandle.h>
#include <Common/Serialize/Util/hkStructureLayout.h>
#include <Common/Serialize/Tagfile/hkTagfileWriter.h>
#include <Common/Serialize/Packfile/hkPackfileWriter.h>
#include <Common/Serialize/Resource/hkObjectResource.h>
#include <Common/Serialize/Serialize/hkContentPredicate.h>

class hkClass;
class hkDataObject;
class hkStreamReader;
class hkStreamWriter;
class hkClassNameRegistry;
class hkTypeInfoRegistry;

	/// Utility functions to load and save packfiles and tagfiles.
	/// See also hkNativePackfileUtils for inplace loading packfiles which do not
	/// require any versioning.
namespace hkSerializeUtil
{
		/// Error details class for loading packfile/tagfile.
	struct HK_EXPORT_COMMON ErrorDetails
	{
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_SERIALIZE, ErrorDetails );

			/// ErrorDetails constructor.
		ErrorDetails() : id(ERRORID_NONE) {}

			/// Error ids for loading packfile/tagfile.
		enum ErrorID
		{
				/// No errors reading from stream.
			ERRORID_NONE,
				/// Failed to read from stream.
			ERRORID_READ_FAILED,
				/// Unsupported file format.
			ERRORID_UNSUPPORTED_FORMAT,
				/// Packfile cannot be read on this platform.
			ERRORID_PACKFILE_PLATFORM,
				/// Versioning cannot be applied to loaded objects.
			ERRORID_VERSIONING_FAILED,
				/// Found object with members that cannot clean up memory when destroyed.
			ERRORID_NONHEAP_OBJECT,
				/// Stream was ok but some error in the data.
			ERRORID_LOAD_FAILED,
				/// The file contains deprecated format but hkFeature_serializeDeprecatedPre700() was not called
			ERRORID_DEPRECATED_NOT_INITIALIZED,
				/// Max error ID
			ERRORID_MAX_ID,

		};

			/// Logs an error inside the ErrorDetails.
			/// This function will not override the current error ID if it isn't ERRORID_NONE.
			/// The first error raised (the lowest level one) is always going to be the more interesting one.
		void raiseError( ErrorID i, const char* msg ) 
		{
			if(id == ERRORID_NONE)
			{
				id = i; 
				defaultMessage = msg; 
			}
		}

			/// Error id. Default is ErrorDetails::ERRORID_NONE.
		hkEnum<ErrorID, hkInt32> id;
			/// Detailed error message, if error id is not ErrorDetails::ERRORID_NONE.
		hkStringPtr defaultMessage;
	};

		/// Option bits for saving.
	enum SaveOptionBits
	{
		SAVE_DEFAULT					= 0x00,		///< All flags default to OFF; enable whichever are needed
		SAVE_TEXT_FORMAT				= 0x01,		///< Use text (usually XML) format; default is binary format if available. Packfiles are always written as binary.
		SAVE_SERIALIZE_IGNORED_MEMBERS	= 0x02,		///< Write members which are usually ignored; default is to skip SERIALIZE_IGNORED members.
		SAVE_WRITE_ATTRIBUTES			= 0x04,		///< Include extended attributes in metadata; default is to write minimum metadata.
		SAVE_CONCISE					= 0x08,		///< Doesn't provide any extra information which would make the file easier to interpret. E.g. additionally write hex floats as text comments.
	};
		/// Options for saving.
	struct HK_EXPORT_COMMON SaveOptions : public hkFlags<SaveOptionBits, int>
	{
		SaveOptions(SaveOptionBits b=SAVE_DEFAULT) : hkFlags<SaveOptionBits,int>(b) {}
		SaveOptions& useText(hkBool32 b) { useBinary(!b); return *this; }
		inline SaveOptions& useBinary(hkBool32 b);
		inline SaveOptions& useConcise(hkBool32 b);
	};

		/// Option bits for loading.
	enum LoadOptionBits
	{
		LOAD_DEFAULT			= 0x00,	///< All flags default to OFF, enable whichever are needed
		LOAD_FAIL_IF_VERSIONING	= 0x01,	///< Allows a way to skip versioning paths (if current version needs to be enforced)
		LOAD_FORCED = 0x02, ///< Force load.
	};
		/// Options for loading.
	struct HK_EXPORT_COMMON  LoadOptions : public hkFlags<LoadOptionBits, int>
	{
		public:
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(0,LoadOptions);
			LoadOptions(LoadOptionBits b=LOAD_DEFAULT) : hkFlags<LoadOptionBits,int>(b), m_classNameReg(HK_NULL), m_typeInfoReg(HK_NULL) {}
			LoadOptions& useClassNameRegistry(const hkClassNameRegistry* creg) { m_classNameReg = creg; return *this; }
			LoadOptions& useTypeInfoRegistry(const hkTypeInfoRegistry* treg) { m_typeInfoReg = treg; return *this; }

			const hkClassNameRegistry* getClassNameRegistry() const;
			const hkTypeInfoRegistry* getTypeInfoRegistry() const;

		protected:
			const hkClassNameRegistry* m_classNameReg;
			const hkTypeInfoRegistry* m_typeInfoReg;
	};


		/// Load serialized objects from stream and return pointer
		/// to hkResource object.
		/// To access hkResource objects you should call hkResource::getContents()
		/// or hkResource::getContentsWithRegistry() specifying type of top level
		/// object pointer you expect.
		/// hkResource is reference counted and users are responsible to
		/// remove reference when they do not need the hkResource content.
		/// The objects owned by hkResource are not reference counted.
		///
		/// Load serialized objects from stream and return pointer
		/// to hkResource object. If 'classReg' is HK_NULL the
		/// class name registry from hkBuiltinTypeRegistry is used instead.
		/// The function does additional check for the stream format, versioning and finishing steps.
		/// It will return HK_NULL if the checks failed. The error details are
		/// returned in 'detailsOut'.
		/// Usually you should use hkSerializeUtil::load().
		///
		/// See also hkNativePackfileUtils::load* for inplace loading.
	HK_EXPORT_COMMON hkResource* HK_CALL load( hkStreamReader* stream, ErrorDetails* detailsOut=HK_NULL, LoadOptions options=LOAD_DEFAULT );

		/// Load serialized objects from a file using name and return pointer
		/// to hkResource object.
		/// See hkSerializeUtil::load( hkStreamReader* sr ) for details.
	HK_EXPORT_COMMON hkResource* HK_CALL load( const char* filename, ErrorDetails* detailsOut=HK_NULL, LoadOptions options=LOAD_DEFAULT );

		/// Load serialized objects from buffer and return pointer
		/// to hkResource object. The buffer may be freed after loading.
		/// See hkSerializeUtil::load( hkStreamReader* sr ) for details.
	HK_EXPORT_COMMON hkResource* HK_CALL load( const void* buf, int buflen, ErrorDetails* detailsOut=HK_NULL, LoadOptions options=LOAD_DEFAULT );


		/// Load serialized objects from stream and return pointer
		/// to hkObjectResource object.
		/// To access hkObjectResource objects you should call hkObjectResource::getContents()
		/// or hkObjectResource::getContentsWithRegistry() specifying type of top level
		/// object pointer you expect.
		/// hkObjectResource is reference counted and users are responsible to
		/// remove reference when they do not need its content.
		/// The objects owned by hkObjectResource are allocated on heap and reference counted.
		///
		/// Load serialized objects from stream and return pointer to hkObjectResource object.
		/// If 'classReg' or 'typeReg' are null the ones from hkBuiltinTypeRegistry are used.
		/// The function does additional check for the stream format, versioning and finishing steps.
		/// It will return HK_NULL if the checks failed. The error details are
		/// returned in 'detailsOut'.
	HK_EXPORT_COMMON hkObjectResource* HK_CALL loadOnHeap( hkStreamReader* stream, ErrorDetails* errorOut=HK_NULL, LoadOptions options=LOAD_DEFAULT );

		/// Load serialized objects from a file using name and return pointer
		/// to hkObjectResource object.
		/// See hkSerializeUtil::load( hkStreamReader* sr ) for details.
	HK_EXPORT_COMMON hkObjectResource* HK_CALL loadOnHeap( const char* filename, ErrorDetails* errorOut=HK_NULL, LoadOptions options=LOAD_DEFAULT );

		/// Load serialized objects from a file using name and return pointer
		/// to hkObjectResource object.
		/// See hkSerializeUtil::load( hkStreamReader* sr ) for details.
	HK_EXPORT_COMMON hkObjectResource* HK_CALL loadOnHeap( const void* buf, int buflen, ErrorDetails* errorOut=HK_NULL, LoadOptions options=LOAD_DEFAULT );


	//
	// Shortcut loads
	//

		/// Shortcut to combine loadOnHeap and hkObjectResource::stealContents.
	template<typename T> inline T* loadObject(hkStreamReader* reader, ErrorDetails* errorOut=HK_NULL);

		/// Shortcut to combine loadOnHeap and hkObjectResource::stealContents.
	template<typename T> inline T* loadObject(const char* filename, ErrorDetails* errorOut=HK_NULL);

		/// Shortcut to combine loadOnHeap and hkObjectResource::stealContents.
	template<typename T> inline T* loadObject(const void* buf, int buflen, ErrorDetails* errorOut=HK_NULL);

		

		/// Save a snapshot of a given object in packfile form using provided writer.
		/// Returns HK_SUCCESS if successful.
		/// If you don't provide a target layout then the current host layout is assumed.
		/// NOTE: Some objects are inherently not serializable because they point to
		/// external memory, i.e., the vertex and index arrays of an hkpMeshShape.
		/// These objects should be converted before saving, i.e hkpMeshShape -> hkpStorageMeshShape
		/// (see hkpHavokSnapshot::ConvertListener class for details).
		/// If you want these conversions applied you should provide a hkpHavokSnapshot::ConvertListener as
		/// a value for userListener.
	HK_EXPORT_COMMON hkResult HK_CALL savePackfile( const void* object, const hkClass& klass, hkStreamWriter* writer, const hkPackfileWriter::Options& packFileOptions, hkPackfileWriter::AddObjectListener* userListener=HK_NULL, SaveOptions options=SAVE_DEFAULT );

		/// Save a snapshot of a given object in tagfile form using provided writer.
		/// Returns HK_SUCCESS if successful.
		/// NOTE: Some objects are inherently not serializable because they point to
		/// external memory, i.e., the vertex and index arrays of an hkpMeshShape.
		/// These objects should be converted before saving, i.e hkpMeshShape -> hkpStorageMeshShape
		/// (see hkpHavokSnapshot::ConvertListener class for details).
		/// If you want these conversions applied you should provide a hkpHavokSnapshot::ConvertListener as
		/// a value for userListener.
	HK_EXPORT_COMMON hkResult HK_CALL saveTagfile( const void* object, const hkClass& klass, hkStreamWriter* writer, hkPackfileWriter::AddObjectListener* userListener=HK_NULL, SaveOptions options=SAVE_DEFAULT );

	HK_EXPORT_COMMON hkResult HK_CALL save( const void* object, const hkClass& klass, hkStreamWriter* writer, SaveOptions options=SAVE_DEFAULT );

		/// Shortcut to save an object with out having to specify the hkClass.
	template<typename T> inline hkResult HK_CALL save( const T* object, hkStreamWriter* writer, SaveOptions options=SAVE_DEFAULT );

		/// Shortcut to save an object with out having to specify the hkClass.
	template<typename T> inline hkResult HK_CALL save( const T* object, const char* filename, SaveOptions options=SAVE_DEFAULT );

		/// The format of an asset file.
	enum FormatType
	{
			/// read or open error.
		FORMAT_ERROR,
			/// readable but not recognised.
		FORMAT_UNKNOWN,
			/// binary packfile
		FORMAT_PACKFILE_BINARY,
			/// XML packfile
		FORMAT_PACKFILE_XML,
			/// Binary tagfile
		FORMAT_TAGFILE_BINARY,
			/// XML tagfile
		FORMAT_TAGFILE_XML,
	};

		/// Information returned by detectFormat.
	struct HK_EXPORT_COMMON FormatDetails
	{

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(0, FormatDetails);

			/// Returns true if the file was serialized after the introduction of predicates
		bool supportsPredicates() const { return m_maxPredicateId > hkContentPredicate::NO_PREDICATE; }

			/// Returns true if the file was serialized with support for this specific predicate.
		bool supportsPredicate(hkContentPredicate::PredicateId pred) const { return pred < m_maxPredicateId; }

		typedef hkHandle<int, -1, FormatDetails> PredicateResult;

			/// If the given predicate didn't exist when the file was serialized the returned value is invalid
			/// (check with PredicateResult::isValid()).
			/// If the predicate is true for the content of the file the value (PredicateResult::value())
			/// is 1 (true), otherwise it is 0 (false).
		PredicateResult verifiesPredicate(hkContentPredicate::PredicateId pred) const;

			/// The type of the file
		hkEnum<FormatType,hkInt32> m_formatType;
			/// The version number for the format 
		int m_formatVersion;
			/// The SDK version which created this file, if known.
		hkStringPtr m_version;
			/// For binary packfiles, the binary format.
		hkStructureLayout::LayoutRules m_layoutRules;
			/// This is the value of FilePredicate::MAX_PREDICATE_ID when the file was serialized. Any predicate bigger than this
			/// can't be checked against this file.
		hkContentPredicate::PredicateId m_maxPredicateId;
			/// The list of predicates which are true for the data in the file.
		hkArray<hkUint16> m_truePredicates;
	};


		/// Detect the type of a packfile stream.
	HK_EXPORT_COMMON hkEnum<FormatType,hkInt32> HK_CALL detectFormat( hkStreamReader* reader, ErrorDetails* errorOut=HK_NULL );

		/// Extract some information from the file header.
		/// See FormatDetails for the available information.
	HK_EXPORT_COMMON void HK_CALL detectFormat(const char* filename, FormatDetails& detailsOut, ErrorDetails* errorOut=HK_NULL );
	HK_EXPORT_COMMON void HK_CALL detectFormat( hkStreamReader* reader, FormatDetails& detailsOut, ErrorDetails* errorOut=HK_NULL );

		/// Is the stream a tagfile, XML packfile or binary packfile for the current platform?
	HK_EXPORT_COMMON hkBool32 HK_CALL isLoadable(hkStreamReader* sr);
}

#include <Common/Serialize/Util/hkSerializeUtil.inl>

#endif // HK_SERIALIZE_UTIL_H

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
