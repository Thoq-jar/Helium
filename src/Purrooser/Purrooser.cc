#include "Purrooser.h"

bool Purrooser::OnInit() {
  cout << BANNER << endl;
  cout << "Starting Purrooser..." << endl;
  wxLog::SetLogLevel(wxLOG_FatalError);

  auto *frame = new PurrooserFrame("Purr");

  ActionsInit();

  frame->Show(true);
  wxCommandEvent event;
  cout << "Purrooser started successfully!" << endl;
  return true;
}