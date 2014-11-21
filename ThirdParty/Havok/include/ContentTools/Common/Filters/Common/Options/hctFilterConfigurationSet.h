/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HAVOK_FILTER_CONFIGURATION_SET__H
#define HAVOK_FILTER_CONFIGURATION_SET__H

/// This class stores a set of filter configurations,
/// and handles loading/saving of that data
class hctFilterConfigurationSet
{
	public:

		/// Structure describing a single filter stage
		struct FilterStage
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_EXPORT, FilterStage );
			
			FilterStage() : m_index(-1), m_optionDataVersion(0) {}
			FilterStage( const FilterStage& other );
		
			int				m_index;				// enumerated filter index (not saved)
			unsigned int	m_optionDataVersion;	// version of the filter that saved the options
			hkArray<char>   m_optionData;			// use AllocateChunk, DeallocateChunk.
		};
		
		/// Structure describing a single configuration of multiple filters
		struct Configuration
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_EXPORT, Configuration );
			
			Configuration() {}
			Configuration( const Configuration& other );
			
			hkStringOld				m_configName;
			hkArray<FilterStage>	m_filterStages;
		};
		
		/// Represents behaviour of any hkOverride.HKO or hkUpgrade.HKO file present
		enum OverrideMode
		{
			MODE_NORMAL,
			MODE_OVERRIDE,
			MODE_UPGRADE
		};
		
		
		/// Construction/destruction
		hctFilterConfigurationSet( const class hctFilterManagerInterface* filterManager );
		~hctFilterConfigurationSet();
		
		/// Get/set the data
		int getData( void* optionData ) const;
		void setData( const void* optionData, int optionDataSize );
		
		/// Check if the data has changed in any way since it was originally set
		bool hasDataChanged();
		
		/// Clear the currently loaded configurations, and set the current configuration index to -1
		void clearConfigurations();
		
		/// Get the current override mode
		const OverrideMode getOverrideMode() const { return m_overrideMode; }
		
		/// Get the current configuration
		Configuration& getCurrentConfiguration() { return m_configurations[ m_currentIndex ]; }
		
		
		/// The set of configurations
		hkArray<Configuration> m_configurations;
		int m_currentIndex;
		
	private:
		
		/// Handle a single configuration ( used in get/setConfigurationSet() )
		int getConfigurationData( void* optionData, int configurationIndex ) const;
		void setConfigurationData( const void* optionData, int optionDataSize, int configurationIndex );
		
		/// Handle configuration sets saved as raw data ( ie. the old way )
		void setConfigurationSetBinary( const void* optionData, int optionDataSize );
		void setConfigurationBinary( const void* optionData, int optionDataSize, int configurationIndex );
		
		
		/// Owner
		const class hctFilterManagerInterface* m_filterManager;
        
		/// Overrides
		hkArray<char> m_originalData;
		OverrideMode m_overrideMode;
};

#endif // HAVOK_FILTER_CONFIGURATION_SET__H

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
