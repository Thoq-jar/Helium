cmake_minimum_required(VERSION 3.28)
project(Purrooser)

set(CMAKE_CXX_STANDARD 14)

find_package(wxWidgets REQUIRED COMPONENTS core base webview)
include(${wxWidgets_USE_FILE})

add_executable(
        Purrooser
        src/Main.cpp
        src/Purrooser/Purrooser.cpp
        src/Purrooser/Purrooser.h
        src/Window/PurrooserFrame.cpp
        src/Window/PurrooserFrame.h
        src/Main.h
)
target_link_libraries(Purrooser ${wxWidgets_LIBRARIES})
