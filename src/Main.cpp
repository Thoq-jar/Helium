#include "Main.hpp"

int main(int argc, char **argv) {
  wxDISABLE_DEBUG_SUPPORT();

  wxApp::SetInstance(new Purrooser());
  wxEntryStart(argc, argv);
  wxTheApp->CallOnInit();
  wxTheApp->OnRun();
  wxTheApp->OnExit();
  wxEntryCleanup();

  return 0;
}
