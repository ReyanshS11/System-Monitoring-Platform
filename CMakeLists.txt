cmake_minimum_required(VERSION 3.10.0)
project(SystemMonitoringPlatform VERSION 0.1.0 LANGUAGES C CXX)

if(WIN32)
    set(PLATFORM_SRC
        src/CPU/windows.cpp
        src/memory/windows.cpp)
elseif(LINUX)
    set(PLATFORM_SRC src/CPU/linux.cpp)
endif()

add_executable(SystemMonitoringPlatform 
    src/main.cpp
    src/CPU/cpu.h
    src/system/system_info.h
    src/system/system_info.cpp
    ${PLATFORM_SRC}
    src/memory/memory.h
)