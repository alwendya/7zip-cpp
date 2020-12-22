// This file is based on the following file from the LZMA SDK (http://www.7-zip.org/sdk.html):
//   ./CPP/7zip/UI/Client7z/Client7z.cpp
#pragma once

#include <vector>
#include <7zip/Archive/IArchive.h>
#include <7zip/IPassword.h>
#include <7zip/UI/Common/UpdateCallback.h>

#include "ProgressCallback.h"

namespace SevenZip
{
namespace intl
{
class MemExtractCallback : public IArchiveExtractCallback, public ICryptoGetTextPassword
{
private:

	long m_refCount = 0;

	CComPtr< IInArchive > m_archiveHandler;
	CComPtr< ISequentialOutStream > m_outMemStream;
	std::vector<BYTE>& m_buffer;

	tstring m_archivePath;
	tstring m_password;

	bool m_isDir = false;
	bool m_hasNewFileSize = false;
	UInt64 m_newFileSize = { 0 };
	tstring m_filePath;

	IProgressCallback* m_callback = nullptr;

public:

	MemExtractCallback(const CComPtr< IInArchive >& archiveHandler,
					   std::vector<BYTE>& buffer,
					   const tstring& archivePath,
					   const tstring& password,
					   IProgressCallback* callback);
	virtual ~MemExtractCallback() = default;

	STDMETHOD(QueryInterface)(REFIID iid, void** ppvObject);
	STDMETHOD_(ULONG, AddRef)();
	STDMETHOD_(ULONG, Release)();

	// IProgress
	STDMETHOD(SetTotal)(UInt64 size);
	STDMETHOD(SetCompleted)(const UInt64* completeValue);

	// Early exit, this is not part of any interface
	STDMETHOD(CheckBreak)();

	// IMemExtractCallback
	STDMETHOD(GetStream)(UInt32 index, ISequentialOutStream** outStream, Int32 askExtractMode);
	STDMETHOD(PrepareOperation)(Int32 askExtractMode) { return S_OK; };
	STDMETHOD(SetOperationResult)(Int32 resultEOperationResult);

	// ICryptoGetTextPassword
	STDMETHOD(CryptoGetTextPassword)(BSTR* password);

private:

	void GetPropertyFilePath(UInt32 index);
	void GetPropertyIsDir(UInt32 index);
	void GetPropertySize(UInt32 index);

	void EmitDoneCallback();
	void EmitFileDoneCallback(const tstring& path);
};
}
}
