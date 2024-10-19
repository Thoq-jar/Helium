#include "Actions.h"

void PurrooserFrame::OnSiteNavigated(wxWebViewEvent& event) {
  if (m_notebook->GetPageCount() > 0) {
    auto const webView = dynamic_cast<wxWebView*>(
        m_notebook->GetCurrentPage()->GetChildren()[0]);
    if (webView && m_searchCtrl) {
      const wxString currentURL = webView->GetCurrentURL();
      if (!currentURL.StartsWith("https://purrooser-api.deno.dev/ui/")) {
        m_searchCtrl->SetValue(currentURL);
      }
    }
  }
}
