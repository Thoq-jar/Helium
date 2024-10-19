cmake_minimum_required(VERSION 3.28)
project(Purr)

set(CMAKE_CXX_STANDARD 14)

find_package(wxWidgets REQUIRED COMPONENTS core base webview)
include(${wxWidgets_USE_FILE})

set(CMAKE_BUILD_TYPE MinSizeRel)

if(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
    add_compile_options(-O3 -DNDEBUG)
endif()

add_executable(
        Purr
        src/Main.cc
        src/Purrooser/Purrooser.cc
        src/Window/PurrooserFrame.cc
        src/Utils/Utils.cc
        src/Utils/Actions/Actions.cc
)

target_link_libraries(Purr ${wxWidgets_LIBRARIES})