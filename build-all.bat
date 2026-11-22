@echo off

setlocal

echo ==========================
echo Building Windows version
echo ==========================

cmake -S . -B build-windows -G "Visual Studio 18 2026"
cmake --build build-windows --config Release

echo ==========================
echo Building Linux version
echo ==========================

wsl bash -c "cd '/mnt/c/Reyansh/System Monitoring Platform' && cmake -S . -B build-linux -DCMAKE_BUILD_TYPE=Release && cmake --build build-linux"

echo ==========================
echo Build complete
echo ==========================
