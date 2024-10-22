#include "Actions.h"

void HeliumFrame::OnSiteLoaded(wxWebViewEvent& event) {
  m_isLoading = false;
  m_reloadButton->SetLabel("↻");
}