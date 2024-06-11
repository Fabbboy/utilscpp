#include "../../include/logger/logger.hh"
#include <cstdarg>
#include <cstdlib>
#include <string>

namespace ucpp {
Logger::Logger(std::string logger) {
  m_level = get_log_level();
  m_handler = __def_stdio_handler;
  m_device = OuputDevice::OD_STDIO;
  m_logger = logger;
}

Logger::Logger(OuputDevice device, LogHandler handler) {
  m_level = get_log_level();
  m_device = device;
  switch (device) {
  case OuputDevice::OD_STDIO:
    m_handler = __def_stdio_handler;
    break;
  case OuputDevice::OD_FSTREAM:
    m_handler = __def_fstream_handler;
    break;
  case OuputDevice::OD_CUSTOM:
    m_handler = handler;
    break;
  default:
    m_handler = __def_stdio_handler;
    break;
  }
};

void Logger::debug(const std::string &msg) {
  if (m_level != LogLevel::LL_DEBUG) {
    return;
  }

  std::string log =
      "[" + get_timestamp() + "][DEBUG][" + m_logger + "] - " + msg;

  m_handler(log);
  return;
}
} // namespace ucpp

#ifndef UCPP_DISABLE_MACROS
ucpp::Logger global_logger("DefaultLogger");
#endif