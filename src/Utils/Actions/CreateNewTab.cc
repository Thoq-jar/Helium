#include "Actions.h"

wxWebView* PurrooserFrame::CreateNewTab(const wxString& url) {
  const auto panel = new wxPanel(m_notebook);
  auto* sizer = new wxBoxSizer(wxVERTICAL);
  auto* webView = wxWebView::New(panel, wxID_ANY, url);

  if (!webView) {
    cout << "Failed to create wxWebView" << endl;
    return nullptr;
  }

  webView->SetUserAgent(
      "Mozilla/5.0 (Purr; 'Light' web Renderer) Purrooser 1.0.27 Nightly "
      "AppleWebKit/605.1.15 (KHTML, like Gecko)");
  sizer->Add(webView, 1, wxEXPAND);

  webView->Bind(wxEVT_WEBVIEW_NAVIGATING, &PurrooserFrame::OnSiteLoading, this);
  webView->Bind(wxEVT_WEBVIEW_LOADED, &PurrooserFrame::OnSiteLoaded, this);
  webView->Bind(wxEVT_WEBVIEW_NAVIGATED, &PurrooserFrame::OnSiteNavigated,
                this);
  webView->Bind(wxEVT_WEBVIEW_ERROR, &PurrooserFrame::OnSiteError, this);

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