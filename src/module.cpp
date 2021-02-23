#include "../includes/includes.h"


namespace g_cheat::memory {
	 
		c_module::c_module() {
			m_module = nullptr;
		}

		c_module::c_module(const wchar_t* module_name) {
			if (!get_module_handle(module_name)) {
				m_module = nullptr;
			}
		}

		bool c_module::is_valid() {
			return m_module.is_valid();
		}

		PTEB c_module::get_teb() {
			return (PTEB)READNWORD(FIELD_OFFSET(NT_TIB, Self));
		}

		bool c_module::get_module_handle(const wchar_t* module_name) {
			auto teb = get_teb();

			if (!teb)
				return false;

			auto peb_ldr = teb->ProcessEnvironmentBlock->Ldr;

			if (!peb_ldr)
				return false;

			for (auto it = peb_ldr->InMemoryOrderModuleList.Flink; it != &peb_ldr->InMemoryOrderModuleList; it = it->Flink) {
				auto entry = CONTAINING_RECORD(it, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);

				//printf("%ls %ls\n", module_name, entry->FullDllName.Buffer);
				//g_mini_crt::string::wcs_str_cmp(entry->FullDllName.Buffer, module_name, g_mini_crt::string::wcs_str_len(module_name))
				//g_mini_crt::string::wcs_str(entry->FullDllName.Buffer, module_name) 
				if (!module_name || g_mini_crt::string::wcs_str(entry->FullDllName.Buffer, module_name)) {
					m_module = reinterpret_cast<uintptr_t>(entry->DllBase);
					return true;
				}
			}
			return false;
		}

		c_address c_module::find_pattern(const char* pattern, const char* mask) {
			for (size_t i = 0u; i < MAX_POINTER_VAL; i++) {
				if ([](const char* _current_byte, const char* _pattern, const char* _mask) {
					for (; *_mask; ++_mask, ++_current_byte, ++_pattern)
						if (*_mask == 'x' && *_current_byte != *_pattern) return false;
						return (*_mask) == 0;
					}(m_module.add(i).as<char*>(), pattern, mask))
					return m_module.add(i);
			}
			
			return c_address();
		}

		c_address c_module::get_export(const char* name) {

			if (!m_module.is_valid()) {
				return c_address();
			}
			
			//process image data
			PIMAGE_NT_HEADERS current_nt_header = (PIMAGE_NT_HEADERS)(m_module + (m_module.as<PIMAGE_DOS_HEADER>())->e_lfanew);
			PIMAGE_EXPORT_DIRECTORY export_dir = (PIMAGE_EXPORT_DIRECTORY)(m_module + current_nt_header->OptionalHeader.DataDirectory[0].VirtualAddress);
			
			//process list
			for (DWORD i = 0; i < export_dir->NumberOfNames; i++) {
				//get ordinal & name
				USHORT idx = ((USHORT*)(m_module + export_dir->AddressOfNameOrdinals))[i];
				const char* current_export_name = m_module.as<const char*>() + ((DWORD*)(m_module + export_dir->AddressOfNames))[i];

				int str_length = g_mini_crt::string::str_len(name);
				if (!g_mini_crt::string::str_cmp(name, current_export_name, str_length))
					return c_address(m_module + ((DWORD*)(m_module + export_dir->AddressOfFunctions))[idx]);
			} 
			return c_address();
		}

		void c_module::find_module(const wchar_t* module_name) {
			if (!get_module_handle(module_name)) {
				m_module = nullptr;
			}
		}
	
}