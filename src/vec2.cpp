#include "../includes/includes.h"


namespace g_cheat::sdk {
	
		c_vec2::c_vec2() {
			m_x = m_y = 0.f;
		}

		c_vec2::c_vec2(float x, float y) {
			m_x = x;
			m_y = y;
		}

		c_vec2::c_vec2(int x, int y) {
			m_x = x;
			m_y = y;
		}


		bool c_vec2::operator==(c_vec2 vec2) {
			return  m_x == vec2.m_x && m_y == vec2.m_y;
		}

		bool c_vec2::operator!=(c_vec2 vec2) {
			return m_x != vec2.m_x || m_y != vec2.m_y;
		}

		bool c_vec2::operator>=(c_vec2 vec2) {
			return (m_x > vec2.m_x && m_y > vec2.m_y) || (*this) == vec2;
		}

		bool c_vec2::operator<=(c_vec2 vec2) {
			return (m_x < vec2.m_x && m_y < vec2.m_y) || (*this) == vec2;
		}

		c_vec2& c_vec2::operator=(c_vec2 vec2) {
			m_x = vec2.m_x;
			m_y = vec2.m_y;
			return *this;
		}

		c_vec2& c_vec2::operator-() {
			m_x = -m_x;
			m_y = -m_y;
			return *this;
		}


		c_vec2 c_vec2::operator+(c_vec2 vec2) {
			return c_vec2(m_x + vec2.m_x, m_y + vec2.m_y);
		}

		c_vec2 c_vec2::operator-(c_vec2 vec2) {
			return c_vec2(m_x - vec2.m_x, m_y - vec2.m_y);
		}

		c_vec2 c_vec2::operator*(c_vec2 vec2) {
			return c_vec2(m_x * vec2.m_x, m_y * vec2.m_y);
		}

		c_vec2 c_vec2::operator/(c_vec2 vec2) {
			return c_vec2(m_x / vec2.m_x, m_y / vec2.m_y);
		}


		c_vec2& c_vec2::operator+=(c_vec2 vec2) {
			m_x += vec2.m_x;
			m_y += vec2.m_y;
			return *this;
		}

		c_vec2& c_vec2::operator-=(c_vec2 vec2) {
			m_x -= vec2.m_x;
			m_y -= vec2.m_y;
			return *this;
		}

		c_vec2& c_vec2::operator*=(c_vec2 vec2) {
			m_x *= vec2.m_x;
			m_y *= vec2.m_y;
			return *this;
		}

		c_vec2& c_vec2::operator/=(c_vec2 vec2) {
			m_x /= vec2.m_x;
			m_y /= vec2.m_y;
			return *this;
		}

		c_vec2 c_vec2::operator>(c_vec2 vec2) {
			return (*this) >= vec2 ? (*this) : vec2;
		}

		c_vec2 c_vec2::operator<(c_vec2 vec2) {
			return (*this) <= vec2 ? (*this) : vec2;
		}



		c_vec2 c_vec2::operator+(float val) {
			return c_vec2(m_x + val, m_y + val);
		}

		c_vec2 c_vec2::operator-(float val) {
			return c_vec2(m_x - val, m_y - val);
		}

		c_vec2 c_vec2::operator*(float val) {
			return c_vec2(m_x * val, m_y * val);
		}

		c_vec2 c_vec2::operator/(float val) {
			return c_vec2(m_x / val, m_y / val);
		}


		c_vec2& c_vec2::operator+=(float val) {
			m_x += val;
			m_y += val;
			return *this;
		}

		c_vec2& c_vec2::operator-=(float val) {
			m_x -= val;
			m_y -= val;
			return *this;
		}

		c_vec2& c_vec2::operator*=(float val) {
			m_x *= val;
			m_y *= val;
			return *this;
		}

		c_vec2& c_vec2::operator/=(float val) {
			m_x /= val;
			m_y /= val;
			return *this;
		}


		float& c_vec2::get_x() {
			return m_x;
		}

		float& c_vec2::get_y() {
			return m_y;
		}


		c_vec2 c_vec2::get_positive() {
			c_vec2 t(m_x, m_y);

			if (t.m_x < 0.f) {
				t.m_x = -t.m_x;
			}

			if (t.m_y < 0.f) {
				t.m_y = -t.m_y;
			}

			return t;
		}


		float c_vec2::get_dot(c_vec2& vec2) {
			return m_x * vec2.m_x + m_y * vec2.m_y;
		}

		float c_vec2::get_dot(float val) {
			return m_x * val + m_y * val;
		}


		float c_vec2::get_length_sqr() {
			return m_x * m_x + m_y * m_y;
		}



		float c_vec2::length() {
			return math::sqrt(get_length_sqr());
		}

		c_vec2 c_vec2::angle_normalize() {
			if (m_x > 180.f)
				m_x -= 360.f;
			else if (m_x < -180.f)
				m_x += 360.f;

			if (m_y > 180.f)
				m_y -= 360.f;
			else if (m_y < -180.f)
				m_y += 360.f;

			return *this;
		}

		float c_vec2::dist_to(c_vec2& vec2) {
			return ((*this) - vec2).length();
		}

}