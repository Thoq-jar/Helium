genrule(
    name = "Purrooser",
    srcs = [],
    outs = ["build_output.txt"],
    cmd = """
    if [[ -d "buildDir" ]]; then
        meson compile -C buildDir
        ./buildDir/purrooser
    else
        meson setup buildDir
        meson compile -C buildDir
        ./buildDir/purrooser
    fi
    echo "Build completed" > build_output.txt
    """,
)

genrule(
    name = "windows",
    srcs = [],
    outs = ["windows_build_output.txt"],
    cmd = """
    if [ -d "buildWindows" ]; then
        rm -rf buildWindows
    fi

    meson setup buildWindows --cross-file windows_cross.txt
    cd buildWindows || exit
    ninja
    cd ..
    echo "Windows build completed" > windows_build_output.txt
    """,
)

genrule(
    name = "linux",
    srcs = [],
    outs = ["linux_build_output.txt"],
    cmd = """
    if [ -d "buildLinux" ]; then
        rm -rf buildLinux
    fi

    meson setup buildLinux --cross-file linux_cross.txt
    cd buildLinux || exit
    ninja
    cd ..
    echo "Linux build completed" > linux_build_output.txt
    """,
)

genrule(
    name = "install",
    srcs = [],
    outs = ["install_build_output.txt"],
    cmd = """
    meson setup buildDir
    meson compile -C buildDir
    echo "Install build completed" > install_build_output.txt
    """,
)

genrule(
    name = "postinstall",
    srcs = [],
    outs = ["postinstall_build_output.txt"],
    cmd = """
    cd ~
    rm -rf .purroosertemp
    purrooser > postinstall_build_output.txt
    """,
)
