#include "../../include/logger/logger.hh"
#include <cstdarg>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

namespace ucpp {
Logger::Logger() {
  m_level = get_log_level();
  m_handler = __def_stdio_handler;
  m_device = OuputDevice::OD_STDIO;
}

Logger::Logger(OuputDevice device, LogHandler handler) {
  m_level = get_log_level();
  m_device = device;
  m_handler = handler;
};

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