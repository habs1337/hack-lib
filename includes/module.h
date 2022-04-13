#pragma once
//#include "address.h"

#if defined(_M_IX86)
#define READNWORD __readfsdword
#elif defined(_M_X64)
#define READNWORD __readgsqword
#endif



namespace g_cheat::memory {

	namespace winternl_rebuild {
        typedef struct _LIST_ENTRY {
            struct _LIST_ENTRY* Flink;
            struct _LIST_ENTRY* Blink;
        } LIST_ENTRY, * PLIST_ENTRY, PRLIST_ENTRY;

        struct UNICODE_STRING {
            uint16_t Length;
            uint16_t MaximumLength;
            wchar_t* Buffer;
        };

        struct LDR_DATA_TABLE_ENTRY {
            LIST_ENTRY InLoadOrderLinks;
            LIST_ENTRY InMemoryOrderLinks;
            union {
                LIST_ENTRY InInitializationOrderLinks;
                LIST_ENTRY InProgressLinks;
            };
            uintptr_t DllBase;
            uintptr_t EntryPoint;
            uint32_t SizeOfImage;
            UNICODE_STRING FullDllName;
            UNICODE_STRING BaseDllName;
        };

        struct PEB_LDR_DATA {
            uint32_t Length;
            uint8_t Initialized;
            uintptr_t SsHandle;
            LIST_ENTRY InLoadOrderModuleList;
            LIST_ENTRY InMemoryOrderModuleList;
            LIST_ENTRY InInitializationOrderModuleList;
            uintptr_t EntryInProgress;
            uint8_t ShutdownInProgress;
            uintptr_t ShutdownThreadId;
        };

        struct PEB {
            uint8_t InheritedAddressSpace;
            uint8_t ReadImageFileExecOptions;
            uint8_t BeingDebugged;
            union {
                uint8_t BitField;
                struct {
                    uint8_t ImageUsesLargePages : 1;
                    uint8_t IsProtectedProcess : 1;
                    uint8_t IsImageDynamicallyRelocated : 1;
                    uint8_t SkipPatchingUser32Forwarders : 1;
                    uint8_t IsPackagedProcess : 1;
                    uint8_t IsAppContainer : 1;
                    uint8_t IsProtectedProcessLight : 1;
                    uint8_t SpareBits : 1;
                };
            };
            uintptr_t Mutant;
            uintptr_t ImageBaseAddress;
            PEB_LDR_DATA* Ldr;
        };

        struct CLIENT_ID {
            uintptr_t UniqueProcess;
            uintptr_t UniqueThread;
        };

        struct TEB {
            NT_TIB NtTib;
            uintptr_t EnvironmentPointer;
            CLIENT_ID ClientId;
            uintptr_t ActiveRpcHandle;
            uintptr_t ThreadLocalStoragePointer;
            PEB* ProcessEnvironmentBlock;
        };
	}

	class c_module {


		PTEB get_teb();
		bool get_module_handle(const wchar_t* module_name);

	public:
		c_address m_start;
		c_address m_end;

		c_module();
		c_module(const wchar_t* module_name);

		bool is_valid();

		c_address find_pattern(const char* pattern, const char* mask);
        c_address find_pattern(const char* pattern);

		c_address get_export(const char* name); 
		c_address get_import(const char* name); 

		void find_module(const wchar_t* module_name = nullptr);
	};

}
