#pragma once

#include "7zpp.h"

namespace SevenZip
{
	class SevenZipWrapper
	{
	public:
		SevenZipWrapper(const TString& libPath);
		~SevenZipWrapper() = default;

		bool CreateArchive();
		bool OpenArchive(const TString& archivePath, const TString* password = nullptr);

		bool ExtractFile(const TString& filename, const TString& path, bool bUseFullPath = false);
		bool ExtractFileToMemory(const TString& filename, std::vector<BYTE>& memBuffer, bool bUseFullPath = false);

		bool AddFile(const TString& filename);
		bool AddFiles(const TString& directory, const TString& searchFilter, bool includeSubdirs = true);
		bool AddMemory(const TString& filePath, void* memPointer, size_t size);

		void SetArchive(const TString& archivePath) { m_archive = archivePath; };

		void SetOutputPath(const TString& outputPath) { m_outputPath = outputPath; };

		void SetCompressionFormat(const CompressionFormatEnum& format) { m_compFormat = format; };
		CompressionFormatEnum GetCompressionFormat() const { return m_compFormat; }

		void SetCompressionLevel(const CompressionLevelEnum& level) { m_compLevel = level; };
		CompressionLevelEnum GetCompressionLevel() const { return m_compLevel; }

		void SetPassword(const TString& password) { m_password = password; };

	private:
		bool FindFilesInArchive(const TString &filename, std::vector<int> &indices, bool bUseFullPath, bool bOnlyFirst);

	protected:
		SevenZipLibrary m_lib;
		SevenZipCompressor m_compressor;
		SevenZipExtractor m_extractor;

		CompressionFormatEnum m_compFormat;
		CompressionLevelEnum m_compLevel;

		bool m_libLoaded;
		TString m_libPath;
		TString m_password;
		TString m_archive;
		TString m_outputPath;
	};
}