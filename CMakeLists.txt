cmake_minimum_required(VERSION 3.28)
project(Purrooser)

set(CMAKE_CXX_STANDARD 14)

find_package(wxWidgets REQUIRED COMPONENTS core base webview)
include(${wxWidgets_USE_FILE})

add_executable(
        Purrooser
        src/Main.cpp
        src/Purrooser/Purrooser.cpp
        src/Window/PurrooserFrame.cpp
        src/utils/Utils.cpp

        src/Main.hpp
        src/Purrooser/Purrooser.hpp
        src/Window/PurrooserFrame.hpp
        src/utils/Utils.hpp
)
target_link_libraries(Purrooser ${wxWidgets_LIBRARIES})
