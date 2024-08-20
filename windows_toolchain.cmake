# windows_toolchain.cmake
# Custom toolchain file for cross-compiling with MinGW-w64 on UNIX (with brew)

set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x86_64)
set(CMAKE_C_COMPILER "/opt/homebrew/bin/x86_64-w64-mingw32-gcc")
set(CMAKE_CXX_COMPILER "/opt/homebrew/bin/x86_64-w64-mingw32-g++")
set(CMAKE_LINKER "/opt/homebrew/bin/x86_64-w64-mingw32-gcc")
set(CMAKE_EXECUTABLE_SUFFIX ".exe")
