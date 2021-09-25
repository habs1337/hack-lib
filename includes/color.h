#pragma once

#define SET_COLOR(name, clr) static c_color get_ ## name () { return clr; }

namespace g_cheat::sdk {

	class c_color {
		int hex_to_color(int hex, int color);
		int color_to_hex(int hex, int color);
	public:
		float r, g, b, a;

		__forceinline bool operator==(c_color col) const {
			return this->r == col.r && this->g == col.g && this->b == col.b && this->a == col.a;
		}

		c_color();
		c_color(float red, float green, float blue, float alpha = 255.f);
		c_color(int red, int green, int blue, int alpha = 255);
		c_color(int hex);

		void set_color(float red, float green, float blue, float alpha = 255.f);
		void set_color(int hex);

		c_color convert_hex_to_color(int hex);

		int convert_color_to_hex();

		static c_color from_hsb(float hue, float saturation, float brightness); // (health/10-1) * 0.033f, 1.f, 1.f

		SET_COLOR(red, c_color(255.f, 0.f, 0.f));
		SET_COLOR(green, c_color(0.f, 255.f, 0.f));
		SET_COLOR(blue, c_color(0.f, 0.f, 255.f));
		SET_COLOR(purple, c_color(255.f, 0.f, 255.f));
		SET_COLOR(bright_blue, c_color(0.f, 255.f, 255.f));
		SET_COLOR(yellow, c_color(255.f, 255.f, 0.f));
		SET_COLOR(white, c_color(255.f, 255.f, 255.f));
		SET_COLOR(black, c_color(0.f, 0.f, 0.f));


	};

}