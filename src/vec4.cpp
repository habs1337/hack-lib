#include "../includes/includes.h"


namespace g_cheat::sdk {
	
		c_vec4::c_vec4() {
			m_x = m_y = m_z = m_w = 0.f;
		}

		c_vec4::c_vec4(float x, float y, float z, float w) {
			m_x = x;
			m_y = y;
			m_z = z;
			m_w = w;
		}

		c_vec4::c_vec4(int x, int y, int z, float w) {
			m_x = x;
			m_y = y;
			m_z = z;
			m_w = w;
		}


		bool c_vec4::operator==(c_vec4 vec4) {
			return  m_x == vec4.m_x && m_y == vec4.m_y && m_z == vec4.m_z && m_w == vec4.m_w;
		}

		bool c_vec4::operator!=(c_vec4 vec4) {
			return m_x != vec4.m_x || m_y != vec4.m_y || m_z != vec4.m_z || m_w != vec4.m_w;
		}

		bool c_vec4::operator>=(c_vec4 vec4) {
			return (m_x > vec4.m_x && m_y > vec4.m_y && m_z > vec4.m_z && m_w > vec4.m_w) || (*this) == vec4;
		}

		bool c_vec4::operator<=(c_vec4 vec4) {
			return (m_x < vec4.m_x&& m_y < vec4.m_y && m_z < vec4.m_z && m_w < vec4.m_w) || (*this) == vec4;;
		}

		c_vec4& c_vec4::operator=(c_vec4 vec4) {
			m_x = vec4.m_x;
			m_y = vec4.m_y;
			m_z = vec4.m_z;
			m_w = vec4.m_w;
			return *this;
		}

		c_vec4& c_vec4::operator-() {
			m_x = -m_x;
			m_y = -m_y;
			m_z = -m_z;
			m_w = -m_w;
			return *this;
		}


		c_vec4 c_vec4::operator+(c_vec4 vec4) {
			return c_vec4(m_x + vec4.m_x, m_y + vec4.m_y, m_z + vec4.m_z, m_w + vec4.m_w);
		}

		c_vec4 c_vec4::operator-(c_vec4 vec4) {
			return c_vec4(m_x - vec4.m_x, m_y - vec4.m_y, m_z - vec4.m_z, m_w - vec4.m_w);
		}

		c_vec4 c_vec4::operator*(c_vec4 vec4) {
			return c_vec4(m_x * vec4.m_x, m_y * vec4.m_y, m_z * vec4.m_z, m_w * vec4.m_w);
		}

		c_vec4 c_vec4::operator/(c_vec4 vec4) {
			return c_vec4(m_x / vec4.m_x, m_y / vec4.m_y, m_z / vec4.m_z, m_w / vec4.m_w);
		}


		c_vec4& c_vec4::operator+=(c_vec4 vec4) {
			m_x += vec4.m_x;
			m_y += vec4.m_y;
			m_z += vec4.m_z;
			m_w += vec4.m_w;
			return *this;
		}

		c_vec4& c_vec4::operator-=(c_vec4 vec4) {
			m_x -= vec4.m_x;
			m_y -= vec4.m_y;
			m_z -= vec4.m_z;
			m_w -= vec4.m_w;
			return *this;
		}

		c_vec4& c_vec4::operator*=(c_vec4 vec4) {
			m_x *= vec4.m_x;
			m_y *= vec4.m_y;
			m_z *= vec4.m_z;
			m_w *= vec4.m_w;
			return *this;
		}

		c_vec4& c_vec4::operator/=(c_vec4 vec4) {
			m_x /= vec4.m_x;
			m_y /= vec4.m_y;
			m_z /= vec4.m_z;
			m_w /= vec4.m_w;
			return *this;
		}

		c_vec4 c_vec4::operator>(c_vec4 vec4) {
			return (*this) >= vec4 ? (*this) : vec4;
		}

		c_vec4 c_vec4::operator<(c_vec4 vec4) {
			return (*this) <= vec4 ? (*this) : vec4;
		}

