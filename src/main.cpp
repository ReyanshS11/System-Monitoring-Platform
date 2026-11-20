#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>

#include "CPU/cpu.h"
#include "memory/memory.h"

int main(int, char**){
    while (true)
    {
        std::cout << "CPU Usage: " << round(getCPUUsage()) << "%" << "\n\n";

        MemoryStats mem = getMemoryStats();
        std::cout << "Memory Statistics - \n"
                    << "    Total Memory: " << round((mem.totalPhys / 1073741824.0) * 10.0) / 10.0 << "GB" << "\n"
                    << "    Available Memory: " << round((mem.availPhys / 1073741824.0) * 10.0) / 10.0 << "GB" << "\n"
                    << "    Used Memory: " << round((mem.usedPhys / 1073741824.0) * 10.0) / 10.0 << "GB" << "\n\n\n";

        std::this_thread::sleep_for(
            std::chrono::seconds(1)
        );
    }
}
