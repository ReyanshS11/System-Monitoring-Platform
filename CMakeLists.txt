cmake_minimum_required(VERSION 3.10.0)
project(SystemMonitoringPlatform VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(WIN32)
    set(PLATFORM_SRC
        src/CPU/windows.cpp
        src/memory/windows.cpp)
elseif(LINUX)
    set(PLATFORM_SRC
        src/CPU/linux.cpp
        src/memory/linux.cpp)
endif()

add_executable(SystemMonitoringPlatform
    src/main.cpp
    src/CPU/cpu.h
    src/system/system_info.h
    src/system/system_info.cpp
    src/memory/memory.h
    ${PLATFORM_SRC}
)

find_package(imgui CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(implot CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    imgui::imgui
    OpenGL::GL
    implot::implot
)