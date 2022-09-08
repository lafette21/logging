#ifndef LOGGING_H
#define LOGGING_H

#include <spdlog/spdlog.h>

namespace logging
{
    enum class Level
    {
        TRACE,
        DEBUG,
        INFO,
        WARN,
        ERROR,
        CRITICAL,
        OFF
    };

    template<typename... T>
    inline void critical(fmt::format_string<T...> fmt, T&& ...args)
    {
        spdlog::critical(fmt, std::forward<T>(args)...);
    }

    template<typename... T>
    inline void debug(fmt::format_string<T...> fmt, T&& ...args)
    {
        spdlog::debug(fmt, std::forward<T>(args)...);
    }

    template<typename... T>
    inline void error(fmt::format_string<T...> fmt, T&& ...args)
    {
        spdlog::error(fmt, std::forward<T>(args)...);
    }

    template<typename... T>
    inline void info(fmt::format_string<T...> fmt, T&& ...args)
    {
        spdlog::info(fmt, std::forward<T>(args)...);
    }

    template<typename... T>
    inline void warn(fmt::format_string<T...> fmt, T&& ...args)
    {
        spdlog::warn(fmt, std::forward<T>(args)...);
    }

    inline void setLevel(const Level& level)
    {
        switch (level)
        {
            case Level::TRACE:
                spdlog::set_level(spdlog::level::trace);
                break;
            case Level::DEBUG:
                spdlog::set_level(spdlog::level::debug);
                break;
            case Level::INFO:
                spdlog::set_level(spdlog::level::info);
                break;
            case Level::WARN:
                spdlog::set_level(spdlog::level::warn);
                break;
            case Level::ERROR:
                spdlog::set_level(spdlog::level::err);
                break;
            case Level::CRITICAL:
                spdlog::set_level(spdlog::level::critical);
                break;
            case Level::OFF:
                spdlog::set_level(spdlog::level::off);
                break;
            default:
                critical("The requested logging level does not exists.");
        }
    }

    inline void setPattern(const std::string& pattern)
    {
        spdlog::set_pattern(pattern);
    }
}

#endif // LOGGING_H
