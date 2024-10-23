set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
set(CMAKE_RC_COMPILER x86_64-w64-mingw32-windres)

set(CMAKE_FIND_ROOT_PATH /usr/local/Cellar/mingw-w64/)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

set(wxWidgets_ROOT_DIR "/opt/homebrew/Cellar/wxwidgets/3.2.6")
set(wxWidgets_INCLUDE_DIRS "${wxWidgets_ROOT_DIR}/include/wx-3.2")
set(wxWidgets_LIBRARIES "${wxWidgets_ROOT_DIR}/lib/libwx_baseu-3.2.dylib;${wxWidgets_ROOT_DIR}/lib/libwx_osx_cocoau_core-3.2.dylib;${wxWidgets_ROOT_DIR}/lib/libwx_osx_cocoau_aui-3.2.dylib;${wxWidgets_ROOT_DIR}/lib/libwx_osx_cocoau_webview-3.2.dylib")

set(CMAKE_PREFIX_PATH "${wxWidgets_ROOT_DIR}/lib/cmake/wxWidgets")

find_package(wxWidgets REQUIRED COMPONENTS core base webview)
include(${wxWidgets_USE_FILE})

message(STATUS "wxWidgets_ROOT_DIR: ${wxWidgets_ROOT_DIR}")
message(STATUS "wxWidgets_LIBRARIES: ${wxWidgets_LIBRARIES}")
message(STATUS "wxWidgets_INCLUDE_DIRS: ${wxWidgets_INCLUDE_DIRS}")