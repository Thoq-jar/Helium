#ifndef C_WRAPPER_H
#define C_WRAPPER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct wxApp wxApp;

void disable_debug_support(void);
wxApp* create_helium(void);
void set_app_instance(wxApp* app);
int entry_start(int argc, char** argv);
void entry_cleanup(void);
wxApp* get_wx_app(void);
int call_on_init(wxApp* app);
int run_app(wxApp* app);
int on_exit(wxApp* app);

#ifdef __cplusplus
}
#endif

#endif
