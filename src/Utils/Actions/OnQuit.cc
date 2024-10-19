#include "Actions.h"

void PurrooserFrame::OnQuit(wxCommandEvent& WXUNUSED(event)) {
  cout << "Goodbye!" << endl;
  Close(true);
}
