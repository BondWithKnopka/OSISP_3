#pragma once

#include <ostream>
#include <vector>

enum MemoryState
{
	Free = 0x10000, Commit = 0x1000, Reserve = 0x2000
};

enum MemoryType
{
	Image = 0x1000000, Mapped = 0x40000, Private = 0x20000
};

enum MemoryProtection
{
	Execute = 0x10,
	ExecuteRead = 0x20,
	ExecuteReadWrite = 0x40,
	ExecuteWriteCopy = 0x80,
	NoAccess = 0x01,
	Read = 0x02,
	ReadWrite = 0x04,
	WriteCopy = 0x08,
	TargetsInvalid = 0x40000000,
	TargetsNoUpdate = 0x40000000,

	Guard = 0x100,
	NoCache = 0x200,
	WriteCombine = 0x400
};

struct MemoryInfo
{
	LPCVOID BaseAddress;
	SIZE_T RegionSize;
	MemoryState State;
	MemoryType Type;
	MemoryProtection Protect;
	MemoryInfo(LPCVOID baseAddress, SIZE_T regionSize, MemoryState state, MemoryType type, MemoryProtection protect)
		: BaseAddress(baseAddress), RegionSize(regionSize), State(state),
		Type(type), Protect(protect) {}
};

inline std::ostream& operator<<(std::ostream& output, const MemoryInfo& memoryInfo)
{
	output << memoryInfo.BaseAddress << " "
		<< memoryInfo.RegionSize / 1024 << " KB "
		<< memoryInfo.State << " "
		<< memoryInfo.Type << " "
		<< memoryInfo.Protect;
	return output;
}

extern bool CanRead(MemoryProtection protection);
extern bool CanWrite(MemoryProtection protection);
extern bool IsGuard(MemoryProtection protection);
extern std::vector<MemoryInfo> GetMemoryRegionsInfo();
extern std::vector<MemoryInfo> GetReadWriteMemoryRegions(const std::vector<MemoryInfo>& memoryRegionsInfo);
extern std::vector<MemoryInfo> GetReadOnlyMemoryRegions(const std::vector<MemoryInfo>& memoryRegionsInfo);