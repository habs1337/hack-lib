#include "../includes/includes.h"


namespace g_cheat::memory {
	 
		c_module::c_module() {
			m_start = nullptr;
			m_end = nullptr;
		}

		c_module::c_module(const wchar_t* module_name) {
			if (!get_module_handle(module_name)) {
				m_start = nullptr;
				m_end = nullptr;
			}
		}

		//should never happen
		bool c_module::is_valid() {
			return m_start.is_valid() && m_end.is_valid();
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
				auto entry = CONTAINING_RECORD(it, winternl_rebuild::LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);

				if (!module_name || g_mini_crt::string::wcs_str(entry->FullDllName.Buffer, module_name)) {
					m_start = entry->DllBase;
					m_end = m_start + entry->SizeOfImage;

					return true;
				}
			}
			return false;
		}


		c_address c_module::find_pattern(const char* pattern, const char* mask) {
			for (auto cur = m_start.as<size_t>(); cur < m_end.as<size_t>(); cur++) {
			
				if ([](const char* _current_byte, const char* _pattern, const char* _mask) {
					for (; *_mask; ++_mask, ++_current_byte, ++_pattern)
						if (*_mask == 'x' && *_current_byte != *_pattern) return false;
						return (*_mask) == 0;
					}(reinterpret_cast<char*>(cur), pattern, mask))
					return c_address(cur);
			}

			return c_address();
		}

		c_address c_module::find_pattern(const char* pattern) {
			const char* pat = pattern;

			c_address first_match;
			for (auto cur = m_start.as<size_t>(); cur < m_end.as<size_t>(); cur++) {
				if (!*pat) {
					return first_match;
				}

				if (*(PBYTE)pat == '\?' || *(BYTE*)cur == g_mini_crt::memory::get_byts(pat)) {
					if (!first_match.as<uintptr_t>())
						first_match = cur;

					if (!pat[2])
						return first_match;

					if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
						pat += 3;
					else pat += 2;
				}
				else {
					pat = pattern;
					first_match = c_address();
				}
			}

			return c_address();
		}

		c_address c_module::get_export(const char* name) {

			if (!m_start.is_valid()) {
				return c_address();
			}
			
			//process image data
			PIMAGE_NT_HEADERS current_nt_header = m_start.add<PIMAGE_NT_HEADERS>(m_start.as<PIMAGE_DOS_HEADER>()->e_lfanew);

			PIMAGE_EXPORT_DIRECTORY export_dir = m_start.add<PIMAGE_EXPORT_DIRECTORY>(current_nt_header->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
			
			//process list
			for (DWORD i = 0; i < export_dir->NumberOfNames; i++) {
				//get ordinal & name
				USHORT idx = ((USHORT*)(m_start + export_dir->AddressOfNameOrdinals))[i];
				const char* current_export_name = m_start.as<const char*>() + ((DWORD*)(m_start + export_dir->AddressOfNames))[i];

				int str_length = g_mini_crt::string::str_len(name);
				if (!g_mini_crt::string::str_cmp(name, current_export_name, str_length)) {
					return m_start.add(m_start.add<DWORD*>(export_dir->AddressOfFunctions)[idx]);
				}
			} 
			return c_address();
		}


		c_address c_module::get_import(const char* name) {
			if (!m_start.is_valid()) {
				return c_address();
			}
			//process image data
			PIMAGE_NT_HEADERS current_nt_header = m_start.add<PIMAGE_NT_HEADERS>(m_start.as<PIMAGE_DOS_HEADER>()->e_lfanew);

			PIMAGE_IMPORT_DESCRIPTOR import_dir = m_start.add<PIMAGE_IMPORT_DESCRIPTOR>(current_nt_header->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);

			for (IMAGE_IMPORT_DESCRIPTOR* current_import = import_dir; current_import->Name != 0; current_import++) {
				auto first_thunk = c_address(current_import->FirstThunk);
				auto original_first_thunk = c_address(current_import->OriginalFirstThunk);
				
				for (int current_function = 0; *(current_function + first_thunk.add(m_start.as<size_t>()).as<void**>()) != nullptr; current_function++) {
					char* imported_function_name = original_first_thunk.to(size_t(m_start) + current_function).add(size_t(m_start)).as<char*>();
					const intptr_t i_funct_name = (intptr_t)imported_function_name;
					if (i_funct_name >= 0) {
						int str_length = g_mini_crt::string::str_len(name);
						if (!g_mini_crt::string::str_cmp(name, imported_function_name, str_length)) {

							return c_address(first_thunk.add(size_t(m_start)).as<void**>() + current_function);
						}
					}
				}

			}
			return c_address();
		}

		void c_module::find_module(const wchar_t* module_name) {
			if (!get_module_handle(module_name)) {
				m_start = nullptr;
				m_end = nullptr;
			}
		}
	
}