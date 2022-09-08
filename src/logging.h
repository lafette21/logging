#ifndef LOGGING_H
#define LOGGING_H

#include <spdlog/spdlog.h>

namespace logging
{
    template<typename... T>
    inline void info(fmt::format_string<T...> fmt, T&& ...args)
    {
        spdlog::info(fmt, std::forward<T>(args)...);
    }
}

#endif // LOGGING_H
