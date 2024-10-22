#ifndef __UTILSCPP_DEBUG_HH__
#define __UTILSCPP_DEBUG_HH__

#define PRAGMA(desc) _Pragma(#desc)

#ifdef DEBUG_MODE
#define DEBUG(format, ...) fprintf(stderr, format, ##__VA_ARGS__)
#else
#if defined(__GNUC__) || defined(__clang__)
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define DEBUG(format, ...)                            \
  PRAGMA(GCC warning "Found DEBUG macro in " __FILE__ \
                     " at line " TOSTRING(__LINE__))
#else
#define DEBUG(format, ...)
#endif
#endif

#endif  // __UTILSCPP_DEBUG_HH__
