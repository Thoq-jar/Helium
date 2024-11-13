const std = @import("std");
const builtin = @import("builtin");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const exe = b.addExecutable(.{
        .name = "Nebulae",
        .root_source_file = b.path("src/main.zig"),
        .target = target,
        .optimize = optimize,
    });

    const cpp_source_files = [_][]const u8{
        "src/wrapper.cc",
        "src/Helium/Helium.cc",
        "src/Window/HeliumFrame.cc",
        "src/Utils/Utils.cc",
        "src/Utils/Actions/Actions.cc",
        "src/Utils/Actions/CreateNewTab.cc",
        "src/Utils/Actions/ToggleUIElements.cc",
        "src/Utils/Actions/ApplyTheme.cc",
        "src/Utils/Actions/OnQuit.cc",
        "src/Utils/Actions/OnToggleTheme.cc",
        "src/Utils/Actions/OnSearch.cc",
        "src/Utils/Actions/OnNewTab.cc",
        "src/Utils/Actions/OnCloseTab.cc",
        "src/Utils/Actions/FullScreenToggle.cc",
        "src/Utils/Actions/OnSiteNavigated.cc",
        "src/Utils/Actions/OnHome.cc",
        "src/Utils/Actions/OnSiteError.cc",
        "src/Utils/Actions/OnSiteLoaded.cc",
        "src/Utils/Actions/OnSiteLoading.cc",
        "src/Utils/Actions/OnStop.cc",
        "src/Utils/Actions/OnBack.cc",
        "src/Utils/Actions/OnForward.cc",
        "src/Utils/Actions/Trim.cc",
        "src/Utils/Actions/OnReload.cc",
    };

    const cpp_flags = [_][]const u8{
        "-std=c++23",
        "-D_FILE_OFFSET_BITS=64",
        "-DWXUSINGDLL",
        "-D__WXMAC__",
        "-D__WXOSX__",
        "-D__WXOSX_COCOA__",
        "-DwxDEBUG_LEVEL=0",
    };

    for (cpp_source_files) |file| {
        exe.addCSourceFile(.{
            .file = .{ .cwd_relative = file },
            .flags = &cpp_flags,
        });
    }

    exe.addIncludePath(.{ .cwd_relative = "/opt/homebrew/include" });
    exe.addIncludePath(.{ .cwd_relative = "/opt/homebrew/opt/wxwidgets@3.2/include" });
    exe.addIncludePath(.{ .cwd_relative = "/opt/homebrew/opt/wxwidgets@3.2/include/wx-3.2" });
    exe.addIncludePath(.{ .cwd_relative = "/opt/homebrew/opt/wxwidgets@3.2/lib/wx/include/osx_cocoa-unicode-3.2" });

    exe.addLibraryPath(.{ .cwd_relative = "/opt/homebrew/lib" });

    exe.linkFramework("IOKit");
    exe.linkFramework("Carbon");
    exe.linkFramework("Cocoa");
    exe.linkFramework("QuartzCore");
    exe.linkFramework("AudioToolbox");
    exe.linkFramework("System");
    exe.linkFramework("OpenGL");
    exe.linkFramework("WebKit");
    exe.linkFramework("Security");
    exe.linkFramework("ApplicationServices");

    exe.linkSystemLibrary("wx_osx_cocoau_webview-3.2");
    exe.linkSystemLibrary("wx_osx_cocoau_xrc-3.2");
    exe.linkSystemLibrary("wx_osx_cocoau_html-3.2");
    exe.linkSystemLibrary("wx_osx_cocoau_qa-3.2");
    exe.linkSystemLibrary("wx_osx_cocoau_adv-3.2");
    exe.linkSystemLibrary("wx_osx_cocoau_core-3.2");
    exe.linkSystemLibrary("wx_baseu_xml-3.2");
    exe.linkSystemLibrary("wx_baseu_net-3.2");
    exe.linkSystemLibrary("wx_baseu-3.2");

    exe.linkSystemLibrary("z");
    exe.linkSystemLibrary("iconv");
    exe.linkSystemLibrary("c++");

    exe.linkLibCpp();
    exe.addIncludePath(.{ .cwd_relative = "src" });

    b.installArtifact(exe);

    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());

    if (b.args) |args| {
        run_cmd.addArgs(args);
    }

    const run_step = b.step("run", "Run the browser");
    run_step.dependOn(&run_cmd.step);

    const exe_unit_tests = b.addTest(.{
        .root_source_file = b.path("src/main.zig"),
        .target = target,
        .optimize = optimize,
    });

    const run_exe_unit_tests = b.addRunArtifact(exe_unit_tests);
    const test_step = b.step("test", "Run unit tests");
    test_step.dependOn(&run_exe_unit_tests.step);
}
