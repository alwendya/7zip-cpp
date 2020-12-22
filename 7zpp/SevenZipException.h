#pragma once


#include <exception>
#include <tchar.h>
#include "SevenString.h"


namespace SevenZip
{
tstring StrFmt(const TCHAR* format, ...);
tstring GetWinErrMsg(const tstring& contextMessage, DWORD lastError);
tstring GetCOMErrMsg(const tstring& contextMessage, HRESULT lastError);

class SevenZipException
{
protected:

	tstring m_message;

public:

	SevenZipException() = default;
	SevenZipException(const tstring& message);
	virtual ~SevenZipException() = default;

	const tstring& GetMessage() const { return m_message; }
};
}
