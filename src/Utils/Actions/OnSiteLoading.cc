#include "Actions.h"

void HeliumFrame::OnSiteLoading(wxWebViewEvent& event) {
  m_isLoading = true;
  m_reloadButton->SetLabel("⏹");
}