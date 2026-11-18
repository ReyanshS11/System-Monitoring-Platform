cmake_minimum_required(VERSION 3.10.0)
project(SystemMonitoringPlatform VERSION 0.1.0 LANGUAGES C CXX)

add_executable(SystemMonitoringPlatform 
    src/main.cpp
    src/CPU/cpu.h
    src/system/system_info.h
    src/system/system_info.cpp
    src/CPU/windows.cpp
)