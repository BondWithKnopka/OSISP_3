#define __STRINGMODIFYINGDLL_H
#include <Windows.h>
#include <vector>
#include "StringModifyingDll.h"
#include <iostream>
#include "../MemoryLib/MemoryLib.h"

const size_t MaxStringSize = 4096;

std::vector<const char*> FindString(const char* s, const std::vector<MemoryInfo>& readMemoryRegions);

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	UNREFERENCED_PARAMETER(hModule);
	UNREFERENCED_PARAMETER(lpReserved);
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		ReplaceString("Hello!", "ByeBye");
	default:
		break;
	}
	return TRUE;
}

bool ReplaceString(const char* oldValue, const char* newValue)
{
	size_t oldLength = strnlen_s(oldValue, MaxStringSize);
	size_t newLength = strnlen_s(newValue, MaxStringSize);
	if (newLength > oldLength)
	{
		return false;
	}
	std::vector<MemoryInfo> memoryRegions = GetMemoryRegionsInfo();
	std::vector<MemoryInfo> readWriteMemoryRegions = GetReadWriteMemoryRegions(memoryRegions);
	auto strings = FindString(oldValue, readWriteMemoryRegions);

	for (auto string : strings)
	{
		for (size_t i = 0; i < newLength; ++i)
		{
			(const_cast<char*>(string))[i] = newValue[i];
		}
		for (size_t i = newLength; i < oldLength; ++i)
		{
			(const_cast<char*>(string))[i] = '\0';
		}
	}
	return true;
}


std::vector<const char*> FindString(const char* s, const std::vector<MemoryInfo>& readMemoryRegions)
{
	std::vector<const char*> result;
	size_t length = strnlen_s(s, MaxStringSize);
	const char* cString = s;

	for (const auto& memoryInfo : readMemoryRegions)
	{
		auto memoryRegionBeginAddress = static_cast<char*>(const_cast<LPVOID>(memoryInfo.BaseAddress));
		for (size_t i = 0; i < memoryInfo.RegionSize / sizeof(CHAR) - length; ++i)
		{
			const CHAR* stringBeginAddress = memoryRegionBeginAddress + i;
			size_t currentStringLength = strnlen_s(stringBeginAddress, MaxStringSize);
			if (currentStringLength == length && strncmp(cString, stringBeginAddress, length) == 0)
			{
				result.push_back(stringBeginAddress);
			}
		}
	}
	return result;
}
