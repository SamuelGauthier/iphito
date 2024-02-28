/**
 * @file Logger.cpp
 * @brief Implements the Logger singleton
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2018-11-17
 */

#include <memory>
#include <mutex>

#include "Logger.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace iphito::utils {

std::shared_ptr<Logger> Logger::instance = nullptr;

std::shared_ptr<Logger>& Logger::Instance() {

    if(!Logger::instance) {

        /* std::lock_guard<std::mutex> lock(Logger::t_mutex); */

        /* if(!Logger::instance) { */
        Logger::instance.reset(new Logger());
        /* } */
    }

    return instance;
}

Logger::Logger() {
    
    this->logger = spdlog::stdout_color_mt("console");
    this->logger->set_level(spdlog::level::debug);
}

Logger::~Logger() {
    // ?
    Logger::instance = nullptr;
}

void Logger::debug(std::string message) {
    logger->debug(message);
}

void Logger::info(std::string message) {
    logger->info(message);
}

void Logger::critical(std::string message) {
    logger->critical(message);
}

void Logger::warn(std::string message) {
    logger->warn(message);
}

} /* namespace iphito::utils */
