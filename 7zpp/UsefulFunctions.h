#pragma once
#include <vector>
#include <7zip/Archive/IArchive.h>
#include <7zTypes.h>
#include "SevenZipLibrary.h"
#include "CompressionFormat.h"

namespace SevenZip
{
using namespace intl;

class UsefulFunctions
{
public:
	static const GUID* GetCompressionGUID(const CompressionFormatEnum& format);

	static CComPtr< IInArchive > GetArchiveReader(const SevenZipLibrary& library, const CompressionFormatEnum& format);
	static CComPtr< IOutArchive > GetArchiveWriter(const SevenZipLibrary& library, const CompressionFormatEnum& format);

	static bool DetectCompressionFormat(const SevenZipLibrary& library, const tstring& archivePath,
										CompressionFormatEnum& archiveCompressionFormat, const tstring& password);

	static bool UsefulFunctions::GetNumberOfItems(const SevenZipLibrary& library, const tstring& archivePath,
												  const CompressionFormatEnum& format, const tstring& password, size_t& numberofitems);

	static bool UsefulFunctions::GetItemsNames(const SevenZipLibrary& library, const tstring& archivePath, const CompressionFormatEnum& format, const tstring& password,
											   size_t& numberofitems, std::vector<std::wstring>& itemnames, std::vector<size_t>& origsizes);

	static const tstring EndingFromCompressionFormat(const CompressionFormatEnum& format);
};
}
