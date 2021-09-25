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

		g_cheat::sdk::c_color c_color::from_hsb(float hue, float saturation, float brightness)
		{
			float h = hue == 1.0f ? 0 : hue * 6.0f;
			float f = h - (int)h;
			float p = brightness * (1.0f - saturation);
			float q = brightness * (1.0f - saturation * f);
			float t = brightness * (1.0f - (saturation * (1.0f - f)));

			if (h < 1)
			{
				return g_cheat::sdk::c_color(
					(unsigned char)(brightness * 255),
					(unsigned char)(t * 255),
					(unsigned char)(p * 255)
				);
			}
			else if (h < 2)
			{
				return g_cheat::sdk::c_color(
					(unsigned char)(q * 255),
					(unsigned char)(brightness * 255),
					(unsigned char)(p * 255)
				);
			}
			else if (h < 3)
			{
				return g_cheat::sdk::c_color(
					(unsigned char)(p * 255),
					(unsigned char)(brightness * 255),
					(unsigned char)(t * 255)
				);
			}
			else if (h < 4)
			{
				return g_cheat::sdk::c_color(
					(unsigned char)(p * 255),
					(unsigned char)(q * 255),
					(unsigned char)(brightness * 255)
				);
			}
			else if (h < 5)
			{
				return g_cheat::sdk::c_color(
					(unsigned char)(t * 255),
					(unsigned char)(p * 255),
					(unsigned char)(brightness * 255)
				);
			}
			else
			{
				return g_cheat::sdk::c_color(
					(unsigned char)(brightness * 255),
					(unsigned char)(p * 255),
					(unsigned char)(q * 255)
				);
			}
		}
}