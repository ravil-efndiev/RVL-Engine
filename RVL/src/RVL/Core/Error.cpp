#include "Error.hpp"

#include "Macros.hpp"

namespace rvl
{
    void rvl::Error::Print()
    {
        if (Status == RVL_RUNTIME_ERROR)
            std::cerr << RVL_LOG_COLOR_RED << "RUNTIME_ERROR => " << Text << RVL_LOG_COLOR_NONE << std::endl;
        else if (Status == RVL_INTERNAL_ERROR)
            std::cerr << RVL_LOG_COLOR_RED << "INTERNAL_ERROR => " << Text << RVL_LOG_COLOR_NONE << std::endl;
    }

    void Error::PrintErrorS(const std::string &text)
    {
        std::cerr << "RUNTIME_ERROR => " << text << std::endl;
    }
}