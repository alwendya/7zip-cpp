#include "stdafx.h"
#include "SevenZipException.h"


namespace SevenZip
{

tstring StrFmt(const TCHAR* format, ...)
{
	tstring result;
	TCHAR* buffer;
	int		sz;
	va_list	args;

	va_start(args, format);

	sz = _vsctprintf(format, args) + 1;
	buffer = new TCHAR[sz];
	_vsntprintf_s(buffer, sz, _TRUNCATE, format, args);
	result = buffer;
	delete[] buffer;

	va_end(args);

	return result;
}

tstring GetWinErrMsg(const tstring& contextMessage, DWORD lastError)
{
	// TODO: use FormatMessage to get the appropriate message from the
	return StrFmt(_T("%s: GetLastError = %lu"), contextMessage.c_str(), lastError);
}

tstring GetCOMErrMsg(const tstring& contextMessage, HRESULT lastError)
{
	// TODO: use FormatMessage to get the appropriate message from the
	return StrFmt(_T("%s: HRESULT = 0x%08X"), contextMessage.c_str(), lastError);
}

SevenZipException::SevenZipException(const tstring& message)
	: m_message(message)
{
}

}
