#include "Actions.h"

void HeliumFrame::OnSiteNavigated(wxWebViewEvent& event) {
  if (m_notebook->GetPageCount() > 0) {
    auto const webView = dynamic_cast<wxWebView*>(
        m_notebook->GetCurrentPage()->GetChildren()[0]);
    if (webView && m_searchCtrl) {
      const wxString currentURL = webView->GetCurrentURL();
      if (!currentURL.StartsWith("https://helium-api.deno.dev/ui/")) {
        m_searchCtrl->SetValue(currentURL);
      }
    }
  }
}
