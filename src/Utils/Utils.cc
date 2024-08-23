#include "Utils.hh"

void Utils::Alert(const wxString &title, const wxString &message) {
  wxMessageDialog dlg(nullptr, message, title, wxOK | wxICON_INFORMATION | wxSTAY_ON_TOP);
  dlg.ShowModal();
}
