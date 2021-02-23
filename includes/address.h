#pragma once


#if defined(_M_IX86)
#define MAX_POINTER_VAL uintptr_t(0xFFF00000)
#elif defined(_M_X64)
#define MAX_POINTER_VAL uintptr_t(0x000f000000000000)
#endif

namespace g_cheat::memory {

	class c_address {
		uintptr_t m_address;
	public:
		__forceinline c_address() {
			m_address = 0;
		}

		__forceinline c_address(uintptr_t a) {
			m_address = a;
		}

		__forceinline c_address(const void* a) {
			m_address = uintptr_t(a);
		}

		__forceinline operator uintptr_t() {
			return m_address;
		}

		__forceinline operator void* () {
			return reinterpret_cast<void*>(m_address);
		}

		__forceinline operator const void* () {
			return reinterpret_cast<const void*>(m_address);
		}

		template< typename t = c_address >
		__forceinline t operator+=(size_t a) {
			this->m_address += a;
			return *this;
		}

		template< typename t = c_address >
		__forceinline t operator-=(size_t a) {
			this->m_address -= a;
			return *this;
		}

		__forceinline bool operator==(c_address a) const {
			return this->as< uintptr_t >() == a.as< uintptr_t >();
		}

		__forceinline bool operator!=(c_address a) const {
			return this->as< uintptr_t >() != a.as< uintptr_t >();
		}

		__forceinline bool operator>=(c_address a) const {
			return this->as< uintptr_t >() >= a.as< uintptr_t >();
		}

		__forceinline bool operator<=(c_address a) const {
			return this->as< uintptr_t >() <= a.as< uintptr_t >();
		}		

		__forceinline bool operator>(c_address a) const {
			return this->as< uintptr_t >() > a.as< uintptr_t >();
		}

		__forceinline bool operator<(c_address a) const {
			return this->as< uintptr_t >() < a.as< uintptr_t >();
		}


		template< typename t = c_address >
		__forceinline t as() const {
			return m_address ? t(m_address) : t{};
		}

		template< typename t = c_address >
		__forceinline t as(size_t offset) const {
			return m_address ? t(m_address + offset) : t{};
		}

		template< typename t = c_address >
		__forceinline t as(intptr_t offset) const {
			return m_address ? t(m_address + offset) : t{};
		}

		template< typename t = c_address >
		__forceinline t at(size_t offset) const {
			return m_address ? *reinterpret_cast<t*>(m_address + offset) : t{};
		}

		template< typename t = c_address >
		__forceinline t at(intptr_t offset) const {
			return m_address ? *reinterpret_cast<t*>(m_address + offset) : t{};
		}

		template< typename t = c_address >
		__forceinline t add(size_t offset) const {
			return m_address ? t(m_address + offset) : t{};
		}

		template< typename t = c_address >
		__forceinline t add(intptr_t offset) const {
			return m_address ? t(m_address + offset) : t{};
		}

		template< typename t = c_address >
		__forceinline t sub(size_t offset) const {
			return (m_address) ? t(m_address - offset) : t{};
		}

		template< typename t = c_address >
		__forceinline t sub(intptr_t offset) const {
			return m_address ? t(m_address - offset) : t{};
		}

		template< typename t = c_address >
		__forceinline t to() const {
			return  *reinterpret_cast<t*>(m_address);
		}

		bool is_valid() {
			return m_address >= 0x10000 && m_address < MAX_POINTER_VAL;
		}


		template< typename t = c_address >
		__forceinline t get() {
			return is_valid() ? t(m_address) : t{};
		}

		template< typename t = c_address >
		__forceinline t relative8(size_t offset = 2) {
			if (!is_valid())
				return t{};

			uintptr_t out = m_address + offset;
			uint8_t r = *reinterpret_cast<uint8_t*>(out);

			if (!r)
				return t{};

			//если размер второго опкода меньше 128 (80 в хексе) - функция находится впереди (дальше, снизу), к следующему опкоду добавляем размер инструкции
			//если размер второго опкода меньше 128 (80 в хексе) - функция находится сзади (раньше, сверху), от следующего опкода отнимаем инверснутые опкоды (с начала, права)
			//чтобы получить первый опкод предыдушей инструкции


			if (r < 128)
				out = (out + 1) + r;
			else
				out = (out + 1) - uint8_t(~r + 1);

			//return reinterpret_cast<t>(out);
			m_address = reinterpret_cast<t>(out);
		}

		template< typename t = c_address >
		__forceinline t relative32(size_t instruction_size) {
			if (!is_valid())
				return t{};

			//мега умная калькуляция которая находит нужные 4 опкода, в которых хранится адрес вызываемой функции

			return intptr_t(m_address) + instruction_size + *reinterpret_cast<int32_t*>(intptr_t(m_address) + (instruction_size - 4));
			//m_address = intptr_t(m_address) + instruction_size + *reinterpret_cast<int32_t*>(intptr_t(m_address) + (instruction_size - 4));
		}

		template < typename t = uintptr_t >
		__forceinline void set(const t& value) {
			if (!is_valid())
				return;

			*reinterpret_cast<t*>(m_address) = value;
		}

		template <typename return_t, typename ...args_t>
		__forceinline return_t call_function(args_t... args) {
			//если эта функция находится в классе, в m_address должен храниться адрес самой функции, а первым аргументом пушится адрес объекта 
			return reinterpret_cast<return_t(*)(args_t...)>(m_address)(args...); //__stdcall
		}

		template <typename return_t, size_t index, typename ...args_t>
		__forceinline return_t call_virtual_function(args_t... args) {
			//в адресе хранится указатель на объект, а индекс вызываемой функции получается из аргументов
			//TODO: переписать
			return reinterpret_cast<return_t(*)(uintptr_t, args_t...)>((*reinterpret_cast<uintptr_t**>(m_address))[index])(m_address, args...);
		}

	};

}
