#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <thread>
#include <chrono>

#include "cpu.h"

struct CPUStats {
    unsigned long long user = 0;
    unsigned long long nice = 0;
    unsigned long long system = 0;
    unsigned long long idle = 0;
    unsigned long long iowait = 0;
    unsigned long long irq = 0;
    unsigned long long softirq = 0;
    unsigned long long steal = 0;
};

CPUStats readCPU()
{
    std::ifstream file {"/proc/stat"};
    std::string line;
    std::getline(file, line);

    std::istringstream iss {line};
    std::string cpuLabel;
    CPUStats s;
    iss >> cpuLabel >> s.user >> s.nice >> s.system >> s.idle >> s.iowait >> s.irq >> s.softirq >> s.steal;
    return s;
}

unsigned long long total(const CPUStats& s)
{
    return s.user + s.nice + s.system + s.iowait + s.irq + s.softirq + s.steal + s.idle;
}

double getCPUUsage()
{
    CPUStats a = readCPU();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    CPUStats b = readCPU();

    auto totalDiff = total(b) - total(a);
    auto idleDiff = b.idle - a.idle;

    double usage = 100.0 * (totalDiff - idleDiff) / totalDiff;
    return usage;
}