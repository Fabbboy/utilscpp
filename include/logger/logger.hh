#ifndef UCPP_LOGGER
#define UCPP_LOGGER
#define UCPP_LOGGER_ENV "UCPP_LOG_LEVEL"

#include <chrono>
#include <cstdarg>
#include <fstream>
#include <iostream>
#include <string>

namespace ucpp {
enum class OuputDevice { OD_STDIO, OD_FSTREAM, OD_CUSTOM };
enum class LogLevel { LL_DESABLED, LL_DEBUG, LL_COUNT };
using LogHandler = void (*)(const std::string &, void *);

static inline void __def_stdio_handler(const std::string &msg, void *) {
  std::cout << msg << std::endl;
}

static inline void __def_fstream_handler(const std::string &msg, void *) {
  auto now = std::chrono::system_clock::now();
  auto now_c = std::chrono::system_clock::to_time_t(now);
  std::string filename = "log-" + std::to_string(now_c) + ".log";
  std::ofstream file(filename);
  file << msg << std::endl;
  file.close();
}

class Logger {
private:
  OuputDevice m_device = OuputDevice::OD_STDIO;
  LogHandler m_handler = nullptr;
  LogLevel m_level = LogLevel::LL_DESABLED;

private:
  inline LogLevel get_log_level() const {
    const char *env = std::getenv(UCPP_LOGGER_ENV);
    unsigned int level = env ? std::atoi(env) : 0;
    if (level >= static_cast<unsigned int>(LogLevel::LL_COUNT)) {
      std::cerr << "Invalid log level: " << level << std::endl;
      return LogLevel::LL_DESABLED;
    }
    return static_cast<LogLevel>(level);
  }

public:
  Logger();
  Logger(OuputDevice device, LogHandler handler = __def_stdio_handler);

  void set_log_level(LogLevel level) { m_level = level; }

  void debug(const std::string &msg, ...);
};
} // namespace ucpp

#ifndef UCPP_DISABLE_MACROS
extern ucpp::Logger global_logger;
#define UCPP_LEVEL(level)                                                      \
  setenv(UCPP_LOGGER_ENV,                                                      \
         std::to_string(static_cast<unsigned int>(level)).c_str(), 1);         \
  global_logger.set_log_level(level);
#define UCPP_DEBUG(msg, ...) global_logger.debug(msg, ##__VA_ARGS__)
#else
#define UCPP_LEVEL(level)                                                      \
  setenv(UCPP_LOGGER_ENV,                                                      \
         std::to_string(static_cast<unsigned int>(level)).c_str(), 1)
#define UCPP_DEBUG(msg, ...)
#endif
#endif