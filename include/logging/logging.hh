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

    enum class Sink
    {
        File,
        Null,
        Stdout,
        Syslog
    };

    class Logger
    {
    public:
        static spdlog::logger& get(std::optional<std::string> const& init = std::nullopt)
        {
            static Logger instance{init.value()};
            return instance._logger;
        }

        constexpr Logger(const Logger&)   = delete;
        constexpr Logger(const Logger&&)  = delete;

        constexpr Logger& operator=(const Logger&)  = delete;
        constexpr Logger& operator=(const Logger&&) = delete;

    private:
        Logger()  = delete;
        Logger(const std::string& name): _logger(spdlog::logger{name}) {}
        ~Logger() = default;

        spdlog::logger _logger;
    };

    inline void addSinks(const std::vector<Sink>& sinks)
    {
        auto& logger = Logger::get();

        for (const auto& elem : sinks)
        {
            switch (elem)
            {
                case Sink::File:
                    logger.sinks().push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("path"));
                    break;
                case Sink::Null:
                    logger.sinks().push_back(std::make_shared<spdlog::sinks::null_sink_mt>());
                    break;
                case Sink::Stdout:
                    logger.sinks().push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
                    break;
                case Sink::Syslog:
                    logger.sinks().push_back(std::make_shared<spdlog::sinks::syslog_sink_mt>("test-log", LOG_PID, LOG_USER, false));
                    break;
                default:
                    logger.critical("The requested logging sink does not exists.");
            }
        }
    }

    template<typename... Args>
    inline void critical(fmt::format_string<Args...> fmt, Args&& ...args)
    {
        Logger::get().critical(fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    inline void debug(fmt::format_string<Args...> fmt, Args&& ...args)
    {
        Logger::get().debug(fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    inline void error(fmt::format_string<Args...> fmt, Args&& ...args)
    {
        Logger::get().error(fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    inline void info(fmt::format_string<Args...> fmt, Args&& ...args)
    {
        Logger::get().info(fmt, std::forward<Args>(args)...);
    }

    inline void init(const std::string& name)
    {
        Logger::get(name);
    }

    template<typename... Args>
    inline void warn(fmt::format_string<Args...> fmt, Args&& ...args)
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
                Logger::get().critical("The requested logging level does not exists.");
        }
    }

    inline void setPattern(const std::string& pattern)
    {
        Logger::get().set_pattern(pattern);
    }
}

#endif // LOGGING_H
