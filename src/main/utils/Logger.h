/**
 * @file Logger.h
 * @brief Describes the Logger singleton
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2018-11-17
 */
#ifndef LOGGER_H
#define LOGGER_H

#include <memory>
#include <mutex>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

class Logger {

public:

    ~Logger();

    static std::shared_ptr<Logger>& Instance();

    void debug(std::string message);
    void info(std::string message);
    void critical(std::string message);
    void warn(std::string message);

private:
    Logger();
    Logger(const Logger& l) = delete;
    Logger& operator=(const Logger& l) = delete;

    static std::shared_ptr<Logger> instance;
    std::shared_ptr<spdlog::logger> logger;
    /* static std::mutex mutex; */
};

#endif /* ifndef LOGGER_H */
