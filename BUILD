build_cmd = """
meson configure buildDir --buildtype=release
meson compile -C buildDir > $@
"""

build_run_cmd = """
meson configure buildDir --buildtype=release
meson compile -C buildDir > $@
./buildDir/Purrooser
"""

genrule(
    name = "PurrooserBuild",
    outs = ["build"],
    cmd = build_cmd,
)

genrule(
    name = "PurrooserRun",
    outs = ["Purrooser"],
    cmd = build_run_cmd,
)
