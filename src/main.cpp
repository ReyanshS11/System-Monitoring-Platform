#include <iostream>
#include <stdlib.h>
#include <thread>
#include <chrono>
#include <cmath>

#include "CPU/cpu.h"
#include "memory/memory.h"
#include "GPU/gpu.h"

int main(int, char**){
    std::cout << "\033[?25l";

    while (true)
    {
        std::cout << "\033[H";

        std::cout << "CPU Usage: " << round(getCPUUsage()) << "%" << "\n\n";

        MemoryStats mem = getMemoryStats();
        std::cout << "Memory Statistics - \n"
                    << "    Total Memory: " << round((mem.totalPhys / 1073741824.0) * 10.0) / 10.0 << "GB" << "\n"
                    << "    Available Memory: " << round((mem.availPhys / 1073741824.0) * 10.0) / 10.0 << "GB" << "\n"
                    << "    Used Memory: " << round((mem.usedPhys / 1073741824.0) * 10.0) / 10.0 << "GB" << "\n\n\n";

        std::cout << "GPU Usage: " << round(getGPUUsage()) << "%" << "\n\n" << std::flush;

        std::this_thread::sleep_for(
            std::chrono::milliseconds(500)
        );
    }

    std::cout << "\033[?25h";
}
