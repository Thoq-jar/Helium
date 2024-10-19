#include "Actions.h"

void PurrooserFrame::OnSiteLoading(wxWebViewEvent& event) {
  m_isLoading = true;
  m_reloadButton->SetLabel("⏹");
}