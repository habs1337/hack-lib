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

	char* str_cat(char* dest, const char* src) {
		char* rdest = dest;

		while (*dest)
			dest++;
		while (*dest++ = *src++)
			;
		return rdest;
	}

	wchar_t* wcs_str_cat(wchar_t* dest, const wchar_t* src) {
		wchar_t* rdest = dest;

		while (*dest)
			dest++;
		while (*dest++ = *src++)
			;
		return rdest;
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


	char* ftoa(double f, char* buf, int precision)
	{
		char* ptr = buf;
		char* p = ptr;
		char* p1;
		char c;
		long intPart;

		// check precision bounds
		if (precision > MAX_PRECISION)
			precision = MAX_PRECISION;

		// sign stuff
		if (f < 0)
		{
			f = -f;
			*ptr++ = '-';
		}

		if (precision < 0)  // negative precision == automatic precision guess
		{
			if (f < 1.0) precision = 6;
			else if (f < 10.0) precision = 5;
			else if (f < 100.0) precision = 4;
			else if (f < 1000.0) precision = 3;
			else if (f < 10000.0) precision = 2;
			else if (f < 100000.0) precision = 1;
			else precision = 0;
		}

		// round value according the precision
		if (precision)
			f += rounders[precision];

		// integer part...
		intPart = f;
		f -= intPart;

		if (!intPart)
			*ptr++ = '0';
		else
		{
			// save start pointer
			p = ptr;

			// convert (reverse order)
			while (intPart)
			{
				*p++ = '0' + intPart % 10;
				intPart /= 10;
			}

			// save end pos
			p1 = p;

			// reverse result
			while (p > ptr)
			{
				c = *--p;
				*p = *ptr;
				*ptr++ = c;
			}

			// restore end pos
			ptr = p1;
		}

		// decimal part
		if (precision)
		{
			// place decimal point
			*ptr++ = '.';

			// convert
			while (precision--)
			{
				f *= 10.0;
				c = f;
				*ptr++ = '0' + c;
				f -= c;
			}
		}

		// terminating zero
		*ptr = 0;

		return buf;
	}

	wchar_t* wcs_ftoa(double f, wchar_t* buf, int precision)
	{
		wchar_t* ptr = buf;
		wchar_t* p = ptr;
		wchar_t* p1;
		wchar_t c;
		long intPart;

		// check precision bounds
		if (precision > MAX_PRECISION)
			precision = MAX_PRECISION;

		// sign stuff
		if (f < 0)
		{
			f = -f;
			*ptr++ = '-';
		}

		if (precision < 0)  // negative precision == automatic precision guess
		{
			if (f < 1.0) precision = 6;
			else if (f < 10.0) precision = 5;
			else if (f < 100.0) precision = 4;
			else if (f < 1000.0) precision = 3;
			else if (f < 10000.0) precision = 2;
			else if (f < 100000.0) precision = 1;
			else precision = 0;
		}

		// round value according the precision
		if (precision)
			f += rounders[precision];

		// integer part...
		intPart = f;
		f -= intPart;

		if (!intPart)
			*ptr++ = '0';
		else
		{
			// save start pointer
			p = ptr;

			// convert (reverse order)
			while (intPart)
			{
				*p++ = '0' + intPart % 10;
				intPart /= 10;
			}

			// save end pos
			p1 = p;

			// reverse result
			while (p > ptr)
			{
				c = *--p;
				*p = *ptr;
				*ptr++ = c;
			}

			// restore end pos
			ptr = p1;
		}

		// decimal part
		if (precision)
		{
			// place decimal point
			*ptr++ = '.';

			// convert
			while (precision--)
			{
				f *= 10.0;
				c = f;
				*ptr++ = '0' + c;
				f -= c;
			}
		}

		// terminating zero
		*ptr = 0;

		return buf;
	}
	
	void debug_text(const char* text) {
		OutputDebugStringA(text);
	}

	void debug_text(const char* text, uintptr_t val, int notation, uintptr_t spoof_caller_address) {
		
		char text_val[12];
		int meme;
		itoa(val, text_val, notation);

		int str_length = strlen(text) + strlen(text_val) + 1;
#ifdef _WIN64
		g_cheat::memory::c_address virtual_caller(spoof_caller_address);
		char* str = reinterpret_cast<char*>(virtual_caller.call_spoofed_function<LPVOID>(HeapAlloc, GetProcessHeap(), HEAP_ZERO_MEMORY, str_length));
#else
		char* str = reinterpret_cast<char*>(HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, str_length));
#endif
		str[0] = 0;

		strcat(str, text);
		strcat(str, text_val);
		OutputDebugStringA(str);

#ifdef _WIN64
		virtual_caller.call_spoofed_function<BOOL>(HeapFree, GetProcessHeap(), HEAP_ZERO_MEMORY, str);
#else
		HeapFree(GetProcessHeap(), HEAP_ZERO_MEMORY, str);
#endif

	}
	
	void debug_text(const char* text, float val, uintptr_t spoof_caller_address) {
		
		char text_val[12];
		int meme;
		ftoa(val, text_val, 3);

		int str_length = strlen(text) + strlen(text_val) + 1;
#ifdef _WIN64
		g_cheat::memory::c_address virtual_caller(spoof_caller_address);
		char* str = reinterpret_cast<char*>(virtual_caller.call_spoofed_function<LPVOID>(HeapAlloc, GetProcessHeap(), HEAP_ZERO_MEMORY, str_length));
#else
		char* str = reinterpret_cast<char*>(HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, str_length));
#endif
		str[0] = 0;

		strcat(str, text);
		strcat(str, text_val);
		OutputDebugStringA(str);

#ifdef _WIN64
		virtual_caller.call_spoofed_function<BOOL>(HeapFree, GetProcessHeap(), HEAP_ZERO_MEMORY, str);
#else
		HeapFree(GetProcessHeap(), HEAP_ZERO_MEMORY, str);
#endif

		
	}

}