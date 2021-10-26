
namespace g_cheat::memory {
    class c_thread_manager {
        std::map<std::string, std::thread> m_threads;
        HINSTANCE m_cheat_module;

    public:
        c_thread_manager() = default;

        void set_module_handle(HINSTANCE module_handle) {
            m_cheat_module = module_handle;
        }

        auto& get_threads() {
            return m_threads;
        }

        std::thread& operator[](const std::string& thread_name) {
            return m_threads[thread_name];
        }

        template <typename function_type_t, typename... args_t>
        void add_thread(const std::string& thread_name, function_type_t(*function_ptr)(args_t...), args_t... args) {
            m_threads[thread_name] = std::thread(function_ptr, args...);
        }

        void delete_thread(const std::string& thread_name) {
            m_threads[thread_name].join();
        }

        void delete_threads() {
            for (auto& current_thread : m_threads) {
                current_thread.second.join();
            }

            FreeLibrary(m_cheat_module);
        }
    };
}