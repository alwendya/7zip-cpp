#pragma once

#include <vector>
#include "FileInfo.h"

namespace SevenZip
{
namespace intl
{
class FileSys
{
public:

	static tstring GetPath(const tstring& filePath);
	static tstring GetFileName(const tstring& filePathOrName);
	static tstring AppendPath(const tstring& left, const tstring& right);
	static tstring ExtractRelativePath(const tstring& basePath, const tstring& fullPath);

	static bool DirectoryExists(const tstring& path);
	static bool IsDirectoryEmptyRecursive(const tstring& path);

	static bool CreateDirectoryTree(const tstring& path);

	static std::vector< FilePathInfo > GetFile(const tstring& filePathOrName, bool absolutePath = false);
	static std::vector< FilePathInfo > GetFilesInDirectory(const tstring& directory, const tstring& searchPattern, const tstring& pathPrefix, bool recursive);

	static CComPtr< IStream > OpenFileToRead(const tstring& filePath);
	static CComPtr< IStream > OpenFileToWrite(const tstring& filePath);
};
}
}
