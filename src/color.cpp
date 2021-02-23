#include "../includes/includes.h"

namespace g_cheat::sdk {

		c_color::c_color() {
			r = g = b = a = 0;
		}

		c_color::c_color(float red, float green, float blue, float alpha) {
			r = red;
			g = green;
			b = blue;
			a = alpha;
		}

		c_color::c_color(int red, int green, int blue, int alpha) {
			r = red;
			g = green;
			b = blue;
			a = alpha;
		}

		c_color::c_color(int hex) {
			(*this) = convert_hex_to_color(hex);
		}


		void c_color::set_color(float red, float green, float blue, float alpha) {
			r = red;
			g = green;
			b = blue;
			a = alpha;
		}

		void c_color::set_color(int hex) {
			(*this) = convert_hex_to_color(hex);
		}

		int c_color::hex_to_color(int hex, int color) {
			return ((hex >> color) & 0xFF) /*/ 255.f*/;
		}

		int c_color::color_to_hex(int hex, int color) {
			return ((color & 0xFF) << hex);

		}

		c_color c_color::convert_hex_to_color(int hex) {
			return c_color(hex_to_color(hex, 16), hex_to_color(hex, 8), hex_to_color(hex, 0), hex_to_color(hex, 24));
		}

		int c_color::convert_color_to_hex() {
			return ((color_to_hex(24, r) + color_to_hex(16, g) + color_to_hex(8, b)) + color_to_hex(0, a));
		}

}