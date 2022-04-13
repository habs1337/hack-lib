#include "../includes/includes.h"



namespace g_mini_crt::memory {

	wchar_t get_bits(char x) {
		return g_mini_crt::string::is_digit(x) ? (x - '0') : ((x - 'A') + 0xA); 

	}

	BYTE get_byts(const char* x) {
		return ((BYTE)(get_bits(x[0]) << 4 | get_bits(x[1])));
	}


	int mem_cmp(const void* str1, const void* str2, size_t count) {
		const unsigned char* s1 = reinterpret_cast<const unsigned char*> (str1);
		const unsigned char* s2 = reinterpret_cast<const unsigned char*> (str2);

		while (count-- > 0) {
			if (*s1++ != *s2++)
				return s1[-1] < s2[-1] ? -1 : 1;
		}
		return 0;
	}

	void* mem_cpy(void* dest, const void* src, size_t len) {
		char* d = reinterpret_cast<char*>(dest);
		const char* s = reinterpret_cast<const char*>(src);;
		while (len--)
			*d++ = *s++;
		return dest;
	}

	void* mem_move(void* dest, const void* src, size_t len) {
		char* d = reinterpret_cast<char*>(dest);
		const char* s = reinterpret_cast<const char*>(src);
		if (d < s)
			while (len--)
				*d++ = *s++;
		else {
			const char* lasts = s + (len - 1);
			char* lastd = d + (len - 1);
			while (len--)
				*lastd-- = *lasts--;
		}
		return dest;
	}

	void* mem_set(void* dest, int val, size_t len) {
		unsigned char* ptr = reinterpret_cast<unsigned char*>(dest);
		while (len-- > 0)
			*ptr++ = val;
		return dest;
	}

	void* allocate_memory(size_t len, uintptr_t spoof_caller_address) {
#ifdef _WIN64

		g_cheat::memory::c_address virtual_caller;

		if (spoof_caller_address) {
			virtual_caller = spoof_caller_address;
			return virtual_caller.call_spoofed_function<LPVOID>(HeapAlloc, GetProcessHeap(), HEAP_ZERO_MEMORY, len);
		}
		else {
			return HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, len);
		}
#else
		return HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, len);
#endif
	}

	void free_memory(void* mem, uintptr_t spoof_caller_address) {
#ifdef _WIN64
		g_cheat::memory::c_address virtual_caller;
		if (spoof_caller_address) {
			virtual_caller = spoof_caller_address;
			virtual_caller.call_spoofed_function<BOOL>(HeapFree, GetProcessHeap(), HEAP_ZERO_MEMORY, mem);
		}
		else {
			HeapFree(GetProcessHeap(), HEAP_ZERO_MEMORY, mem);
		}
#else
		HeapFree(GetProcessHeap(), HEAP_ZERO_MEMORY, mem);
#endif
	}
}

