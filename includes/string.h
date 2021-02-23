#pragma once

namespace g_mini_crt::string {
	char to_lower(char symb);

	wchar_t wcs_to_lower(wchar_t symb);

	bool in_range(char x, char a, char b);
	bool wcs_in_range(wchar_t x, wchar_t a, wchar_t b);

	bool is_digit(char string);
	bool wcs_is_digit(wchar_t string);


	uint32_t str_len(const char* string);
	uint32_t wcs_str_len(const wchar_t* string);

	int32_t str_cmp(const char* first, const char* second, uint32_t size = 0);
	int32_t wcs_str_cmp(const wchar_t* first, const wchar_t* second, uint32_t size = 0);

	char* str_chr(char* string, uint32_t value);
	wchar_t* wcs_str_chr(wchar_t* string, uint32_t value);


	char* str_str(char* first, const char* second);
	wchar_t* wcs_str(wchar_t* first, const wchar_t* second);


	size_t atoi(const char* c);
	size_t wcs_atoi(const wchar_t* c);

	char* itoa(size_t number, char* destination, int notation = 10);
	wchar_t* wcs_itoa(size_t number, wchar_t* destination, int notation = 10);

}