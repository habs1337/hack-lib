#include "../includes/includes.h"

extern "C" int _fltused = 0;

namespace g_mini_crt::string {

	char to_lower(char symb) {
		return  (symb >= 'A' && symb <= 'Z') ? (symb + 32) : symb;
	}

	wchar_t wcs_to_lower(wchar_t symb) {
		return  (symb >= 'A' && symb <= 'Z') ? (symb + 32) : symb;
	}

	bool in_range(char x, char a, char b) {
		return (x >= a && x <= b);
	}

	bool wcs_in_range(wchar_t x, wchar_t a, wchar_t b) {
		return (x >= a && x <= b);
	}

	bool is_digit(char string) {
		return string >= '0' && string <= '9';
	}

	bool wcs_is_digit(wchar_t string) {
		return string >= '0' && string <= '9';
	}

	uint32_t str_len(const char* string) {
		uint32_t counter = 0;
		if (!string) return 0;
		for (; *string != '\0'; ++string)
			++counter;
		return counter;
	}

	uint32_t wcs_str_len(const wchar_t* string) {
		uint32_t counter = 0;
		if (!string) return 0;
		for (; *string != '\0'; ++string)
			++counter;
		return counter;
	}

	char* str_chr(char* string, uint32_t value) {
		do {
			if (to_lower(*string) == value)
				return  reinterpret_cast<char*>(string);
		} while (to_lower(*string++));
		return 0;
	}

	wchar_t* wcs_str_chr(wchar_t* string, uint32_t value) {
		do {
			if (wcs_to_lower(*string) == value)
				return  string;
		} while (wcs_to_lower(*string++));
		return 0;
	}


	int32_t str_cmp(const char* first, const char* second, uint32_t size) {
		char first_char, second_char;

		if (size == 0) {
			int32_t first_len = str_len(first), second_len = str_len(second);
			size = first_len > second_len ? first_len : second_len;
		}

		while (size-- > 0) {
			first_char = to_lower(*first++);
			second_char = to_lower(*second++);

			if (first_char != second_char)
				return first_char - second_char;

			if (first_char == '\0')
				return 0;
		}
		return 0;
	}

	int32_t wcs_str_cmp(const wchar_t* first, const wchar_t* second, uint32_t size) {
		wchar_t first_char, second_char;

		if (size == 0) {
			int32_t first_len = wcs_str_len(first), second_len = wcs_str_len(second);
			size = first_len > second_len ? first_len : second_len;
		}

		while (size-- > 0) {
			first_char = wcs_to_lower(*first++);
			second_char = wcs_to_lower(*second++);

			if (first_char != second_char)
				return first_char - second_char;

			if (first_char == '\0')
				return 0;
		}
		return 0;
	}

	char* str_str(char* first, const char* second) {
		auto source = first;
		auto length = str_len(second);
		for (; (source = str_chr(source, *second)) != 0; source++) {
			if (str_cmp(source, second, length) == 0)
				return source;
		}
		return 0;
	}

	wchar_t* wcs_str(wchar_t* first, const wchar_t* second) {
		auto source = first;
		auto length = wcs_str_len(second);
		for (; (source = wcs_str_chr(source, *second)) != 0; source++) {
			if (wcs_str_cmp(source, second, length) == 0)
				return source;
		}
		return 0;
	}


	size_t atoi(const char* c) {
		size_t result = 0;
		short state = 1;
		if (*c == '+' || *c == '-') {
			if (*c == '-') state = -1;
			c++;
		}
		while (wcs_is_digit(*c)) {
			result *= 10;
			result += (size_t)(*c - '0');
			c++;
		}
		return (result * state);
	}

	size_t wcs_atoi(const wchar_t* c) {
		size_t value = 0;
		short sign = 1;
		if (*c == '+' || *c == '-') {
			if (*c == '-') sign = -1;
			c++;
		}
		while (wcs_is_digit(*c)) {
			value *= 10;
			value += (size_t)(*c - '0');
			c++;
		}
		return (value * sign);
	}

	char* itoa(size_t number, char* destination, int notation) {
		size_t count = 0;
		do {
			size_t digit = number % notation;
			destination[count++] = (digit > 9) ? digit - 10 + 'A' : digit + '0';
		} while ((number /= notation) != 0);
		destination[count] = '\0';
		size_t i;
		for (i = 0; i < count / 2; ++i) {
			char symbol = destination[i];
			destination[i] = destination[count - i - 1];
			destination[count - i - 1] = symbol;
		}
		return destination;
	}

	wchar_t* wcs_itoa(size_t number, wchar_t* destination, int notation) {
		size_t count = 0;
		do {
			size_t digit = number % notation;
			destination[count++] = (digit > 9) ? digit - 10 + 'A' : digit + '0';
		} while ((number /= notation) != 0);
		destination[count] = '\0';
		size_t i;
		for (i = 0; i < count / 2; ++i) {
			wchar_t symbol = destination[i];
			destination[i] = destination[count - i - 1];
			destination[count - i - 1] = symbol;
		}
		return destination;
	}

}