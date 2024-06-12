#ifndef UCPP_LOGGER
#define UCPP_LOGGER
#define UCPP_LOGGER_ENV "UCPP_LOG_LEVEL"

#include <chrono>
#include <cstdarg>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

namespace ucpp {
enum class OuputDevice { OD_STDIO, OD_FSTREAM, OD_CUSTOM };
enum class LogLevel {
  LL_DISABLED,
  LL_DEBUG,
  LL_WARNING,
  LL_ERROR,
  LL_FATAL,
  LL_COUNT
};
std::ostream &operator<<(std::ostream &os, const LogLevel &lg);
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

  static inline std::string get_timestamp() {
    std::string format = "%Y-%m-%dT%H:%M:%S";
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now_c), format.c_str());
    return ss.str();
  }

public:
  Logger(std::string logger = "DefaultLogger");
  Logger(std::string logger, LogLevel level,
         OuputDevice device = OuputDevice::OD_STDIO,
         LogHandler handler = __def_stdio_handler);

  void set_log_level(LogLevel level) { m_level = level; }
  void set_name(const std::string &name) { m_logger = name; }

  void log(const std::string &msg);
  void log(const char *msg);
};
} // namespace ucpp

#endif