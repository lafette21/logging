#ifndef LOGGING_H
#define LOGGING_H

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

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

    template<typename T>
    class Singleton
    {
    public:
        static T& get()
        {
            static T instance;
            return instance;
        }

        constexpr Singleton(const Singleton&)   = delete;
        constexpr Singleton(const Singleton&&)  = delete;

        constexpr Singleton& operator=(const Singleton&)  = delete;
        constexpr Singleton& operator=(const Singleton&&) = delete;

    private:
        Singleton()  = default;
        ~Singleton() = default;
    };

    template<typename T>
    using Logger = Singleton<T>;

    class Console
    {
    public:
        Console()
        {
            _logger = spdlog::stdout_color_mt("console");
        }

        ~Console()
        {
            spdlog::drop("console");
        }

        template<typename... Args>
        inline void critical(fmt::format_string<Args...> fmt, Args&& ...args)
        {
            _logger->critical(fmt, std::forward<Args>(args)...);
        }

        template<typename... Args>
        inline void debug(fmt::format_string<Args...> fmt, Args&& ...args)
        {
            _logger->debug(fmt, std::forward<Args>(args)...);
        }

        template<typename... Args>
        inline void error(fmt::format_string<Args...> fmt, Args&& ...args)
        {
            _logger->error(fmt, std::forward<Args>(args)...);
        }

        template<typename... Args>
        inline void info(fmt::format_string<Args...> fmt, Args&& ...args)
        {
            _logger->info(fmt, std::forward<Args>(args)...);
        }

        template<typename... Args>
        inline void warn(fmt::format_string<Args...> fmt, Args&& ...args)
        {
            _logger->warn(fmt, std::forward<Args>(args)...);
        }

        inline void setLevel(const Level& level)
        {
            switch (level)
            {
                case Level::TRACE:
                    _logger->set_level(spdlog::level::trace);
                    break;
                case Level::DEBUG:
                    _logger->set_level(spdlog::level::debug);
                    break;
                case Level::INFO:
                    _logger->set_level(spdlog::level::info);
                    break;
                case Level::WARN:
                    _logger->set_level(spdlog::level::warn);
                    break;
                case Level::ERROR:
                    _logger->set_level(spdlog::level::err);
                    break;
                case Level::CRITICAL:
                    _logger->set_level(spdlog::level::critical);
                    break;
                case Level::OFF:
                    _logger->set_level(spdlog::level::off);
                    break;
                default:
                    _logger->critical("The requested logging level does not exists.");
            }
        }

        inline void setPattern(const std::string& pattern)
        {
            _logger->set_pattern(pattern);
        }

    private:
        std::shared_ptr<spdlog::logger> _logger;
    };

    template<typename Stream = Console, typename... Args>
    inline void critical(fmt::format_string<Args...> fmt, Args&& ...args)
    {
        Logger<Stream>::get().critical(fmt, std::forward<Args>(args)...);
    }

    template<typename Stream = Console, typename... Args>
    inline void debug(fmt::format_string<Args...> fmt, Args&& ...args)
    {
        Logger<Stream>::get().debug(fmt, std::forward<Args>(args)...);
    }

    template<typename Stream = Console, typename... Args>
    inline void error(fmt::format_string<Args...> fmt, Args&& ...args)
    {
        Logger<Stream>::get().error(fmt, std::forward<Args>(args)...);
    }

    template<typename Stream = Console, typename... Args>
    inline void info(fmt::format_string<Args...> fmt, Args&& ...args)
    {
        Logger<Stream>::get().info(fmt, std::forward<Args>(args)...);
    }

    template<typename Stream = Console, typename... Args>
    inline void warn(fmt::format_string<Args...> fmt, Args&& ...args)
    {
        Logger<Stream>::get().warn(fmt, std::forward<Args>(args)...);
    }

    template<typename Stream = Console>
    inline void setLevel(const Level& level)
    {
        Logger<Stream>::get().setLevel(level);
    }

    template<typename Stream = Console>
    inline void setPattern(const std::string& pattern)
    {
        Logger<Stream>::get().setPattern(pattern);
    }
}

#endif // LOGGING_H
