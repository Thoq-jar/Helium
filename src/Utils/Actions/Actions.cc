#include <wx/filename.h>
#include <wx/msgdlg.h>
#include <wx/notebook.h>
#include <wx/srchctrl.h>
#include <wx/webview.h>
#include <wx/wx.h>
#include <regex>
#include "../../Main.hh"

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

void PurrooserFrame::ApplyTheme() {
  wxColor backgroundColor;
  wxColor textColor;

  if (m_currentTheme == Theme::DARK) {
    backgroundColor = wxColor(30, 30, 30);
    textColor = wxColor(255, 255, 255);
  } else if (m_currentTheme == Theme::LIGHT) {
    backgroundColor = wxColor(255, 255, 255);
    textColor = wxColor(30, 30, 30);
  } else {
    Utils::Alert("Purrooser (FATAL ERROR)",
                 "Oops! The theme you selected is invalid! Please restart the "
                 "application and try again!");
  }

  if (backgroundColor.IsOk() && textColor.IsOk()) {
    m_notebook->SetForegroundColour(textColor);
    SetBackgroundColour(backgroundColor);
    SetForegroundColour(textColor);
    m_searchCtrl->SetForegroundColour(textColor);
    m_newTabButton->SetForegroundColour(textColor);
    m_closeTabButton->SetForegroundColour(textColor);
    m_backButton->SetForegroundColour(textColor);
    m_forwardButton->SetForegroundColour(textColor);
    m_homeButton->SetForegroundColour(textColor);
    m_errorPageOpened = false;

    for (size_t i = 0; i < m_notebook->GetPageCount(); ++i) {
      const auto panel = dynamic_cast<wxPanel*>(m_notebook->GetPage(i));
      if (panel) {
        panel->SetForegroundColour(textColor);
      }
    }

    Refresh();
    Update();
  } else {
    cout << "Invalid color detected in ApplyTheme" << endl;
  }
}

void PurrooserFrame::OnSearch(wxCommandEvent& event) {
  wxString url = m_searchCtrl->GetValue();
  url.Replace(" ", "+");

  const std::regex tldRegex(R"((\.[a-z]{2,})$)");

  if (url.StartsWith("purr://")) {
    const wxString command = url.AfterFirst('/');
    if (command == "/newtab") {
      CreateNewTab("https://purrooser-api.deno.dev/ui/index.html");
      return;
    }
    if (command == "/error") {
      CreateNewTab("https://purrooser-api.deno.dev/ui/error.html");
      return;
    }
    if (command == "/about") {
      CreateNewTab("https://purrooser-api.deno.dev/ui/about.html");
      return;
    }
    if (command == "/kitty") {
      CreateNewTab("https://purrooser-api.deno.dev/ui/kitty.html");
      return;
    }
    if (command == "/settings") {
      CreateNewTab("https://purrooser-api.deno.dev/ui/settings.html");
      return;
    }
    if (command == "/weather") {
      CreateNewTab("https://purrooser-api.deno.dev/ui/weather.html");
      return;
    }
    Utils::Alert("Purr", "Unknown purr:// URL!");
    return;
  }
  if (!url.StartsWith("http://") && !url.StartsWith("https://")) {
    if (!std::regex_search(url.ToStdString(), tldRegex)) {
      url = "https://google.com/?q=" + url;
    } else {
      url = "https://" + url;
    }
  }

  if (m_notebook->GetPageCount() > 0) {
    const auto webView = dynamic_cast<wxWebView*>(
        m_notebook->GetCurrentPage()->GetChildren()[0]);
    if (webView) {
      webView->LoadURL(url);
    }
  } else {
    CreateNewTab(url);
  }
}

void PurrooserFrame::OnNewTab(wxCommandEvent& event) {
  CreateNewTab("https://purrooser-api.deno.dev/ui/index.html");
}

void PurrooserFrame::OnCloseTab(wxCommandEvent& event) {
  const int selection = m_notebook->GetSelection();
  if (selection != wxNOT_FOUND) {
    m_notebook->DeletePage(selection);
  }
}

void PurrooserFrame::OnToggleTheme(wxCommandEvent& event) {
  m_currentTheme =
      (m_currentTheme == Theme::LIGHT) ? Theme::DARK : Theme::LIGHT;
  ApplyTheme();
}

void PurrooserFrame::OnQuit(wxCommandEvent& WXUNUSED(event)) {
  cout << "Goodbye!" << endl;
  Close(true);
}

void PurrooserFrame::OnForward(wxCommandEvent& event) {
  if (m_notebook->GetPageCount() == 0) {
    return;
  }
  const auto webView =
      dynamic_cast<wxWebView*>(m_notebook->GetCurrentPage()->GetChildren()[0]);
  if (webView && webView->CanGoForward()) {
    webView->GoForward();
  }
}

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

void PurrooserFrame::OnReload(wxCommandEvent& event) {
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

void PurrooserFrame::OnSiteLoading(wxWebViewEvent& event) {
  m_isLoading = true;
  m_reloadButton->SetLabel("⏹");
}

void PurrooserFrame::OnSiteLoaded(wxWebViewEvent& event) {
  m_isLoading = false;
  m_reloadButton->SetLabel("↻");
}

void PurrooserFrame::OnSiteError(wxWebViewEvent& event) {
  if (!m_errorPageOpened) {
    m_errorPageOpened = true;
    return;
  }
}

void PurrooserFrame::OnHome(wxCommandEvent& event) {
  OnCloseTab(event);
  CreateNewTab("https://purrooser-api.deno.dev/ui/index.html");
}

wstring trim(const wstring& str) {
  const auto start = str.find_first_not_of(L" \t\n\r");
  const auto end = str.find_last_not_of(L" \t\n\r");
  return (start == wstring::npos) ? L"" : str.substr(start, end - start + 1);
}

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

void PurrooserFrame::FullScreenToggle(wxCommandEvent& event) {
  if (m_notebook->GetPageCount() > 0) {
    const auto webView = dynamic_cast<wxWebView*>(
        m_notebook->GetCurrentPage()->GetChildren()[0]);
    if (webView) {
      const bool isFullScreen = IsFullScreen();
      ShowFullScreen(!isFullScreen,
                     wxFULLSCREEN_NOBORDER | wxFULLSCREEN_NOCAPTION);
      ToggleUIElements(isFullScreen);
    }
  }
}

void PurrooserFrame::ToggleUIElements(bool show) {
  m_backButton->Show(show);
  m_forwardButton->Show(show);
  m_homeButton->Show(show);
  m_reloadButton->Show(show);
  m_searchButton->Show(show);
  m_searchCtrl->Show(show);
  m_newTabButton->Show(show);
  m_closeTabButton->Show(show);
  Layout();
}
