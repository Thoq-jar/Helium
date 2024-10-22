#include "Actions.h"

wxWebView* HeliumFrame::CreateNewTab(const wxString& url) {
  const auto panel = new wxPanel(m_notebook);
  auto* sizer = new wxBoxSizer(wxVERTICAL);
  auto* webView = wxWebView::New(panel, wxID_ANY, url);

  if (!webView) {
    cout << "Failed to create wxWebView" << endl;
    return nullptr;
  }

  sizer->Add(webView, 1, wxEXPAND);

  webView->Bind(wxEVT_WEBVIEW_NAVIGATING, &HeliumFrame::OnSiteLoading, this);
  webView->Bind(wxEVT_WEBVIEW_LOADED, &HeliumFrame::OnSiteLoaded, this);
  webView->Bind(wxEVT_WEBVIEW_NAVIGATED, &HeliumFrame::OnSiteNavigated,
                this);
  webView->Bind(wxEVT_WEBVIEW_ERROR, &HeliumFrame::OnSiteError, this);

  panel->SetSizer(sizer);
  m_notebook->AddPage(panel, webView->GetCurrentTitle(), true);

  webView->Bind(wxEVT_WEBVIEW_TITLE_CHANGED, [this, webView](wxWebViewEvent&) {
    const int pageIndex = m_notebook->FindPage(webView->GetParent());
    if (pageIndex != wxNOT_FOUND) {
      m_notebook->SetPageText(pageIndex, webView->GetCurrentTitle());
    }
  });

  if (m_currentTheme == Theme::DARK) {
    ApplyTheme();
  }

  return webView;
}