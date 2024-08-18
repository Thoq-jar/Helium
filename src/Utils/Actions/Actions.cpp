#include "../../Main.hpp"

const string FINAL_ENGINE = "https://" + DEFAULT_SEARCH + "." + SEARCH_TLD;

wxWebView *PurrooserFrame::CreateNewTab(const wxString &url) {
  auto *panel = new wxPanel(m_notebook);
  auto *sizer = new wxBoxSizer(wxVERTICAL);

  auto *webView = wxWebView::New(panel, wxID_ANY, url);
  if (!webView) {
    cout << "Failed to create wxWebView" << endl;
    return nullptr;
  }
  sizer->Add(webView, 1, wxEXPAND);

  panel->SetSizer(sizer);
  m_notebook->AddPage(panel, webView->GetCurrentTitle(), true);

  webView->Bind(wxEVT_WEBVIEW_TITLE_CHANGED, [this, webView](wxWebViewEvent &) {
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
    Utils::Alert("Purrooser", "Hey there! Light mode isn't currently finished! Please check back another time!");
    // backgroundColor = wxColor(100, 100, 100);
    // textColor = wxColor(230, 230, 230);
  } else {
    Utils::Alert("Purrooser (FATAL ERROR)",
                 "Oops! The theme you selected is invalid! Please restart the application and try again!");
  }

  if (backgroundColor.IsOk() && textColor.IsOk()) {
    m_notebook->SetBackgroundColour(backgroundColor);
    m_notebook->SetForegroundColour(textColor);
    SetBackgroundColour(backgroundColor);
    SetForegroundColour(textColor);
    m_searchCtrl->SetBackgroundColour(backgroundColor);
    m_searchCtrl->SetForegroundColour(textColor);
    m_newTabButton->SetBackgroundColour(backgroundColor);
    m_newTabButton->SetForegroundColour(textColor);

    for (size_t i = 0; i < m_notebook->GetPageCount(); ++i) {
      const auto panel = dynamic_cast<wxPanel *>(m_notebook->GetPage(i));
      if (panel) {
        panel->SetBackgroundColour(backgroundColor);
        panel->SetForegroundColour(textColor);
      }
    }

    Refresh();
    Update();
  } else {
    cout << "Invalid color detected in ApplyTheme" << endl;
  }
}

void PurrooserFrame::OnSearch(wxCommandEvent &event) {
  wxString url = m_searchCtrl->GetValue();
  if (!url.StartsWith("https://") && !url.StartsWith("http://")) {
    if (url.find('.') == wxNOT_FOUND) {
      url = FINAL_ENGINE + "/" + SEARCH_QUERY_TAG + url;
    } else {
      url = "https://" + url;
    }
  }
  CreateNewTab(url);
}

void PurrooserFrame::OnNewTab(wxCommandEvent &event) {
  CreateNewTab(FINAL_ENGINE);
}

void PurrooserFrame::OnCloseTab(wxCommandEvent &event) {
  const int selection = m_notebook->GetSelection();
  if (selection != wxNOT_FOUND) {
    m_notebook->DeletePage(selection);
  }
}

void PurrooserFrame::OnToggleTheme(wxCommandEvent &event) {
  m_currentTheme = (m_currentTheme == Theme::LIGHT) ? Theme::DARK : Theme::LIGHT;
  ApplyTheme();
}

void PurrooserFrame::OnQuit(wxCommandEvent & WXUNUSED(event)) {
  cout << "Goodbye!" << endl;
  Close(true);
}

void PurrooserFrame::OnSearchEngineChange(wxCommandEvent &event) {
  const wxString selectedEngine = m_searchEngineChoice->GetStringSelection();
  OnCloseTab(event);
  CreateNewTab("https://www." + selectedEngine + ".com");
}