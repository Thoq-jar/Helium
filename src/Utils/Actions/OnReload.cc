#include "Actions.h"

void HeliumFrame::OnReload(wxCommandEvent& event) {
  if (m_notebook->GetPageCount() == 0) {
    return;
  }
  auto const webView =
      dynamic_cast<wxWebView*>(m_notebook->GetCurrentPage()->GetChildren()[0]);
  if (webView) {
    if (m_isLoading) {
      webView->Stop();
      m_isLoading = false;
      m_reloadButton->SetLabel(RELOAD_ICON);
    } else {
      webView->Reload();
      m_isLoading = true;
      m_reloadButton->SetLabel(STOP_ICON);
    }
  }
}