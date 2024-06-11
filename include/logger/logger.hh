#ifndef UCPP_LOGGER
#define UCPP_LOGGER
#define UCPP_LOGGER_ENV "UCPP_LOG_LEVEL"

#include <chrono>
#include <cstdarg>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

namespace ucpp {
enum class OuputDevice { OD_STDIO, OD_FSTREAM, OD_CUSTOM };
enum class LogLevel { LL_DISABLED, LL_DEBUG, LL_COUNT };
using LogHandler = void (*)(const std::string &);

static inline void __def_stdio_handler(const std::string &msg) {
  std::cout << msg << std::endl;
}

static inline void __def_fstream_handler(const std::string &msg) {
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
  LogLevel m_level = LogLevel::LL_DISABLED;
  std::string m_logger;

private:
  inline LogLevel get_log_level() const {
    const char *env = std::getenv(UCPP_LOGGER_ENV);
    unsigned int level = env ? std::atoi(env) : 0;
    if (level >= static_cast<unsigned int>(LogLevel::LL_COUNT)) {
      std::cerr << "Invalid log level: " << level << std::endl;
      return LogLevel::LL_DISABLED;
    }
    return static_cast<LogLevel>(level);
  }

  inline std::string get_timestamp() const {
    std::string format = "%Y-%m-%dT%H:%M:%S";
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now_c), format.c_str());
    return ss.str();
  }

public:
  Logger(std::string logger = "DefaultLogger");
  Logger(OuputDevice device, LogHandler handler = __def_stdio_handler);

  void set_log_level(LogLevel level) { m_level = level; }
  void set_name(const std::string &name) { m_logger = name; }
  // logger
  void debug(const std::string &msg);
};

} // namespace ucpp

#ifndef UCPP_DISABLE_MACROS
extern ucpp::Logger global_logger;
#define UCPP_LEVEL(level)                                                      \
  setenv(UCPP_LOGGER_ENV,                                                      \
         std::to_string(static_cast<unsigned int>(level)).c_str(), 1);         \
  global_logger.set_log_level(level);
#define UCPP_SETDEF(name) global_logger.set_name(name)
#define UCPP_DEBUG(msg) global_logger.debug(msg)
#else
#define UCPP_LEVEL(level)                                                      \
  setenv(UCPP_LOGGER_ENV,                                                      \
         std::to_string(static_cast<unsigned int>(level)).c_str(), 1)
#define UCPP_DEBUG(msg, ...)
#define UCPP_SETDEF(name)
#endif
#endif