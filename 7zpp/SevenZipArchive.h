#pragma once

#include <atlbase.h>
#include <vector>
#include "SevenZipLibrary.h"
#include "FileInfo.h"
#include "CompressionFormat.h"
#include "CompressionLevel.h"

namespace SevenZip
{
class SevenZipArchive
{
public:
	SevenZipArchive() = default;
	SevenZipArchive(SevenZipLibrary* library, const tstring& archivePath);
	virtual ~SevenZipArchive() = default;

	virtual bool ReadInArchiveMetadata();

	virtual void SetCompressionFormat(const CompressionFormatEnum& format);
	virtual CompressionFormatEnum GetCompressionFormat();

	virtual void SetCompressionLevel(const CompressionLevelEnum& level) { m_compressionLevel = level; }
	virtual CompressionLevelEnum GetCompressionLevel() const { return m_compressionLevel; }

	virtual bool DetectCompressionFormat();

	virtual size_t GetNumberOfItems();
	virtual const std::vector<std::wstring>& GetItemsNames();
	virtual const std::vector<size_t>& GetOrigSizes();
	virtual void SetPassword(const tstring& password) { m_password = password; }

	void SetLibrary(SevenZipLibrary* library) { m_library = library; }
	void SetArchivePath(const tstring& archivePath) { m_archivePath = archivePath; }

protected:
	bool m_ReadMetadata = false;
	bool m_OverrideCompressionFormat = false;
	SevenZipLibrary* m_library = nullptr;
	tstring m_archivePath;
	CompressionFormatEnum m_compressionFormat = CompressionFormat::SevenZip;
	CompressionLevelEnum m_compressionLevel = CompressionLevel::Normal;
	size_t m_numberofitems = 0;
	std::vector<std::wstring> m_itemnames;
	std::vector<size_t> m_origsizes;
	tstring m_password;

private:
	bool pri_GetNumberOfItems();
	bool pri_GetItemsNames();
	bool pri_DetectCompressionFormat(CompressionFormatEnum& format);
	bool pri_DetectCompressionFormat();
};
}
