/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_IMAGE_H
#define HK_IMAGE_H

/// An abstract interface to an image
class HK_EXPORT_COMMON hkImage : public hkReferencedObject
{
	public:
		
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);

	public:

		/// Channel data types
		enum DataType
		{
			TYPE_UINT8		= 0,
			TYPE_UINT16		= 1,
			TYPE_UINT32		= 2,
			TYPE_FLOAT32	= 3,

			TYPE_UNKNOWN	= 0xFF,
		};

		/// Channel usage type
		enum UsageType
		{
			USAGE_COLOR_R	= 0,
			USAGE_COLOR_G	= 1,
			USAGE_COLOR_B	= 2,
			USAGE_COLOR_A	= 3,
			USAGE_LUMINANCE	= 4,

			USAGE_UNKNOWN	= 0xFF,
		};

		/// Image channel info
		struct HK_EXPORT_COMMON ChannelInfo 
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, hkImage::ChannelInfo);

			/// Initializes all elements
			HK_FORCE_INLINE void set(int offset, int pitch, int stride, DataType dt, UsageType ut)
			{
				m_offset		= hkUint32(offset);
				m_pitch			= hkUint32(pitch);
				m_elementStride	= hkUint16(stride);
				m_dataType		= dt;
				m_usage			= ut;
			}

			hkUint32 m_offset;						///< Offset of the channel in the data buffer
			hkUint32 m_pitch;						///< Size (in bytes) of a horizontal line of pixels in this channel
			hkUint16 m_elementStride;				///< Channel stride (in bytes)

			hkEnum<DataType, hkUint8> m_dataType;	///< The type of elements stored in the channel
			hkEnum<UsageType, hkUint8> m_usage;		///< The 'meaning' of the elements stored in the channel
		};

		/// Image descriptor
		struct HK_EXPORT_COMMON Descriptor
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, hkImage::Descriptor);

			/// Constructor
			Descriptor();

			/// Copy constructor
			Descriptor(const Descriptor& other);

			/// Returns true if the image channels are interleaved
			bool isInterleaved() const;

			/// Returns the number of bits per pixel for this image format. If the image is not interleaved, it will return -1
			int getNumBitsPerPixel() const;

			hkUint32 m_imageWidth;					///< Width of the image in pixels
			hkUint32 m_imageHeight;					///< Height of the image in pixels
			hkArray<ChannelInfo> m_channelInfos;	///< The channels
		};

	public:

		/// Destructor
		virtual ~hkImage();

	public:

		/// Returns the image descriptor
		virtual void getDescriptor(Descriptor& imageInfoOut) const = 0;

		/// Returns the image's data buffer
		virtual void* accessData() = 0;

		/// Returns a read-only pointer to the image's data buffer
		HK_FORCE_INLINE const void* getData() const	{	return const_cast<hkImage*>(this)->accessData();	}

	public:

		/// Creates an image with the given description
		static hkImage* HK_CALL createImage(const Descriptor& imageInfo);

		/// Returns the size in bytes of the given data type
		static int HK_CALL getSizeOf(DataType dataType);
};

#endif	//HK_TEXTURE_LOADER_H

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
