#include "gpu.h"

#include <Windows.h>
#include <Pdh.h>

struct GPUStats {
    double utilization = 0;
    double VRAM = 0;
};

double getGPUUsage()
{
    GPUStats stats = {};

    PDH_HQUERY query;
    PDH_HCOUNTER counter;

    if (PdhOpenQueryW(nullptr, 0, &query) != ERROR_SUCCESS)
    {
        return -1.0;
    }

    if (PdhAddEnglishCounterW(
        query,
        L"\\GPU Engine(*)\\Utilization Percentage",
        0,
        &counter
    ) != ERROR_SUCCESS)
    {
        return -1.0;
    }

    PdhCollectQueryData(query);

    Sleep(500);

    if (PdhCollectQueryData(query) != ERROR_SUCCESS)
    {
        PdhCloseQuery(query);
        return -1.0;
    }

    PDH_FMT_COUNTERVALUE value;

    if(PdhGetFormattedCounterValue(
        counter,
        PDH_FMT_DOUBLE,
        nullptr,
        &value
    ) == ERROR_SUCCESS)
    {
        stats.utilization = value.doubleValue;
    }

    return stats.utilization;
}