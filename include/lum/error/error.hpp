#pragma once
#include <string>

namespace lum{
    class Error{
    public:
        explicit Error(std::string source);
        static void throw_err(std::string msg, int, int);
        [[noreturn]] static void throw_and_return(std::string msg, int, int);

    private:
        std::string msg;

    };
}
