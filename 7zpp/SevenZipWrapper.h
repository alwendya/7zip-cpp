#pragma once

#include "7zpp.h"

namespace SevenZip
{
class SevenZipWrapper
{
public:
	SevenZipWrapper();
	SevenZipWrapper(const tstring& libPath);
	~SevenZipWrapper() = default;

	bool CreateArchive(const tstring& archivePath, const tstring& password = tstring());
	bool OpenArchive(const tstring& archivePath, const tstring& password = tstring());

	bool SetLibPath(const tstring& libPath) { return (m_libLoaded = m_lib.Load(libPath)); }

	SevenZip::SevenZipCompressor& GetCompressor() { return m_compressor; }
	SevenZip::SevenZipExtractor& GetExtractor() { return m_extractor; }

private:
	bool m_libLoaded = false;

	SevenZipLibrary m_lib;
	SevenZipCompressor m_compressor;
	SevenZipExtractor m_extractor;
};
}