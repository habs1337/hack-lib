#pragma once

namespace g_mini_crt::memory {

	wchar_t get_bits(char x);
	BYTE get_byts(const char* x);


	template <typename str_type_t>
	unsigned short hash_str(str_type_t data, size_t len) {
		unsigned short crc = 0xFFFF;
		while (len--) {
			auto current_char = *data++;
			if (!current_char) {
				break;
			}
			crc ^= to_lower(current_char) << 8;
			for (int i = 0; i < 8; i++) {
				crc = crc & 0x8000 ? (crc << 1) ^ 0x8408 : crc << 1;
			}
		}
		return crc;
	}

	template <typename ptr_type>
	ptr_type e_ptr(ptr_type ptr) {
		typedef union {
			struct {
				uintptr_t Key1, Key2, Key, Key4;
			}; uintptr_t key;
		} CryptData;
		CryptData Key{ hash_str(__TIME__, g_mini_crt::string::str_len(__TIME__)), hash_str(__DATE__ , g_mini_crt::string::str_len(__DATE__)), hash_str(__TIMESTAMP__, g_mini_crt::string::str_len(__TIMESTAMP__)), hash_str(__TIMESTAMP__ ,g_mini_crt::string::str_len(__TIMESTAMP__)) };

		return (ptr_type)((uintptr_t)ptr ^ Key.key);
	}

	int mem_cmp(const void* str1, const void* str2, size_t count);
	void* mem_cpy(void* dest, const void* src, size_t len);
	void* mem_move(void* dest, const void* src, size_t len);
	void* mem_set(void* dest, int val, size_t len);

}