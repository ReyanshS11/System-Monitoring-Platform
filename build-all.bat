@echo off

setlocal

echo ==========================
echo Building Windows version
echo ==========================

cmake -S . -B build-windows -G "Visual Studio 18 2026" ^
    -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg-2026.03.18/scripts/buildsystems/vcpkg.cmake ^
    -DVCPKG_TARGET_TRIPLET=x64-windows
cmake --build build-windows --config Release

echo ==========================
echo Building Linux version
echo ==========================

wsl bash -c "cd '/mnt/c/Reyansh/System Monitoring Platform' && cmake -S . -B build-linux -DCMAKE_TOOLCHAIN_FILE=/home/reyansh/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-linux -DCMAKE_BUILD_TYPE=Release && cmake --build build-linux"

echo ==========================
echo Build complete
echo ==========================
