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
