/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_hkOptionalComponent_H
#define HK_hkOptionalComponent_H


class hkOstream;

	/// Utility to determine if systems which are linked in, are actually used.
	/// If a system is registered but never used, it unnecessarily increases the executable code size.
	/// 
	/// By far the best approach to reduce code size is to reduce dependencies so that if it is never explicitly called,
	/// it can be stripped at link time. Sometimes this is impossible because decision to use a system depends on some runtime value.
	/// 
	/// A common pattern in these cases is to replace a hard dependency "i.e. X* x = new X()" with a soft dependency
	/// through a creation function pointer. e.g. "X* x = (*X::create)()". Since "X::create" is a function pointer, rather than a plain
	/// static method, this allows swapping implementations of X without rebuilding. Note that for a function pointer "p", C/C++ treats 
	/// "(*p)()" and "p()" identically so you will often see "X* x = X::create()" instead of the more explicit "X* x= (*X::create)()"
	///
	/// In the extreme case, you may know that in a certain configuration, X::create
	/// cannot never be called and the creation function pointer may be set to null, thus allowing the linker
	/// to strip the unused code.
	///
	/// This class allows systems to register such creation functions and report if they have been used or not.
	/// Assuming there are no hard dependencies and the only dependencies left are through function pointers,
	/// the following 2 things are needed to make a component optional:
	/// 
	/// -# Use the macro HK_OPTIONAL_COMPONENT_DEFINE(systemName, funcPtr, implementation) to define a helper variable.
	/// Assignment of the function pointer will not happen until HK_OPTIONAL_COMPONENT_REQUEST is called (see below).
	/// -# Whenever the component is actually used (typically in "implementation", above) indicate that system has been used
	/// by calling HK_OPTIONAL_COMPONENT_MARK_USED(systemName).
	///
	/// To use an optional component use the HK_OPTIONAL_COMPONENT_REQUEST(systemName) macro.
	/// This assigns the function pointer and marks the system as being requested.
	///
	/// Finally you can iterate through the registered systems using getFirstComponent() and getNext()
	/// to examine which systems were linked and used. Alternatively writeReport() writes a text summary.
class HK_EXPORT_COMMON hkOptionalComponent
{
	public:

		HK_DECLARE_PLACEMENT_ALLOCATOR();
			
			/// 
		typedef void (*OnRequestFunction)();

			/// The normal constructor, used to initialize a function pointer upon request.
			/// This is used by the HK_OPTIONAL_COMPONENT_DEFINE macro.
		hkOptionalComponent(const char* name, void** funcPtr, void* func);

			/// This constructor allows an arbitrary callback if initialization of a system requires more
			/// than assigning a single pointer.
			/// This is used by the HK_OPTIONAL_COMPONENT_DEFINE_MANUAL macro.
		hkOptionalComponent(const char* name, OnRequestFunction func); 
	
			/// Get the head of the component list.
		static const hkOptionalComponent* getFirstComponent();

			/// Get the head of the component list.
		static void writeReport(hkOstream& os);

			/// Usually called via HK_OPTIONAL_COMPONENT_REQUEST to request the component is linked in.
		void request();

			/// Mark the system as being used
		inline void markUsed() { m_isUsed = true; }

			/// Get the name of the system
		inline const char* getName() const { return m_name; }

			/// True if it has been used
		inline hkBool isUsed() const { return m_isUsed; }

			/// True if it was requested.
			/// Sometimes components appear even if they have not been requested, usually because of a hard dependency.
		inline hkBool wasRequested() const { return m_isRequested; }

			/// Get the next info in the list
		inline const hkOptionalComponent* getNext() const { return m_next; }
				
	protected:

		hkOptionalComponent* m_next;
		const char* m_name;
		OnRequestFunction m_onLink;
		void** m_funcPtr;
		void* m_func;
		hkBool m_isUsed;
		hkBool m_isRequested;
};


#define HK_OPTIONAL_COMPONENT_DEFINE(NAME, FUNC_PTR, FUNC_ADDR) \
	hkOptionalComponent hkOptionalComponent_##NAME(#NAME, (void**)&FUNC_PTR, (void*)FUNC_ADDR)
#define HK_OPTIONAL_COMPONENT_DEFINE_MANUAL(NAME, ON_LINK) \
	hkOptionalComponent hkOptionalComponent_##NAME(#NAME, ON_LINK)

#define HK_OPTIONAL_COMPONENT_REQUEST(NAME) \
	extern hkOptionalComponent hkOptionalComponent_##NAME; \
	hkOptionalComponent_##NAME.request()

#define HK_OPTIONAL_COMPONENT_MARK_USED(NAME) \
	extern hkOptionalComponent hkOptionalComponent_##NAME; \
	hkOptionalComponent_##NAME.markUsed()


#endif // HK_hkOptionalComponent_H

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
