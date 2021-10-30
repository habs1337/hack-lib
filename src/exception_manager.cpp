#include "../includes/includes.h"

namespace g_cheat::memory::exception_manager {

    PVOID exception_status = 0;
    size_t logs_counter = 0;
    uintptr_t base_module_handle = 0;


    LONG WINAPI handle_exception(struct _EXCEPTION_POINTERS* ExceptionInfo)
    {
        PCONTEXT context = ExceptionInfo->ContextRecord;

        PEXCEPTION_RECORD exception_record = ExceptionInfo->ExceptionRecord;

#ifdef _AMD64_
        context->Rip++;
#else
        context->Eip++;
#endif    

#ifdef LOGS_PATH
        std::string path = LOGS_PATH;
        path += "log_" + std::to_string(logs_counter);
        std::ofstream outfile(path);

        if (outfile.is_open() && outfile.good()) {
            outfile << "exception address:" << exception_record->ExceptionAddress << std::endl
                << "exception offset:" << reinterpret_cast<uintptr_t>(exception_record->ExceptionAddress) - base_module_handle << std::endl
                << "exception code:" << exception_record->ExceptionCode << std::endl
                << "exception flags:" << exception_record->ExceptionFlags << std::endl
                << "exception information:" << exception_record->ExceptionInformation << std::endl
                << "exception parameters:" << exception_record->NumberParameters << std::endl;


            outfile.close();
            logs_counter++;
        }
        else {
            g_mini_crt::string::debug_text("could not write to file!");
            g_mini_crt::string::debug_integer("exception offset", reinterpret_cast<uintptr_t>(exception_record->ExceptionAddress) - base_module_handle, 16, 0);
        }
#else
        g_mini_crt::string::debug_integer("exception offset", reinterpret_cast<uintptr_t>(exception_record->ExceptionAddress) - base_module_handle, 16, 0);
#endif
        return EXCEPTION_CONTINUE_EXECUTION;
    }


    void on_work() {
        exception_status = AddVectoredExceptionHandler(1, handle_exception); //CALL_FIRST
    }

    void on_stop() {
        if (exception_status) {
            RemoveVectoredExceptionHandler(exception_status);
        }
    }

    void set_module_base(uintptr_t module_base) {
        base_module_handle = module_base;
    }
}

