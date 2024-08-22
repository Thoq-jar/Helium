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
    """,
)

genrule(
    name = "install",
    srcs = [],
    outs = ["install_build_output.txt"],
    cmd = """
    bazel build //:Purrooser --spawn_strategy=standalone
    """,
)

genrule(
    name = "post-install",
    srcs = [],
    outs = ["install_build_output.txt"],
    cmd = """
    cd ~
    rm -rf .purroosertemp
    purrooser
    """,
)
