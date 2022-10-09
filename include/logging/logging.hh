#ifndef LOGGING_H
#define LOGGING_H

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/null_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/syslog_sink.h>

namespace logging
{
    enum class Level
    {
        Trace,
        Debug,
        Info,
        Warn,
        Error,
        Critical,
        Off
    };

    struct File {};
    struct Null {};
    struct Stdout {};
    struct Syslog {};

    class unreachable : public std::exception
    {
    public:
        const char* what() const noexcept override
        {
            return "Unreachable branch!";
        }
    };

    class Logger
    {
    public:
        constexpr Logger(const Logger&)   = delete;
        constexpr Logger(const Logger&&)  = delete;

        constexpr Logger& operator=(const Logger&)  = delete;
        constexpr Logger& operator=(const Logger&&) = delete;

    private:
        Logger()  = delete;
        Logger(const std::string& name): _logger(spdlog::logger{name}) {}
        ~Logger() = default;

        static spdlog::logger& get(std::optional<std::string> const& init = std::nullopt)
        {
            static Logger instance{init.value()};
            return instance._logger;
        }

        template<typename... Args> friend inline void critical(fmt::format_string<Args...>, Args&&...);
        template<typename... Args> friend inline void debug(fmt::format_string<Args...>, Args&&...);
        template<typename... Args> friend inline void error(fmt::format_string<Args...>, Args&&...);
        template<typename... Args> friend inline void info(fmt::format_string<Args...>, Args&&...);
        template<typename... Args> friend inline void warn(fmt::format_string<Args...>, Args&&...);

        template<typename T, typename... Args> friend inline void addSink(Args&&...);

        friend inline void init(const std::string&);
        friend inline void setLevel(const Level&);
        friend inline void setPattern(const std::string&);

        spdlog::logger _logger;
    };

    template<typename T, typename... Args>
    inline void addSink(Args&&... args)
    {
        if constexpr (std::is_same_v<T, Null>)
        {
            Logger::get().sinks().push_back(std::make_shared<spdlog::sinks::null_sink_mt>());
        }
        else if constexpr (std::is_same_v<T, Stdout>)
        {
            Logger::get().sinks().push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
        }
        else if constexpr (std::is_same_v<T, File>)
        {
            Logger::get().sinks().push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(std::forward<Args>(args)...));
        }
        else if constexpr (std::is_same_v<T, Syslog>)
        {
            Logger::get().sinks().push_back(std::make_shared<spdlog::sinks::syslog_sink_mt>(std::forward<Args>(args)..., LOG_PID, LOG_USER, false));
        }
        else
        {
            throw unreachable();
        }
    }

    template<typename... Args>
    inline void critical(fmt::format_string<Args...> fmt, Args&&... args)
    {
        Logger::get().critical(fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    inline void debug(fmt::format_string<Args...> fmt, Args&&... args)
    {
        Logger::get().debug(fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    inline void error(fmt::format_string<Args...> fmt, Args&&... args)
    {
        Logger::get().error(fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    inline void info(fmt::format_string<Args...> fmt, Args&&... args)
    {
        Logger::get().info(fmt, std::forward<Args>(args)...);
    }

    inline void init(const std::string& name)
    {
        Logger::get(name);
    }

    template<typename... Args>
    inline void warn(fmt::format_string<Args...> fmt, Args&&... args)
    {
        Logger::get().warn(fmt, std::forward<Args>(args)...);
    }

    inline void setLevel(const Level& level)
    {
        switch (level)
        {
            case Level::Trace:
                Logger::get().set_level(spdlog::level::trace);
                break;
            case Level::Debug:
                Logger::get().set_level(spdlog::level::debug);
                break;
            case Level::Info:
                Logger::get().set_level(spdlog::level::info);
                break;
            case Level::Warn:
                Logger::get().set_level(spdlog::level::warn);
                break;
            case Level::Error:
                Logger::get().set_level(spdlog::level::err);
                break;
            case Level::Critical:
                Logger::get().set_level(spdlog::level::critical);
                break;
            case Level::Off:
                Logger::get().set_level(spdlog::level::off);
                break;
            default:
                throw unreachable();
        }
    }

    inline void setPattern(const std::string& pattern)
    {
        Logger::get().set_pattern(pattern);
    }
}

#endif // LOGGING_H
