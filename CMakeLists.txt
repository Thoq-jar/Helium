cmake_minimum_required(VERSION 3.28)
project(Helium)

set(CMAKE_CXX_STANDARD 23)

find_package(wxWidgets REQUIRED COMPONENTS core base webview)
include(${wxWidgets_USE_FILE})

set(CMAKE_BUILD_TYPE MinSizeRel)

if (CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
    add_compile_options(-O3 -DNDEBUG)
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(-O3 -DNDEBUG)
endif ()

add_executable(
        Helium
        src/Main.cc
        src/Helium/Helium.cc
        src/Window/HeliumFrame.cc
        src/Utils/Utils.cc
        src/Utils/Actions/Actions.cc
        src/Utils/Actions/CreateNewTab.cc
        src/Utils/Actions/ToggleUIElements.cc
        src/Utils/Actions/ApplyTheme.cc
        src/Utils/Actions/OnQuit.cc
        src/Utils/Actions/OnToggleTheme.cc
        src/Utils/Actions/OnSearch.cc
        src/Utils/Actions/OnNewTab.cc
        src/Utils/Actions/OnCloseTab.cc
        src/Utils/Actions/FullScreenToggle.cc
        src/Utils/Actions/OnSiteNavigated.cc
        src/Utils/Actions/OnHome.cc
        src/Utils/Actions/OnSiteError.cc
        src/Utils/Actions/OnSiteLoaded.cc
        src/Utils/Actions/OnSiteLoading.cc
        src/Utils/Actions/OnStop.cc
        src/Utils/Actions/OnBack.cc
        src/Utils/Actions/OnForward.cc
        src/Utils/Actions/Trim.cc
        src/Utils/Actions/OnReload.cc
)

target_link_libraries(Helium ${wxWidgets_LIBRARIES})

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    set_target_properties(Helium PROPERTIES CMAKE_CXX_CLANG_TIDY "clang-tidy;-p;${CMAKE_BINARY_DIR}")
endif()