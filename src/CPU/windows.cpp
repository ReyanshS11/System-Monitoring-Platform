#include "cpu.h"

#include <Windows.h>

#include <thread>
#include <chrono>

struct CPUStats {
    FILETIME lpIdleTime;
    FILETIME lpKernelTime;
    FILETIME lpUserTime;
};

CPUStats readCPU()
{
    CPUStats stats = {};
    GetSystemTimes(&stats.lpIdleTime, &stats.lpKernelTime, &stats.lpUserTime);

    return stats;
}

unsigned long long convertFileTime(FILETIME time) {
    ULARGE_INTEGER result;

    result.LowPart = time.dwLowDateTime;
    result.HighPart = time.dwHighDateTime;

    return result.QuadPart;
}

unsigned long long total(CPUStats stats)
{
    return convertFileTime(stats.lpKernelTime) + convertFileTime(stats.lpUserTime);
}

double getCPUUsage()
{
    CPUStats a = readCPU();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    CPUStats b = readCPU();

    auto totalDiff = total(b) - total(a);
    auto idleDiff = convertFileTime(b.lpIdleTime) - convertFileTime(a.lpIdleTime);

    double usage = 100.0 * (totalDiff - idleDiff) / totalDiff;
    return usage;
}