#ifndef __UTILSCPP_MACRO_HH__
#define __UTILSCPP_MACRO_HH__

#define PRAGMA(desc) _Pragma(#desc)
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define COMPTIME_ERR(msg) PRAGMA(GCC error msg)
#define UNREACHABLE()                                                          \
  THROW("Reached unreachable code in %s:%d", __FILE__, __LINE__)
#define NOT_IMPLEMENTED(msg)                                                   \
  THROW("Not implemented: %s:%d: %s", __FILE__, __LINE__, msg)

#ifdef __cplusplus
#include <cstdio>
#include <cstdlib>
#define THROW(msg, ...)                                                        \
  do {                                                                         \
    int size = std::snprintf(nullptr, 0, msg, __VA_ARGS__) + 1;                \
    std::unique_ptr<char[]> buffer(new char[size]);                            \
    std::snprintf(buffer.get(), size, msg, __VA_ARGS__);                       \
    throw std::runtime_error(buffer.get());                                    \
  } while (0)
#else
#include <stdio.h>
#include <stdlib.h>
#define THROW(msg, ...)                                                        \
  do {                                                                         \
    fprintf(stderr, msg, __VA_ARGS__);                                         \
    fprintf(stderr, "\n");                                                     \
    abort();                                                                   \
  } while (0)
#endif

#endif