#include "../includes/includes.h"


namespace g_cheat::sdk {
	
		c_vec3::c_vec3() {
			m_x = m_y = m_z = 0.f;
		}

		c_vec3::c_vec3(float x, float y, float z) {
			m_x = x;
			m_y = y;
			m_z = z;
		}

		c_vec3::c_vec3(int x, int y, int z) {
			m_x = x;
			m_y = y;
			m_z = z;
		}


		bool c_vec3::operator==(c_vec3 vec3) {
			return  m_x == vec3.m_x && m_y == vec3.m_y && m_z == vec3.m_z;
		}

		bool c_vec3::operator!=(c_vec3 vec3) {
			return m_x != vec3.m_x || m_y != vec3.m_y || m_z != vec3.m_z;
		}

		bool c_vec3::operator>=(c_vec3 vec3) {
			return (m_x > vec3.m_x && m_y > vec3.m_y && m_z > vec3.m_z) || (*this) == vec3;
		}

		bool c_vec3::operator<=(c_vec3 vec3) {
			return (m_x < vec3.m_x && m_y < vec3.m_y && m_z < vec3.m_z) || (*this) == vec3;;
		}

		c_vec3& c_vec3::operator=(c_vec3 vec3) {
			m_x = vec3.m_x;
			m_y = vec3.m_y;
			m_z = vec3.m_z;
			return *this;
		}

		c_vec3& c_vec3::operator-() {
			m_x = -m_x;
			m_y = -m_y;
			m_z = -m_z;
			return *this;
		}


		c_vec3 c_vec3::operator+(c_vec3 vec3) {
			return c_vec3(m_x + vec3.m_x, m_y + vec3.m_y, m_z + vec3.m_z);
		}

		c_vec3 c_vec3::operator-(c_vec3 vec3) {
			return c_vec3(m_x - vec3.m_x, m_y - vec3.m_y, m_z - vec3.m_z);
		}

		c_vec3 c_vec3::operator*(c_vec3 vec3) {
			return c_vec3(m_x * vec3.m_x, m_y * vec3.m_y, m_z * vec3.m_z);
		}

		c_vec3 c_vec3::operator/(c_vec3 vec3) {
			return c_vec3(m_x / vec3.m_x, m_y / vec3.m_y, m_z / vec3.m_z);
		}


		c_vec3& c_vec3::operator+=(c_vec3 vec3) {
			m_x += vec3.m_x;
			m_y += vec3.m_y;
			m_z += vec3.m_z;
			return *this;
		}

		c_vec3& c_vec3::operator-=(c_vec3 vec3) {
			m_x -= vec3.m_x;
			m_y -= vec3.m_y;
			m_z -= vec3.m_z;
			return *this;
		}

		c_vec3& c_vec3::operator*=(c_vec3 vec3) {
			m_x *= vec3.m_x;
			m_y *= vec3.m_y;
			m_z *= vec3.m_z;
			return *this;
		}

		c_vec3& c_vec3::operator/=(c_vec3 vec3) {
			m_x /= vec3.m_x;
			m_y /= vec3.m_y;
			m_z /= vec3.m_z;
			return *this;
		}

		c_vec3 c_vec3::operator>(c_vec3 vec3) {
			return (*this) >= vec3 ? (*this) : vec3;
		}

		c_vec3 c_vec3::operator<(c_vec3 vec3) {
			return (*this) <= vec3 ? (*this) : vec3;
		}

		c_vec3 c_vec3::operator+(float val) {
			return c_vec3(m_x + val, m_y + val, m_z + val);
		}

		c_vec3 c_vec3::operator-(float val) {
			return c_vec3(m_x - val, m_y - val, m_z - val);
		}

		c_vec3 c_vec3::operator*(float val) {
			return c_vec3(m_x * val, m_y * val, m_z * val);
		}

		c_vec3 c_vec3::operator/(float val) {
			return c_vec3(m_x / val, m_y / val, m_z / val);
		}


		c_vec3& c_vec3::operator+=(float val) {
			m_x += val;
			m_y += val;
			m_z += val;
			return *this;
		}

		c_vec3& c_vec3::operator-=(float val) {
			m_x -= val;
			m_y -= val;
			m_z -= val;
			return *this;
		}

		c_vec3& c_vec3::operator*=(float val) {
			m_x *= val;
			m_y *= val;
			m_z *= val;
			return *this;
		}

		c_vec3& c_vec3::operator/=(float val) {
			m_x /= val;
			m_y /= val;
			m_z /= val;
			return *this;
		}


		float& c_vec3::get_x() {
			return m_x;
		}

		float& c_vec3::get_y() {
			return m_y;
		}

		float& c_vec3::get_z() {
			return m_z;
		}

		c_vec3 c_vec3::get_positive() {
			c_vec3 t(m_x, m_y, m_z);

			if (t.m_x < 0.f) {
				t.m_x = -t.m_x;
			}

			if (t.m_y < 0.f) {
				t.m_y = -t.m_y;
			}

			if (t.m_z < 0.f) {
				t.m_z = -t.m_z;
			}

			return t;
		}


		float c_vec3::get_dot(c_vec3 vec3) {
			return m_x * vec3.m_x + m_y * vec3.m_y + m_z * vec3.m_z;
		}

		float c_vec3::get_dot(float val) {
			return m_x * val + m_y * val + m_z * val;
		}

		c_vec3 c_vec3::get_cross(c_vec3 vec3) {
			return c_vec3(m_y * vec3.m_z - m_z * vec3.m_y,
				m_z * vec3.m_x - m_x * vec3.m_z, 
				m_x * vec3.m_y - m_y * vec3.m_x);
		}

		c_vec3 c_vec3::get_cross(float val) {
			return c_vec3(m_y * val - m_z * val,
				m_z * val - m_x * val,
				m_x * val - m_y * val);
		}

		float c_vec3::get_length_3d_sqr() {
			return get_length_2d_sqr() + m_z * m_z;
		}

		float c_vec3::get_length_2d_sqr() {
			return m_x * m_x + m_y * m_y;
		}


		float c_vec3::length_3d() {
			return math::sqrt(get_length_3d_sqr());
		}

		float c_vec3::length_2d() {
			return math::sqrt(get_length_2d_sqr());
		}

		c_vec3 c_vec3::angle_normalize() {
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

		float c_vec3::vector_normalize() {
			auto previous_length = length_3d();

			(*this) /= (previous_length + FLT_EPSILON);
			return previous_length;
		}

		c_vec3 c_vec3::vector_normalized() {
			(*this).vector_normalize();
			return (*this);
		}

		float c_vec3::dist_to_3d(c_vec3 vec3) {
			return ((*this) - vec3).length_3d();
		}

		float c_vec3::dist_to_2d(c_vec3 vec3) {
			return ((*this) - vec3).length_2d();
		}
	
		c_vec3 c_vec3::matrix_mutliply(g_cheat::sdk::c_matrix4x4 matrix) {
			return  c_vec3(matrix.m[0][0] * this->m_x + matrix.m[1][0] * this->m_y + matrix.m[2][0] * this->m_z,
				matrix.m[0][1] * this->m_x + matrix.m[1][1] * this->m_y + matrix.m[2][1] * this->m_z,
				matrix.m[0][2] * this->m_x + matrix.m[1][2] * this->m_y + matrix.m[2][2] * this->m_z);
		}
}