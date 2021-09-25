#pragma once

namespace g_mini_crt::string {
#define MAX_PRECISION	(10)
	static const double rounders[MAX_PRECISION + 1] =
	{
		0.5,				// 0
		0.05,				// 1
		0.005,				// 2
		0.0005,				// 3
		0.00005,			// 4
		0.000005,			// 5
		0.0000005,			// 6
		0.00000005,			// 7
		0.000000005,		// 8
		0.0000000005,		// 9
		0.00000000005		// 10
	};

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

	char* str_cat(char* dest, const char* src);
	wchar_t* wcs_str_cat(wchar_t* dest, const wchar_t* src);


	size_t atoi(const char* c);
	size_t wcs_atoi(const wchar_t* c);

	char* itoa(size_t number, char* destination, int notation = 10);
	wchar_t* wcs_itoa(size_t number, wchar_t* destination, int notation = 10);

	char* ftoa(double f, char* buf, int precision);
	wchar_t* wcs_ftoa(double f, wchar_t* buf, int precision);

	void debug_text(const char* text);
	void debug_text(const char* text, uintptr_t val, int notation, uintptr_t spoof_caller_address);
	void debug_text(const char* text, float val, uintptr_t spoof_caller_address);
}