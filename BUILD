genrule(
    name = "Purrooser",
    srcs = ["build-utils/purr_run.star"],
    outs = ["Purrooser.txt"],
    cmd = "sh build-utils/purr_run.star && touch $@",
    visibility = ["//visibility:public"],
)

genrule(
    name = "Install",
    srcs = ["build-utils/install.star"],
    outs = ["PurrooserInstall.txt"],
    cmd = "sh build-utils/install.star && touch $@",
    visibility = ["//visibility:public"],
)

genrule(
    name = "WindowsCC",
    srcs = ["build-utils/windows_cc.star"],
    outs = ["PurrooserWindowsCC.txt"],
    cmd = "sh build-utils/windows_cc.star && touch $@",
    visibility = ["//visibility:public"],
)

genrule(
    name = "LinuxCC",
    srcs = ["build-utils/linux_cc.star"],
    outs = ["PurrooserLinuxCC.txt"],
    cmd = "sh build-utils/linux_cc.star && touch $@",
    visibility = ["//visibility:public"],
)
