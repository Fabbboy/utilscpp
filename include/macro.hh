#ifndef __UTILSCPP_MACRO_HH__
#define __UTILSCPP_MACRO_HH__

#define PRAGMA(desc) _Pragma(#desc)
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define COMPTIME_ERR(msg) PRAGMA(GCC error msg)

#endif