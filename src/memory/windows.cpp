#include "memory.h"

#include <iostream>
#include <Windows.h>

MemoryStats getMemoryStats()
{
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);

    if (GlobalMemoryStatusEx(&memInfo))
    {
        std::uint64_t totalPhys = memInfo.ullTotalPhys;
        std::uint64_t availPhys = memInfo.ullAvailPhys;
        std::uint64_t usedPhys = totalPhys - availPhys;

        MemoryStats stats {totalPhys, availPhys, usedPhys};
        return stats;
    }

    MemoryStats none;
    return none;
}