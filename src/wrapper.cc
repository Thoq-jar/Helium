#include "wrapper.h"

extern "C" {
    void disable_debug_support(void) {
        wxDISABLE_DEBUG_SUPPORT();
    }

    wxApp* create_helium(void) {
        return new Helium();
    }

    void set_app_instance(wxApp* app) {
        wxApp::SetInstance(app);
    }

    int entry_start(int argc, char** argv) {
        return wxEntryStart(argc, argv);
    }

    void entry_cleanup(void) {
        wxEntryCleanup();
    }

    wxApp* get_wx_app(void) {
        return wxTheApp;
    }

    int call_on_init(wxApp* app) {
        return app->CallOnInit();
    }

    int run_app(wxApp* app) {
        return app->OnRun();
    }

    int on_exit(wxApp* app) {
        return app->OnExit();
    }
}
