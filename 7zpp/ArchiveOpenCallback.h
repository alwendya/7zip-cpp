// This file is based on the following file from the LZMA SDK (http://www.7-zip.org/sdk.html):
//   ./CPP/7zip/UI/Client7z/Client7z.cpp
#pragma once

#include <7zip/Archive/IArchive.h>
#include <7zip/IPassword.h>
#include "SevenString.h"

namespace SevenZip
{
namespace intl
{
class ArchiveOpenCallback : public IArchiveOpenCallback, public ICryptoGetTextPassword
{
private:

	long m_refCount = 0;
	tstring m_password;

public:

	ArchiveOpenCallback(const tstring& password);
	virtual ~ArchiveOpenCallback() = default;

	STDMETHOD(QueryInterface)(REFIID iid, void** ppvObject);
	STDMETHOD_(ULONG, AddRef)();
	STDMETHOD_(ULONG, Release)();

	// IArchiveOpenCallback
	STDMETHOD(SetTotal)(const UInt64* files, const UInt64* bytes) { return S_OK; };
	STDMETHOD(SetCompleted)(const UInt64* files, const UInt64* bytes) { return S_OK; };

	// ICryptoGetTextPassword
	STDMETHOD(CryptoGetTextPassword)(BSTR* password);
};
}
}
