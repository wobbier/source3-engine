/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKBASE_LOCAL_SINGLETON_H
#define HKBASE_LOCAL_SINGLETON_H

#ifndef __HAVOK_PARSER__

template <typename T>
class hkLocalSingleton
{
	public:

		static T* s_instance;

			/// Get the instance of this singleton. This creates an instance when hkBaseSystem::init is called.
		static HK_FORCE_INLINE T& HK_CALL getInstance()
		{
			return *hkLocalSingleton<T>::s_instance;
		}

			/// Remove a reference to the existing singleton and use the supplied one instead.
		static void HK_CALL replaceInstance(T* t)
		{
			if(hkLocalSingleton<T>::s_instance)
			{
				hkLocalSingleton<T>::s_instance->removeReference();
			}
			hkLocalSingleton<T>::s_instance = t;
		}

		/// Remove a reference to the existing singleton and use the supplied one instead adding a reference to it.
		static void HK_CALL replaceInstanceAndAddReference(T* t)
		{
			t->addReference();
			if (hkLocalSingleton<T>::s_instance)
			{
				hkLocalSingleton<T>::s_instance->removeReference();
			}
			hkLocalSingleton<T>::s_instance = t;			
		}

			/// Has this singleton been initialized?
		static hkBool HK_CALL isInitialised()
		{
			return hkLocalSingleton<T>::s_instance != HK_NULL;
		}

	protected:

		hkLocalSingleton() { }

		hkLocalSingleton(const hkLocalSingleton&) {}; //not implemented
		hkLocalSingleton& operator= (const hkLocalSingleton&) { return *this; }; //not implemented
};

	
/// Add BASE_CLASS to the singleton init list.
/// The singleton is automatically created with all the other singletons and automatically destroyed.
#define HK_LOCAL_SINGLETON_IMPLEMENTATION(BASE_CLASS) \
	template<> BASE_CLASS* hkLocalSingleton<BASE_CLASS>::s_instance = HK_NULL; \
	static hkReferencedObject* HK_CALL BASE_CLASS ## create() { return new BASE_CLASS(); } \
	static hkSingletonInitNode hkSingletonRegister##BASE_CLASS (#BASE_CLASS, &BASE_CLASS ## create, (void**)&BASE_CLASS::s_instance)

/// Add CUSTOM_CLASS as the implementation of BASE_CLASS to the singleton init list.
/// The singleton is automatically created with all the other singletons and automatically destroyed.
#define HK_LOCAL_SINGLETON_CUSTOM_IMPLEMENTATION(BASE_CLASS, CUSTOM_CLASS) \
	template<> BASE_CLASS* hkLocalSingleton<BASE_CLASS>::s_instance = HK_NULL; \
	static hkReferencedObject* HK_CALL BASE_CLASS ## create() { return new CUSTOM_CLASS(); } \
	static hkSingletonInitNode hkSingletonRegister##BASE_CLASS (#BASE_CLASS, &BASE_CLASS ## create, (void**)&BASE_CLASS::s_instance)

/// When the singleton is to be instantiated at start up a function is called. If the function returns HK_NULL
/// it indicates the construction couldn't be performed, because something else needed to be constructed first.
/// Havok will automatically try to reconstruct once other singletons have been constructed.
/// 
/// The signature of the function should be hkReferencedObject* HK_CALL func() { ... }.
/// The singleton is automatically created with all the other singletons with the given custom call, and automatically 
/// destroyed as a normal singleton.
#define HK_LOCAL_SINGLETON_CUSTOM_CALL(BASE_CLASS, FUNC) \
	template<> BASE_CLASS* hkLocalSingleton<BASE_CLASS>::s_instance = HK_NULL; \
	static hkSingletonInitNode hkSingletonRegister##BASE_CLASS (#BASE_CLASS, &FUNC, (void**)&BASE_CLASS::s_instance)

/// Manual implementation singletons have null creation pointers and must
/// explicitly be initialized in hkBaseSystem::init().
/// The singleton is NOT automatically created or automatically destroyed, the user will need to create and
/// delete it manually using hkSingleton<>::replaceInstance(). This allows for creation of the singleton before
/// any other singleton and deletion after all others.
#define HK_LOCAL_SINGLETON_MANUAL_IMPLEMENTATION(BASE_CLASS) \
	template<> BASE_CLASS* hkLocalSingleton<BASE_CLASS>::s_instance = HK_NULL; \
	static hkSingletonInitNode hkSingletonRegister##BASE_CLASS (#BASE_CLASS, HK_NULL, (void**)&BASE_CLASS::s_instance)

#define HK_LOCAL_SINGLETON_SPECIALIZATION_DECL(BASE_CLASS) \
	template<> BASE_CLASS* hkLocalSingleton<BASE_CLASS>::s_instance

#endif

#endif // HKBASE_LOCAL_SINGLETON_H

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