		c_vec4 c_vec4::operator+(float val) {
			return c_vec4(m_x + val, m_y + val, m_z + val, m_w + val);
		}

		c_vec4 c_vec4::operator-(float val) {
			return c_vec4(m_x - val, m_y - val, m_z - val, m_w - val);
		}

		c_vec4 c_vec4::operator*(float val) {
			return c_vec4(m_x * val, m_y * val, m_z * val, m_w * val);
		}

		c_vec4 c_vec4::operator/(float val) {
			return c_vec4(m_x / val, m_y / val, m_z / val, m_w / val);
		}


		c_vec4& c_vec4::operator+=(float val) {
			m_x += val;
			m_y += val;
			m_z += val;
			m_w += val;
			return *this;
		}

		c_vec4& c_vec4::operator-=(float val) {
			m_x -= val;
			m_y -= val;
			m_z -= val;
			m_w -= val;
			return *this;
		}

		c_vec4& c_vec4::operator*=(float val) {
			m_x *= val;
			m_y *= val;
			m_z *= val;
			m_w *= val;
			return *this;
		}

		c_vec4& c_vec4::operator/=(float val) {
			m_x /= val;
			m_y /= val;
			m_z /= val;
			m_w /= val;
			return *this;
		}

		float& c_vec4::get_x() {
			return m_x;
		}

		float& c_vec4::get_y() {
			return m_y;
		}

		float& c_vec4::get_z() {
			return m_z;
		}

		float& c_vec4::get_w() {
			return m_w;
		}

		c_vec4 c_vec4::get_positive() {
			c_vec4 t(m_x, m_y, m_z, m_w);

			if (t.m_x < 0.f) {
				t.m_x = -t.m_x;
			}

			if (t.m_y < 0.f) {
				t.m_y = -t.m_y;
			}

			if (t.m_z < 0.f) {
				t.m_z = -t.m_z;
			}

			if (t.m_w < 0.f) {
				t.m_w = -t.m_w;
			}

			return t;
		}


		float c_vec4::get_dot(c_vec4 vec4) {
			return m_x * vec4.m_x + m_y * vec4.m_y + m_z * vec4.m_z + m_w * vec4.m_w;
		}

		float c_vec4::get_dot(float val) {
			return m_x * val + m_y * val + m_z * val + m_w * val;
		}

		float c_vec4::get_length_4d_sqr() {
			return get_length_3d_sqr() + m_w * m_w;
		}

		float c_vec4::get_length_3d_sqr() {
			return get_length_2d_sqr() + m_z * m_z;
		}

		float c_vec4::get_length_2d_sqr() {
			return m_x * m_x + m_y * m_y;
		}

		float c_vec4::length_4d() {
			return math::sqrt(get_length_4d_sqr());
		}

		float c_vec4::length_3d() {
			return math::sqrt(get_length_3d_sqr());
		}

		float c_vec4::length_2d() {
			return math::sqrt(get_length_2d_sqr());
		}

		c_vec4 c_vec4::angle_normalize() {
			if (m_x > 180.f)
				m_x -= 360.f;
			else if (m_x < -180.f)
				m_x += 360.f;

			if (m_y > 180.f)
				m_y -= 360.f;
			else if (m_y < -180.f)
				m_y += 360.f;

			m_z = 0.f;

			return *this;
		}

		float c_vec4::vector_normalize() {
			auto previous_length = length_3d();

			(*this) /= (previous_length + FLT_EPSILON);
			return previous_length;
		}

		c_vec4 c_vec4::vector_normalized() {
			(*this).vector_normalize();
			return (*this);
		}

		float c_vec4::dist_to_4d(c_vec4 vec4) {
			return ((*this) - vec4).length_4d();
		}

		float c_vec4::dist_to_3d(c_vec4 vec4) {
			return ((*this) - vec4).length_3d();
		}

		float c_vec4::dist_to_2d(c_vec4 vec4) {
			return ((*this) - vec4).length_2d();
		}

}

