purrooser_run = """
if [[ -d "buildDir" ]]; then
    meson compile -C buildDir
    ./buildDir/purrooser
else
    meson setup buildDir
    meson compile -C buildDir
    ./buildDir/purrooser
fi
touch $@  # Ensure the output file is created
"""

window_crosscompile = """
if [ -d "buildWindows" ]; then
    rm -rf buildWindows
fi

meson setup buildWindows --cross-file windows_cross.txt
cd buildWindows || exit
ninja
cd ..
touch $@  # Ensure the output file is created
"""

linux_crosscompile = """
if [ -d "buildLinux" ]; then
    rm -rf buildLinux
fi

meson setup buildLinux --cross-file linux_cross.txt
cd buildLinux || exit
ninja
cd ..
touch $@  # Ensure the output file is created
"""

install_code = """
if [[ -d "buildDir" ]]; then
    meson compile -C buildDir
    ./buildDir/purrooser
else
    meson setup buildDir
    meson compile -C buildDir
fi
touch $@  # Ensure the output file is created
"""

post_install = """
cd ~
rm -rf .purroosertemp
touch $@  # Ensure the output file is created
"""

genrule(
    name = "Purrooser",
    srcs = [],
    outs = ["build_output.txt"],
    cmd = purrooser_run,
)

genrule(
    name = "windows",
    srcs = [],
    outs = ["windows_build_output.txt"],
    cmd = window_crosscompile,
)

genrule(
    name = "linux",
    srcs = [],
    outs = ["linux_build_output.txt"],
    cmd = linux_crosscompile,
)

genrule(
    name = "install",
    srcs = [],
    outs = ["install_output.txt"],
    cmd = install_code,
)

genrule(
    name = "postinstall",
    srcs = [],
    outs = ["postinstall_build_output.txt"],
    cmd = post_install,
)
