#ifndef __COMMONC_MACRO_HH__
#define __COMMONC_MACRO_HH__

#define PRAGMA(desc) _Pragma(#desc)
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define COMPTIME_ERR(msg) PRAGMA(GCC error msg)
#ifdef __cplusplus
#define IS_CPP 1
#else
#define IS_CPP 0
#endif

#endif