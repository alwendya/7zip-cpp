#pragma once

#include <deque>
#include "FileInfo.h"

namespace SevenZip
{
namespace intl
{
class PathScanner
{
public:

	class Callback
	{
	public:

		virtual ~Callback() = default;

		virtual void BeginScan() {}
		virtual void EndScan() {}
		virtual bool ShouldDescend(const FilePathInfo& directory) = 0;
		virtual void EnterDirectory(const tstring& path) {}
		virtual void LeaveDirectory(const tstring& path) {}
		virtual void ExamineFile(const FilePathInfo& file, bool& exit) = 0;
	};

public:

	static void Scan(const tstring& root, const tstring& pathPrefix, Callback& cb);
	static void Scan(const tstring& root, const tstring& pathPrefix, const tstring& searchPattern, Callback& cb);

private:

	static bool ExamineFiles(const tstring& directory, const tstring& searchPattern, const tstring& pathPrefix, Callback& cb);
	static void ExamineDirectories(const tstring& directory, std::deque< tstring >& subDirs, const tstring& pathPrefix, Callback& cb);

	static bool IsAllFilesPattern(const tstring& searchPattern);
	static bool IsSpecialFileName(const tstring& fileName);
	static bool IsDirectory(const WIN32_FIND_DATA& fdata);
	static FilePathInfo ConvertFindInfo(const tstring& directory, const tstring& pathPrefix, const WIN32_FIND_DATA& fdata);
};
}
}
