#pragma once
#include "address.h"



namespace g_cheat::memory {

	//uintptr_t vmt_data[10000];
	
	class c_vmt {
		c_address* m_new_table, *m_previous_table, m_class_base;
		size_t m_table_size;
		
		size_t get_table_size();
	public:

		bool init(c_address class_base);
		//void setup_hook(size_t index, void* function_ptr);
		template< typename t = c_address >
		__forceinline t setup_hook(size_t index, void* function_ptr) {
			size_t vmt_index{ m_rtti ? index + 1 : index };

			// sanity check some stuff first.
			if (index > m_table_size) {
				return t{};
					}
				

			// redirect.
			m_new_vmt[vmt_index] = (uintptr_t)function_ptr;

			return m_old_vmt[index].as< t >();
		}

		void disable_hook(size_t index);
		void unhook_table();

		template< typename o = void*, typename i = void* >
		__forceinline o force_cast(i in) {
			union { i in; o out; }
			u = { in };
			return u.out;
		};

		template< typename t = c_address >
		__forceinline t call_original_method(size_t index) {
			return m_previous_table[index].as< t >();
		}
	};

}
