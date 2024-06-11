#include "../../include/logger/logger.hh"
#include <cstdarg>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

namespace ucpp {
Logger::Logger() {
  const char *env = std::getenv(UCPP_LOGGER_ENV);
  if (env) {
    std::string env_str(env);
    switch (env_str[0]) {
    case '0':
      m_level = LogLevel::LL_DESABLED;
      break;
    case '1':
      m_level = LogLevel::LL_DEBUG;
      break;
    default:
      std::cerr << "Invalid log level: " << env_str << std::endl;
      break;
    }
  }

  m_handler = __def_stdio_handler;
  m_device = OuputDevice::OD_STDIO;
}

void Logger::debug(const std::string &msg, ...) {
  if (m_level != LogLevel::LL_DEBUG) {
    return;
  }

  std::string final_msg = "[DEBUG] " + msg;
  va_list args;
  va_start(args, msg);
  int size = vsnprintf(nullptr, 0, final_msg.c_str(), args);
  std::vector<char> buffer(size + 1);

  va_start(args, msg);
  vsnprintf(buffer.data(), buffer.size(), final_msg.c_str(), args);
  va_end(args);

  if (m_handler) {
    m_handler(std::string(buffer.data()), args);
  } else {
    std::cerr << "Log handler not set." << std::endl;
  }
}
} // namespace ucpp

#ifndef UCPP_DISABLE_MACROS
ucpp::Logger global_logger;
#endif