#include "Actions.h"

void HeliumFrame::OnCloseTab(wxCommandEvent& event) {
  const int selection = m_notebook->GetSelection();
  if (selection != wxNOT_FOUND) {
    m_notebook->DeletePage(selection);
  }
}