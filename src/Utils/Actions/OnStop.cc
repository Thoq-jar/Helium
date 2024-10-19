#include "Actions.h"

void PurrooserFrame::OnStop(wxCommandEvent& event) {
  if (m_notebook->GetPageCount() == 0) {
    return;
  }
  auto const webView =
      dynamic_cast<wxWebView*>(m_notebook->GetCurrentPage()->GetChildren()[0]);
  if (webView) {
    webView->Stop();
    m_isLoading = false;
    m_reloadButton->SetLabel(RELOAD_ICON);
  }
}