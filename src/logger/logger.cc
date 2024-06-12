#include "../../include/logger/logger.hh"
#include <cstdarg>
#include <cstdlib>
#include <sstream>
#include <string>

namespace ucpp {
Logger::Logger(std::string logger) {
  m_level = get_log_level();
  m_handler = __def_stdio_handler;
  m_device = OuputDevice::OD_STDIO;
  m_logger = logger;
}

Logger::Logger(std::string logger, LogLevel level, OuputDevice device,
               LogHandler handler) {
  m_level = level;
  m_device = device;
  m_logger = logger;
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

void Logger::log(const std::string &msg) {
  std::stringstream ss;
  ss << "[" << get_timestamp() << "]";
  ss << "[" << m_level << "]";
  ss << "[" << m_logger << "]";
  ss << " - " << msg;
  if (m_level == LogLevel::LL_FATAL) {
    throw std::runtime_error(ss.str());
  }
  m_handler(ss.str());
  return;
}

void Logger::log(const char *msg) {
  std::stringstream ss;
  ss << "[" << get_timestamp() << "]";
  ss << "[" << m_level << "]";
  ss << "[" << m_logger << "]";
  ss << " - " << msg;
  if (m_level == LogLevel::LL_FATAL) {
    throw std::runtime_error(ss.str());
  }
  m_handler(ss.str());
  return;
}
} // namespace ucpp

std::ostream &ucpp::operator<<(std::ostream &os, const ucpp::LogLevel &lg) {
  switch (lg) {
  case ucpp::LogLevel::LL_DISABLED:
    os << "DISABLED";
    break;
  case ucpp::LogLevel::LL_DEBUG:
    os << "DEBUG";
    break;
  case ucpp::LogLevel::LL_WARNING:
    os << "WARNING";
    break;
  case ucpp::LogLevel::LL_ERROR:
    os << "ERROR";
    break;
  case ucpp::LogLevel::LL_FATAL:
    os << "FATAL";
    break;
  case ucpp::LogLevel::LL_COUNT:
  default:
    os << "NOPT";
    break;
  }
  return os;
}