cmake_minimum_required(VERSION 3.28)
project(Helium)

set(CMAKE_CXX_STANDARD 14)

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

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Helium.app/Contents/MacOS)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/Helium.app/Contents/MacOS)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/Helium.app/Contents/Resources)
file(COPY assets/AppIcon.icns DESTINATION ${CMAKE_BINARY_DIR}/Helium.app/Contents/Resources)
file(WRITE ${CMAKE_BINARY_DIR}/Helium.app/Contents/Info.plist
        "<plist version=\"1.0\">
<dict>
    <key>CFBundleName</key>
    <string>Helium</string>
    <key>CFBundleVersion</key>
    <string>1.0</string>
    <key>CFBundleIdentifier</key>
    <string>dev.thoq.helium</string>
    <key>CFBundleIconFile</key>
	<string>AppIcon</string>
	<key>CFBundleIconName</key>
	<string>AppIcon</string>
</dict>
</plist>")

add_custom_command(TARGET Helium POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E rename
        ${CMAKE_CURRENT_BINARY_DIR}/Helium
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Helium
)

add_custom_command(TARGET Helium POST_BUILD
        COMMAND chmod +x ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Helium
)

add_custom_command(TARGET Helium POST_BUILD
        COMMAND cp ${CMAKE_BINARY_DIR}/Helium.app/Contents/Resources/AppIcon.icns ${CMAKE_BINARY_DIR}/Helium.app/Contents/Resources/AppIcon.icns
)