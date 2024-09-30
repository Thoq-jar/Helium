cmake_minimum_required(VERSION 3.28)
project(Purr)

set(CMAKE_CXX_STANDARD 14)

find_package(wxWidgets REQUIRED COMPONENTS core base webview)
include(${wxWidgets_USE_FILE})

add_executable(
        # Executable
        Purr

        # Sources
        src/Main.cc
        src/Purrooser/Purrooser.cc
        src/Window/PurrooserFrame.cc
        src/utils/Utils.cc
        src/Utils/Actions/Actions.cc

        # Headers
        src/Main.hh
        src/Purrooser/Purrooser.hh
        src/Window/PurrooserFrame.hh
        src/utils/Utils.hh
        src/Utils/Actions/Actions.hh
)

target_link_libraries(Purr ${wxWidgets_LIBRARIES})
