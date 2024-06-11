#ifndef UCPP_LOGGER
#define UCPP_LOGGER
#define UCPP_LOGGER_ENV "UCPP_LOG_LEVEL"

#include <cstdarg>
#include <iostream>
#include <string>

namespace ucpp {
enum class OuputDevice { OD_STDIO, OD_FSTREAM };
enum class LogLevel { LL_DESABLED, LL_DEBUG };
using LogHandler = void (*)(const std::string &, void *);

static inline void __def_stdio_handler(const std::string &msg, void *) {
  std::cout << msg << std::endl;
}

class Logger {
private:
  OuputDevice m_device = OuputDevice::OD_STDIO;
  LogHandler m_handler = nullptr;
  LogLevel m_level = LogLevel::LL_DESABLED;

public:
  Logger();

  void debug(const std::string &msg, ...);
};
} // namespace ucpp

#ifndef UCPP_DISABLE_MACROS
extern ucpp::Logger global_logger;
#define UCPP_LOG_DEBUG(msg, ...) global_logger.debug(msg, ##__VA_ARGS__)
#else
#define UCPP_LOG_DEBUG(msg, ...)
#endif
#endif