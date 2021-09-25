
namespace g_mini_crt::memory {

	//todo::rework to more effective memory-managment
	template <typename array_t, int max_size = 128>
	class c_vector {
		int m_current_size;
		array_t m_data[max_size] = {};
		array_t m_empty = {};
	public:

		array_t& operator[](int index)
		{
			if (index < m_current_size && index >= 0 && !is_empty()) {
				return m_data[index];
			}

			return m_empty;
		}

		c_vector() {
			m_current_size = 0;
		}

		int size() {
			return m_current_size;
		}

		bool is_empty() {
			return m_current_size == 0;

		}

		bool is_full() {
			return m_current_size == max_size;
		}

		void push_front(array_t element) {
			if (is_full()) {
				return;
			}

			for (int i = m_current_size - 1; i >= 0; i--) {
				m_data[i + 1] = m_data[i];
			}

			m_current_size++;
			m_data[0] = element;
		}

		void push_back(array_t element) {
			if (is_full()) {
				return;
			}

			m_data[m_current_size++] = element;
		}

		array_t front() {
			if (is_empty()) {
				return m_empty;
			}

			return m_data[0];
		}

		array_t back() {
			if (is_empty()) {
				return m_empty;
			}

			return m_data[m_current_size - 1];
		}

		array_t& at(int index) {
			if (index < m_current_size && index >= 0 && !is_empty()) {
				return m_data[index];
			}

			return m_empty;
		}


		void erase_front() {
			if (is_empty()) {
				return;
			}

			m_data[0] = m_empty;

			for (int i = 0; i < m_current_size - 1; i++) {
				m_data[i] = m_data[i + 1];
			}

			m_current_size--;

		}

		void erase_back() {
			if (is_empty()) {
				return;
			}

			m_current_size--;
			m_data[m_current_size] = m_empty;
		}

		void erase_element(int index) {
			if (index > m_current_size || index < 0 || is_empty()) {
				return;
			}

			m_data[index] = m_empty;

			for (int i = index; i < m_current_size - 1; i++) {
				m_data[i] = m_data[i + 1];
			}
			m_current_size--;
		}

	};

}

