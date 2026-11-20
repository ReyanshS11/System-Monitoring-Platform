#pragma once

#include <cstdint>

struct MemoryStats {
    uint64_t totalPhys = 0;
    uint64_t availPhys = 0;
    uint64_t usedPhys = 0;
};

MemoryStats getMemoryStats();