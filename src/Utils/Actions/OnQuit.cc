#include "Actions.h"

void HeliumFrame::OnQuit(wxCommandEvent& WXUNUSED(event)) {
  cout << "Goodbye!" << endl;
  Close(true);
}
