#include "stdafx.h"

#include "SevenZipWrapper.h"
#include "FileSys.h"

namespace SevenZip
{
	SevenZipWrapper::SevenZipWrapper(const TString& libPath)
		: m_libPath(libPath)
		, m_libLoaded(false)
	{
		m_libLoaded = m_lib.Load(libPath);
	}

	bool SevenZipWrapper::OpenArchive(const TString& archivePath, const TString* password /*= nullptr*/)
	{
		m_archive = archivePath;
		if(password)
		{
			m_password = *password;
		}

		if (!m_libLoaded)
		{
			return false;
		}

		m_extractor.SetLibrary(&m_lib);
		m_extractor.SetArchivePath(m_archive);
		m_extractor.SetPassword(m_password);

		m_extractor.ReadInArchiveMetadata();
		m_compFormat = m_extractor.GetCompressionFormat();

		return true;
	}

	bool SevenZipWrapper::CreateArchive()
	{
		if (!m_libLoaded)
		{
			return false;
		}

		return m_compressor.DoCompress();
	}

	bool SevenZipWrapper::ExtractFile(const TString& filename, const TString& path, bool bUseFullPath /*= false*/)
	{
		std::vector<int> indices;
		if (!FindFilesInArchive(filename, indices, bUseFullPath, true)) return false;

		return m_extractor.ExtractFilesFromArchive((unsigned int*)indices.data(), (unsigned int)indices.size(), path);
	}

	bool SevenZipWrapper::ExtractFileToMemory(const TString& filename, std::vector<BYTE>& memBuffer, bool bUseFullPath /*= false*/)
	{
		std::vector<int> indices;
		if (!FindFilesInArchive(filename, indices, bUseFullPath, true)) return false;

		// only first found file to extract
		return m_extractor.ExtractFileToMemory(indices[0], memBuffer);
	}

	bool SevenZipWrapper::AddFile(const TString& filename)
	{
		return m_compressor.AddFile(filename);
	}

	bool SevenZipWrapper::AddFiles(const TString& directory, const TString& searchFilter, bool includeSubdirs /*= true*/)
	{
		return m_compressor.AddFiles(directory, searchFilter, includeSubdirs);
	}

	bool SevenZipWrapper::AddMemory(const TString& filePath, void* memPointer, size_t size)
	{
		return m_compressor.AddMemory(filePath, memPointer, size);
	}

	bool SevenZipWrapper::FindFilesInArchive(const TString &filename, std::vector<int> &indices, bool bUseFullPath, bool bOnlyFirst)
	{
		const std::vector<std::wstring>& files = m_extractor.GetItemsNames();
#ifdef _UNICODE
		const wchar_t* filenameStr = filename.c_str();
#else
		wchar_t filenameStr[MAX_PATH];
		MultiByteToWideChar(_AtlGetConversionACP(), 0, filename.c_str(), (int)filename.length() + 1, filenameStr, MAX_PATH);
#endif

		int indice = 0;
		for (const auto& file : files)
		{
			int add = _wcsicmp(filenameStr, file.c_str());
			if (add != 0 && !bUseFullPath)
			{
				size_t pos = file.rfind('\\');
				if (pos != std::string::npos)
				{
					++pos;
					add = _wcsicmp(filenameStr, file.c_str() + pos);
				}
			}

			if (add == 0)
			{
				indices.push_back(indice);
				if (bOnlyFirst) break;
			}

			indice++;
		}

		return !indices.empty();
	}
}
