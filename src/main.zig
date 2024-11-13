const std = @import("std");
const c = @cImport({
    @cInclude("c_wrapper.h");
});

pub fn main() !void {
    c.disable_debug_support();

    const app = c.create_helium();
    c.set_app_instance(app);

    const argc: c_int = 0;
    const argv: [*c][*c]u8 = null;

    _ = c.entry_start(argc, @ptrCast(argv));

    const wx_app = c.get_wx_app();
    _ = c.call_on_init(wx_app);
    _ = c.run_app(wx_app);
    _ = c.on_exit(wx_app);

    c.entry_cleanup();
}
