#ifndef __UTILSCPP_DEBUG_HH__
#define __UTILSCPP_DEBUG_HH__

#include "macro.hh"

#ifdef DEBUG_MODE
#define DEBUG(format, ...) fprintf(stderr, format, ##__VA_ARGS__)
#else
#if defined(__GNUC__) || defined(__clang__)
#define DEBUG(format, ...)                            \
  PRAGMA(GCC warning "Found DEBUG macro in " __FILE__ \
                     " at line " TOSTRING(__LINE__))
#elif defined(_MSC_VER)
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#pragma warning(push)
#define DEBUG(format, ...)                          \
  __pragma(message("Found DEBUG macro in " __FILE__ \
                   " at line " TOSTRING(__LINE__)))
#pragma warning(pop)
#else
#define DEBUG(format, ...)
#endif
#endif

#endif  // __UTILSCPP_DEBUG_HH__
