#pragma once
//#include "address.h"

#if defined(_M_IX86)
#define READNWORD __readfsdword
#elif defined(_M_X64)
#define READNWORD __readgsqword
#endif



namespace g_cheat::memory {

	class c_module {


		PTEB get_teb();
		bool get_module_handle(const wchar_t* module_name);

	public:
		c_address m_module;

		c_module();
		c_module(const wchar_t* module_name);

		bool is_valid();

		c_address find_pattern(const char* pattern, const char* mask);

		c_address get_export(const char* name); 
		c_address get_import(const char* name); 

		void find_module(const wchar_t* module_name = nullptr);
	};

}
