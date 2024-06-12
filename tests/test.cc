#include "../include/logger/logger.hh"

int main() {
  ucpp::Logger testLogger("testLogger", ucpp::LogLevel::LL_FATAL);
  testLogger.log("hello world you idiot");
  return 0;
}