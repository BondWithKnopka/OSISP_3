#pragma once
#include <string>
#include <vector>
#include <MemoryLib.h>
#include <string_view>

using namespace std;

const int* FindInt(int number, const vector<MemoryInfo>& readMemoryRegions)
{
	for (const auto& memoryInfo : readMemoryRegions)
	{
		int* beginAddress = (int*)memoryInfo.BaseAddress;
		for (size_t i = 0; i < memoryInfo.RegionSize / sizeof(int); ++i)
		{
			if (number == *(beginAddress + i))
			{
				return beginAddress + i;
			}
		}
	}
	return nullptr;
}

vector<const char*> findstring(const string& s, const vector<MemoryInfo>& readmemoryregions)
{
	vector<const char*> result;
	size_t length = s.length();
	const char* cstring = s.c_str();
	for (const auto& memoryinfo : readmemoryregions)
	{
		char* memoryregionbeginaddress = (char*)memoryinfo.BaseAddress;
		for (size_t i = 0; i < memoryinfo.RegionSize / sizeof(char) - length; ++i)
		{
			const char* stringbeginaddress = memoryregionbeginaddress + i;
			if (strncmp(cstring, stringbeginaddress, length) == 0)
			{
				result.push_back(stringbeginaddress);
			}
		}
	}
	return result;
}


template <typename CharType>
vector<basic_string_view<CharType, char_traits<CharType>>> FindS(const basic_string < CharType, char_traits<CharType>, allocator<CharType>>& string, const vector<MemoryInfo>& readMemoryRegions)
{
	vector<basic_string_view<CharType, char_traits<CharType>>> result;
	size_t length = string.length();
	for (const auto& memoryInfo : readMemoryRegions)
	{
		CharType* memoryRegionBeginAddress = (CharType*)memoryInfo.BaseAddress;
		for (size_t i = 0; i + length < memoryInfo.RegionSize / sizeof(CharType); ++i)
		{
			const CharType* stringBeginAddress = memoryRegionBeginAddress + i;
			basic_string_view<CharType, char_traits<CharType>> comparedString(stringBeginAddress);
			if (string.compare(comparedString) == 0)
			{
				result.push_back(comparedString);
			}
		}
	}
	return result;
}