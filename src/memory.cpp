#include "../includes/includes.h"
//#ifdef _WIN64
//PVOID g_mini_crt::memory::red_addr::ReturnAddressStubEnc = 0;
//#endif


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

}

