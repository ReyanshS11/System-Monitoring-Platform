#include <iostream>
#include <thread>
#include <chrono>

#include "CPU/cpu.h"

int main(int, char**){
    while (true)
    {
        std::cout << getCPUUsage() << "\n";

        std::this_thread::sleep_for(
            std::chrono::seconds(1)
        );
    }
}
