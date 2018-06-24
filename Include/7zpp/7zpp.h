#pragma once


#include "SevenZipCompressor.h"
#include "SevenZipExtractor.h"
#include "SevenZipLister.h"

// Version of this library
#define SEVENZIP_VERSION "0.3.0-20180422"

#define SEVENZIP_LIBNAME "7zpp"

#ifdef _DEBUG
	#define LIBDBG "d"
#else
#define LIBDBG

#endif
#ifdef _UNICODE
	#define CHARSET "u"
#else
	#define CHARSET "a"
#endif
#ifdef _WIN64
	#define BITNESS "64"
#else
	#define BITNESS "32"
#endif

#pragma comment ( lib, SEVENZIP_LIBNAME BITNESS CHARSET LIBDBG  ".lib" )

#undef LIBDBG
#undef CHARSET
#undef BITNESS
