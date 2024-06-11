#ifndef UCPP_LOGGER
#define UCPP_LOGGER
#define UCPP_LOGGER_ENV "UCPP_LOG_LEVEL"
#ifndef UCPP_DISABLE_MACROS
#endif

namespace ucpp {
enum class OuputDevice { OD_STDIO, OD_FSTREAM };
using 

class Logger {
private:
  bool active;
  OuputDevice device;
};

#ifndef UCPP_DISABLE_MACROS
extern Logger global_logger;
#endif
} // namespace ucpp

#endif