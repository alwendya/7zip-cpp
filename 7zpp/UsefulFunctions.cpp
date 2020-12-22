#include "stdafx.h"
#include <array>
#include "UsefulFunctions.h"
#include "PropVariant.h"
#include "GUIDs.h"
#include "FileSys.h"
#include "ArchiveOpenCallback.h"
#include "InStreamWrapper.h"


namespace SevenZip
{
using namespace intl;

const GUID* UsefulFunctions::GetCompressionGUID(const CompressionFormatEnum& format)
{
	const GUID* guid = nullptr;

	switch (format)
	{
		case CompressionFormat::Zip:
			guid = &SevenZip::intl::CLSID_CFormatZip;
			break;

		case CompressionFormat::GZip:
			guid = &SevenZip::intl::CLSID_CFormatGZip;
			break;

		case CompressionFormat::BZip2:
			guid = &SevenZip::intl::CLSID_CFormatBZip2;
			break;

		case CompressionFormat::Rar:
			guid = &SevenZip::intl::CLSID_CFormatRar;
			break;

		case CompressionFormat::Tar:
			guid = &SevenZip::intl::CLSID_CFormatTar;
			break;

		case CompressionFormat::Iso:
			guid = &SevenZip::intl::CLSID_CFormatIso;
			break;

		case CompressionFormat::Cab:
			guid = &SevenZip::intl::CLSID_CFormatCab;
			break;

		case CompressionFormat::Lzma:
			guid = &SevenZip::intl::CLSID_CFormatLzma;
			break;

		case CompressionFormat::Lzma86:
			guid = &SevenZip::intl::CLSID_CFormatLzma86;
			break;

		default:
			guid = &SevenZip::intl::CLSID_CFormat7z;
			break;
	}
	return guid;
}

CComPtr< IInArchive > UsefulFunctions::GetArchiveReader(const SevenZipLibrary& library, const CompressionFormatEnum& format)
{
	const GUID* guid = GetCompressionGUID(format);

	CComPtr< IInArchive > archive;
	library.CreateObject(*guid, IID_IInArchive, reinterpret_cast<void**>(&archive));
	return archive;
}

CComPtr< IOutArchive > UsefulFunctions::GetArchiveWriter(const SevenZipLibrary& library, const CompressionFormatEnum& format)
{
	const GUID* guid = GetCompressionGUID(format);

	CComPtr< IOutArchive > archive;
	library.CreateObject(*guid, IID_IOutArchive, reinterpret_cast<void**>(&archive));
	return archive;
}

bool UsefulFunctions::GetNumberOfItems(const SevenZipLibrary& library, const tstring& archivePath,
									   const CompressionFormatEnum& format, const tstring& password, size_t& numberofitems)
{
	CComPtr< IStream > fileStream = FileSys::OpenFileToRead(archivePath);

	if (fileStream == nullptr)
	{
		return false;
	}

	CComPtr< IInArchive > archive = UsefulFunctions::GetArchiveReader(library, format);
	if (!archive)
	{
		return false;
	}

	CComPtr< InStreamWrapper > inFile = new InStreamWrapper(fileStream);
	CComPtr< ArchiveOpenCallback > openCallback = new ArchiveOpenCallback(password);

	HRESULT hr = archive->Open(inFile, nullptr, openCallback);
	if (hr != S_OK)
	{
		return false;
	}

	UInt32 mynumofitems;
	hr = archive->GetNumberOfItems(&mynumofitems);
	if (hr != S_OK)
	{
		return false;
	}
	numberofitems = size_t(mynumofitems);

	archive->Close();
	return true;
}

bool UsefulFunctions::GetItemsNames(const SevenZipLibrary& library, const tstring& archivePath,
									const CompressionFormatEnum& format, const tstring& password,
									size_t& numberofitems, std::vector<std::wstring>& itemnames, std::vector<size_t>& origsizes)
{
	CComPtr< IStream > fileStream = FileSys::OpenFileToRead(archivePath);

	if (fileStream == nullptr)
	{
		return false;
	}

	CComPtr< IInArchive > archive = UsefulFunctions::GetArchiveReader(library, format);
	if (!archive)
	{
		return false;
	}

	CComPtr< InStreamWrapper > inFile = new InStreamWrapper(fileStream);
	CComPtr< ArchiveOpenCallback > openCallback = new ArchiveOpenCallback(password);

	HRESULT hr = archive->Open(inFile, nullptr, openCallback);
	if (hr != S_OK)
	{
		return false;
	}

	UInt32 mynumofitems;
	hr = archive->GetNumberOfItems(&mynumofitems);
	if (hr != S_OK)
	{
		return false;
	}
	numberofitems = size_t(mynumofitems);

	itemnames.clear();
	itemnames.resize(numberofitems);

	origsizes.clear();
	origsizes.resize(numberofitems);

	for (UInt32 i = 0; i < numberofitems; i++)
	{
		// Get uncompressed size of file
		CPropVariant prop;
		hr = archive->GetProperty(i, kpidSize, &prop);
		if (hr != S_OK)
		{
			return false;
		}

		int size = prop.intVal;
		origsizes[i] = size_t(size);

		// Get name of file
		hr = archive->GetProperty(i, kpidPath, &prop);
		if (hr != S_OK)
		{
			return false;
		}

		//valid string? pass back the found value and call the callback function if set
		if (prop.vt == VT_BSTR)
		{
			itemnames[i] = prop.bstrVal;
		}
	}

	archive->Close();
	return true;
}

bool UsefulFunctions::DetectCompressionFormat(const SevenZipLibrary& library, const tstring& archivePath,
											  CompressionFormatEnum& archiveCompressionFormat, const tstring& password)
{
	CComPtr< IStream > fileStream = FileSys::OpenFileToRead(archivePath);

	if (fileStream == nullptr)
	{
		return false;
	}

	std::array<CompressionFormatEnum, 12> myAvailableFormats;

	// Add more formats here if 7zip supports more formats in the future
	myAvailableFormats[0] = CompressionFormat::Zip;
	myAvailableFormats[1] = CompressionFormat::SevenZip;
	myAvailableFormats[2] = CompressionFormat::Rar;
	myAvailableFormats[3] = CompressionFormat::GZip;
	myAvailableFormats[4] = CompressionFormat::BZip2;
	myAvailableFormats[5] = CompressionFormat::Tar;
	myAvailableFormats[6] = CompressionFormat::Lzma;
	myAvailableFormats[7] = CompressionFormat::Lzma86;
	myAvailableFormats[8] = CompressionFormat::Cab;
	myAvailableFormats[9] = CompressionFormat::Iso;
	myAvailableFormats[10] = CompressionFormat::Arj;
	myAvailableFormats[11] = CompressionFormat::XZ;

	// Check each format for one that works
	for (const auto& myAvailableFormat : myAvailableFormats)
	{
		archiveCompressionFormat = myAvailableFormat;

		CComPtr< IInArchive > archive = UsefulFunctions::GetArchiveReader(library, archiveCompressionFormat);
		if (!archive) continue;

		CComPtr< InStreamWrapper > inFile = new InStreamWrapper(fileStream);
		CComPtr< ArchiveOpenCallback > openCallback = new ArchiveOpenCallback(password);

		HRESULT hr = archive->Open(inFile, nullptr, openCallback);
		if (hr == S_OK)
		{
			// We know the format if we get here, so return
			archive->Close();
			return true;
		}

		archive->Close();
	}

	//
	//  There is a problem that GZip files will not be detected using the above method.
	//  This is a fix.
	//
	size_t myNumOfItems = 0;
	archiveCompressionFormat = CompressionFormat::GZip;
	bool result = GetNumberOfItems(library, archivePath, archiveCompressionFormat, password, myNumOfItems);
	if (result && myNumOfItems > 0)
	{
		// We know this file is a GZip file, so return
		return true;
	}

	// If you get here, the format is unknown
	archiveCompressionFormat = CompressionFormat::Unknown;
	return false;
}

const tstring UsefulFunctions::EndingFromCompressionFormat(const CompressionFormatEnum& format)
{
	switch (format)
	{
		case CompressionFormat::Zip:
			return _T(".zip");
		case CompressionFormat::SevenZip:
			return _T(".7z");
		case CompressionFormat::Rar:
			return _T(".rar");
		case CompressionFormat::GZip:
			return _T(".gz");
		case CompressionFormat::BZip2:
			return _T(".bz");
		case CompressionFormat::Tar:
			return _T(".tar");
		case CompressionFormat::Lzma:
			return _T(".lzma");
		case CompressionFormat::Lzma86:
			return _T(".lzma86");
		case CompressionFormat::Cab:
			return _T(".cab");
		case CompressionFormat::Iso:
			return _T(".iso");
		case CompressionFormat::Arj:
			return _T(".arj");
		case CompressionFormat::XZ:
			return _T(".xz");
	}
	return _T(".zip");
}

}

