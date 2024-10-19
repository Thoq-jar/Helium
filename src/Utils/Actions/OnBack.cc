#include "Actions.h"

void PurrooserFrame::OnBack(wxCommandEvent& event) {
  if (m_notebook->GetPageCount() == 0) {
    return;
  }
  const auto webView =
      dynamic_cast<wxWebView*>(m_notebook->GetCurrentPage()->GetChildren()[0]);
  if (webView && webView->CanGoBack()) {
    webView->GoBack();
  }
}