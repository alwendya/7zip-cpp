#pragma once
#include "SevenString.h"

namespace SevenZip
{
namespace intl
{
struct FileInfo
{
	tstring		FileName;
	FILETIME	LastWriteTime = { 0 };
	FILETIME	CreationTime = { 0 };
	FILETIME	LastAccessTime = { 0 };
	ULONGLONG	Size = 0ULL;
	ULONGLONG	PackedSize = 0ULL;
	UINT		Attributes = 0;
	bool		IsDirectory = false;
	bool		memFile = false;
	void*		memPointer = nullptr;
};

struct FilePathInfo : public FileInfo
{
	tstring		rootPath;
	tstring		FilePath;
};
}
}
