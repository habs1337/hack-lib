#pragma once

//added cuz i`ve got tired from this code, unfortunaly it`s still unfinished, prob someday it would be reworked
namespace g_cheat::memory {
    class c_async {
    public:

        std::future<int> m_async;
        std::promise<void> m_current_promise;
        template <typename function_type_t = void*, typename... args_t>
        void on_init(std::launch async_type, std::shared_future<void>& global_shared, function_type_t(*function_ptr)(args_t...), args_t... args) {
            m_async = std::async(async_type, [this, &global_shared, function_ptr, args...]()
            {
                this->m_current_promise.set_value();
                global_shared.wait();
                return function_ptr(args...);
            });
        }

        void prepare_async() {
            m_current_promise.get_future().wait();
        }

        template <typename function_type_t>
        function_type_t get_value() {
            return m_async.get();
        }
    };


    class c_async_manager {
        std::promise<void> m_global_promise;


        std::launch m_async_type;
        std::map<std::string, c_async> m_async;

        std::shared_future<void> m_global_shared_future;
    public:


        void on_init(std::launch async_type) {
            m_global_shared_future = m_global_promise.get_future();
            m_async_type = async_type;
        }

        void change_async_type(std::launch async_type) {
            m_async_type = async_type;
        }

        template <typename function_type_t, typename... args_t>
        void on_init_async(const char* async_name, function_type_t(*function_ptr)(args_t...), args_t... args) {
            m_async[async_name].on_init<function_type_t, args_t...>(m_async_type, m_global_shared_future, function_ptr, args...);
        }

        void prepare_async(const char* async_name) {
            //it`s gonna stop our async
            if (m_async_type == std::launch::deferred) {
                return;
            }

            m_async[async_name].prepare_async();
        }

        void launch_asyncs() {
            m_global_promise.set_value();
        }

        template<typename function_type_t>
        function_type_t get_value(const char* async_name) {
            return m_async[async_name].get_value<function_type_t>();
        }
    };
}


//int test_inc(cmd_t cmd, string async_name) {
//    cmd.m_base_value++;
//    std::this_thread::sleep_for(std::chrono::milliseconds(60));
//
//    printf("%s::tickcount:%i\n", async_name.c_str(), GetTickCount64());
//    printf("%s::id:%i\n", async_name.c_str(), std::this_thread::get_id());
//
//    return cmd.m_base_value;
//}
//
//bool test_positive(cmd_t cmd, string async_name) {
//    cmd.m_is_positive = true;
//    std::this_thread::sleep_for(std::chrono::milliseconds(60));
//
//    printf("%s::tickcount:%i\n", async_name.c_str(), GetTickCount64());
//    printf("%s::id:%i\n", async_name.c_str(), std::this_thread::get_id());
//
//    return cmd.m_is_positive;
//}
//
//c_async_manager async_manager;
//
//async_manager.on_init(std::launch::async);
//async_manager.on_init_async<int, cmd_t, string>("async1", test_inc, cmd, "async1");
//async_manager.on_init_async<bool, cmd_t, string>("async2", test_positive, cmd, "async2");
//
//
//
//async_manager.prepare_async("async1");
//async_manager.prepare_async("async2");
//
//async_manager.launch_asyncs();
//
//cmd.m_base_value = async_manager.get_value<int>("async1");
//cmd.m_is_positive = async_manager.get_value<bool>("async2");