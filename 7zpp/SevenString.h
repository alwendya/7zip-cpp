#pragma once

#include <string>
#include <OleAuto.h>

namespace SevenZip
{
#ifdef _UNICODE
using tstring = std::wstring;
#else
using tstring = std::string;
#endif
}
namespace SevenZip
{
BSTR TStringAllocSysString(const tstring& string);
tstring BstrToTString(BSTR string);
}
