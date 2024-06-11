#include "../include/logger/logger.hh"

int main() {
  UCPP_LEVEL(ucpp::LogLevel::LL_DEBUG);
  UCPP_DEBUG("Hello, %s!", "world");
  return 0;
}