#include "framework.h"
#include <vector>
#include "MemoryLib.h"

bool CanRead(MemoryProtection protection)
{
	return protection & (ExecuteRead | ExecuteReadWrite | Read | ReadWrite);
}

bool CanWrite(MemoryProtection protection)
{
	return protection & (ExecuteReadWrite | ReadWrite | WriteCopy);
}

bool IsGuard(MemoryProtection protection)
{
	return protection & Guard;
}

std::vector<MemoryInfo> GetReadOnlyMemoryRegions(const std::vector<MemoryInfo>& memoryRegionsInfo)
{
	std::vector<MemoryInfo> result;
	for (const auto& memoryRegionInfo : memoryRegionsInfo)
	{
		if (memoryRegionInfo.State == MemoryState::Commit
			&& !IsGuard(memoryRegionInfo.Protect)
			&& CanRead(memoryRegionInfo.Protect)
			&& !CanWrite(memoryRegionInfo.Protect))
		{
			result.push_back(memoryRegionInfo);
		}
	}
	return result;
}

std::vector<MemoryInfo> GetMemoryRegionsInfo()
{
	std::vector<MemoryInfo> result;
	SYSTEM_INFO systemInfo;
	GetSystemInfo(&systemInfo);
	void* pMemory = systemInfo.lpMinimumApplicationAddress;
	MEMORY_BASIC_INFORMATION memoryInfo;
	while (pMemory < systemInfo.lpMaximumApplicationAddress)
	{
		if (VirtualQuery(pMemory, &memoryInfo, sizeof(MEMORY_BASIC_INFORMATION)))
		{
			result.push_back(
				{
					memoryInfo.BaseAddress,
					memoryInfo.RegionSize,
					MemoryState(memoryInfo.State),
					MemoryType(memoryInfo.Type),
					MemoryProtection(memoryInfo.Protect)
				});
			pMemory = (void*)((char*)pMemory + memoryInfo.RegionSize);
		}
		else
		{
			break;
		}
	}
	return result;
}

std::vector<MemoryInfo> GetReadWriteMemoryRegions(const std::vector<MemoryInfo>& memoryRegionsInfo)
{
	std::vector<MemoryInfo> result;
	for (const auto& memoryRegionInfo : memoryRegionsInfo)
	{
		if (memoryRegionInfo.State == MemoryState::Commit
			&& !IsGuard(memoryRegionInfo.Protect)
			&& CanRead(memoryRegionInfo.Protect)
			&& CanWrite(memoryRegionInfo.Protect))
		{
			result.push_back(memoryRegionInfo);
		}
	}
	return result;
}