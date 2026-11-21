#include "memory.h"

#include <iostream>
#include <fstream>
#include <string>

MemoryStats getMemoryStats()
{
    MemoryStats stats = {};

    std::ifstream file("/proc/meminfo");
    std::string key;
    std::uint64_t value;
    std::string unit;

    while (file >> key >> value >> unit)
    {
        if (key == "MemTotal:") stats.totalPhys = value * 1024;
        if (key == "MemAvailable:") stats.availPhys = value * 1024;
    }

    stats.usedPhys = stats.totalPhys - stats.availPhys;

    return stats;
}