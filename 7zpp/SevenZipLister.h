#pragma once

#include "SevenZipLibrary.h"
#include "SevenZipArchive.h"
#include "CompressionFormat.h"
#include "ListCallback.h"


namespace SevenZip
{
class SevenZipLister : public SevenZipArchive
{
public:
	tstring m_archivePath;

	SevenZipLister() = default;
	SevenZipLister(SevenZipLibrary* library, const tstring& archivePath);
	virtual ~SevenZipLister() = default;

	virtual bool ListArchive(const tstring& password, ListCallback* callback = nullptr);


private:
	bool ListArchive(const CComPtr< IStream >& archiveStream, const tstring& password, ListCallback* callback);
};
}
