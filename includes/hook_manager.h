#pragma once


namespace g_cheat::memory::hooks {

	class c_vmt {
		c_address m_new_vtable, m_original_vtable, m_class_base;
		size_t m_current_vtable_size;
		bool m_hooked_table;

		void get_vtable_size();
	public:

		c_vmt();

		bool init(void** class_base);
		void setup_hook(size_t index, void* function_ptr);

		void disable_hook(size_t index);
		void unhook_vtable();

		template< typename o = void*, typename i = void* >
		static __forceinline o force_cast(i in) {
			union { i in; o out; }
			u = { in };
			return u.out;
		};

		template< typename t = c_address >
		__forceinline t call_original_method(size_t index) {
			//return m_original_vtable[index].as< t >();
			return m_original_vtable.as<c_address*>()[index].as<t>();
		}
	};

}