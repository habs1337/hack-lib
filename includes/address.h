#pragma once


#if defined(_M_IX86)
#define MIN_POINTER_VAL uintptr_t(0x00000)
#define MAX_POINTER_VAL uintptr_t(0xFFF00000)
#elif defined(_M_X64)
#define MIN_POINTER_VAL uintptr_t(0x10000)
#define MAX_POINTER_VAL uintptr_t(0x000f000000000000)

extern "C" void* _spoofer_stub();
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

		template< typename t = c_address, typename a = size_t >
		__forceinline t as(a offset) const {
			return m_address ? t(m_address + offset) : t{};
		}

		template< typename t = c_address, typename a = size_t >
		__forceinline t at(a offset) const {
			return m_address ? *reinterpret_cast<t*>(m_address + offset) : t{};
		}

		template< typename t = c_address, typename a = size_t>
		__forceinline t add(a offset) const {
			return m_address ? t(m_address + offset) : t{};
		}


		template< typename t = c_address, typename a = size_t >
		__forceinline t sub(a offset) const {
			return (m_address) ? t(m_address - offset) : t{};
		}

		template< typename t = c_address >
		__forceinline t to() const {
			return  *reinterpret_cast<t*>(m_address);
		}

		template< typename t = c_address, typename a = size_t >
		__forceinline t to(a offset) const {
			return  *reinterpret_cast<t*>(m_address + offset);
		}

		bool is_valid() {
			return (uintptr_t)m_address >= MIN_POINTER_VAL && (uintptr_t)m_address < MAX_POINTER_VAL;
		}


		template< typename t = c_address >
		__forceinline t get() {
			return is_valid() ? t(m_address) : t{};
		}

		template< typename t = c_address, typename a = size_t >
		__forceinline t relative8(a offset = 2) {
			if (!is_valid())
				return t{};

			uintptr_t out = m_address + offset;
			uint8_t r = *reinterpret_cast<uint8_t*>(out);

			if (!r)
				return t{};

			//если размер второго опкода меньше 128 (80 в хексе) - функци€ находитс€ впереди (дальше, снизу), к следующему опкоду добавл€ем размер инструкции
			//если размер второго опкода меньше 128 (80 в хексе) - функци€ находитс€ сзади (раньше, сверху), от следующего опкода отнимаем инверснутые опкоды (с начала, права)
			//чтобы получить первый опкод предыдушей инструкции


			if (r < 128)
				out = (out + 1) + r;
			else
				out = (out + 1) - uint8_t(~r + 1);

			return intptr_t(out);
		}

		template< typename t = c_address, typename a = size_t >
		__forceinline t relative32(a instruction_size) {
			if (!is_valid())
				return t{};

			//мега умна€ калькул€ци€ котора€ находит нужные 4 опкода, в которых хранитс€ адрес вызываемой функции

			return intptr_t(m_address) + instruction_size + *reinterpret_cast<int32_t*>(intptr_t(m_address) + (instruction_size - 4));
		}

		template < typename t = uintptr_t >
		__forceinline void set(const t& value) {
			if (!is_valid())
				return;

			*reinterpret_cast<t*>(m_address) = value;
		}

		template <typename return_t, typename ...args_t>
		__forceinline return_t call_function(args_t... args) { //call from memory
			//function_ptr.call_function<function_return_type, void*, arg_type>(ptr_at_object, arg);
			return reinterpret_cast<return_t(*)(args_t...)>(m_address)(args...); //__stdcall
		}

		template <typename return_t, size_t index, typename ...args_t>
		__forceinline return_t call_virtual_function(args_t... args) { //call from memory
			//current_object.call_virtual_function<function_return_type, vtable_idx, arg_type>(arg);
			return reinterpret_cast<return_t(*)(uintptr_t, args_t...)>((*reinterpret_cast<uintptr_t**>(m_address))[index])(m_address, args...);
		}

		//call from your project to create your own cool callback system
		//better use std::function cuz lambdas

		//example of pushing lambdas
		//void(*test)(int) = lambda_function;
		//function_caller(test, lambdas_args);

		//example of getting function address
		//int* function_address = (int*)((uintptr_t)&function);

		template <typename ...args_t>
		void function_caller(void(*func)(args_t...), args_t... args) { 
			func(args...);
		}


		//trash fix cuz it`s don`t addapted for x86
#if(_M_X64)
		//m_address = address of first ff 27 opcodes
		//this->m_base_handle.find_pattern(XORSTR("\xFF\x27"), XORSTR("xx"))
		template<typename Ret = void, typename First = void*, typename Second = void*, typename Third = void*, typename Fourth = void*, typename... Stack>
		__forceinline Ret call_spoofed_function(void* Func, First a1 = First{}, Second a2 = Second{}, Third a3 = Third{}, Fourth a4 = Fourth{}, Stack... args) {
			struct shell_params { const void* a1; void* a2; void* a3; };
			shell_params CallCtx = { reinterpret_cast<const void*>(m_address), Func, nullptr };
			typedef Ret(*ShellFn)(First, Second, Third, Fourth, PVOID, PVOID, Stack...);
			return ((ShellFn)&_spoofer_stub)(a1, a2, a3, a4, &CallCtx, nullptr, args...);
		}

		//Spoof VFTable Return Address
		template<typename Ret = void, typename... Args>
		__forceinline Ret call_spoofed_virtual_function(PVOID Class, int Index, Args... AddArgs) {
			return call_spoofed_function<Ret>((*(PVOID**)Class)[Index], Class, AddArgs...);
		}
#endif
	};

}
