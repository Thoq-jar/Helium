#include "Actions.h"

void PurrooserFrame::OnSiteLoaded(wxWebViewEvent& event) {
  m_isLoading = false;
  m_reloadButton->SetLabel("↻");
}