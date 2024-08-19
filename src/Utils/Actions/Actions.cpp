#include "../../Main.hpp"

wxWebView* PurrooserFrame::CreateNewTab(const wxString& url) {
  auto* panel = new wxPanel(m_notebook);
  auto* sizer = new wxBoxSizer(wxVERTICAL);

  auto* webView = wxWebView::New(panel, wxID_ANY, url);
  if (!webView) {
    cout << "Failed to create wxWebView" << endl;
    return nullptr;
  }
  sizer->Add(webView, 1, wxEXPAND);

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
      const int selectedIndex = m_searchEngineChoice->GetSelection();
      const wxString selectedEngine = SEARCH_ENGINES[selectedIndex];
      url = selectedEngine + "/" + SEARCH_QUERY_TAG + url;
    } else {
      url = "https://" + url;
    }
  }
  CreateNewTab(url);
}

void PurrooserFrame::OnNewTab(wxCommandEvent &event) {
  const int selectedIndex = m_searchEngineChoice->GetSelection();
  const wxString selectedEngine = SEARCH_ENGINES[selectedIndex];
  CreateNewTab(selectedEngine);
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
  const int selectedIndex = m_searchEngineChoice->GetSelection();
  const wxString selectedEngine = SEARCH_ENGINES[selectedIndex];

  wxString homeDir = wxFileName::GetHomeDir();
  wxString filePath = homeDir + wxFILE_SEP_PATH + "purr_settings.txt";

  ofstream outFile(filePath.ToStdString());
  if (outFile.is_open()) {
    outFile << selectedEngine.ToStdString();
    outFile.close();
  } else {
    Utils::Alert("Error", "Unable to save the settings!");
  }

  cout << "Goodbye!" << endl;
  Close(true);
}

void PurrooserFrame::OnSearchEngineChange(wxCommandEvent &event) {
  const int selectedIndex = m_searchEngineChoice->GetSelection();
  const wxString selectedEngine = SEARCH_ENGINES[selectedIndex];
  OnCloseTab(event);
  CreateNewTab(selectedEngine);
}

void PurrooserFrame::OnBack(wxCommandEvent &event) {
  if (m_notebook->GetPageCount() == 0) {
    return;
  }
  const auto webView = dynamic_cast<wxWebView *>(m_notebook->GetCurrentPage()->GetChildren()[0]);
  if (webView && webView->CanGoBack()) {
    webView->GoBack();
  }
}

void PurrooserFrame::OnForward(wxCommandEvent &event) {
  if (m_notebook->GetPageCount() == 0) {
    return;
  }
  const auto webView = dynamic_cast<wxWebView *>(m_notebook->GetCurrentPage()->GetChildren()[0]);
  if (webView && webView->CanGoForward()) {
    webView->GoForward();
  }
}

void PurrooserFrame::OnHome(wxCommandEvent &event) {
  const int selectedIndex = m_searchEngineChoice->GetSelection();
  const wxString selectedEngine = SEARCH_ENGINES[selectedIndex];
  CreateNewTab(selectedEngine);
}

void PurrooserFrame::OnSaveSearchEngine(wxCommandEvent &event) {
  const int selectedIndex = m_searchEngineChoice->GetSelection();
  const wxString selectedEngine = SEARCH_ENGINES[selectedIndex];

  wxString homeDir = wxFileName::GetHomeDir();
  wxString filePath = homeDir + wxFILE_SEP_PATH + "purr_settings.txt";

  ofstream outFile(filePath.ToStdString());
  if (outFile.is_open()) {
    outFile << selectedEngine.ToStdString();
    outFile.close();
  } else {
    Utils::Alert("Error", "Unable to save the settings!");
  }
}

wstring trim(const wstring& str) {
  const auto start = str.find_first_not_of(L" \t\n\r");
  const auto end = str.find_last_not_of(L" \t\n\r");
  return (start == wstring::npos) ? L"" : str.substr(start, end - start + 1);
}

void PurrooserFrame::LoadSearchEngine() {
  wxString homeDir = wxFileName::GetHomeDir();
  wxString filePath = homeDir + wxFILE_SEP_PATH + "purr_settings.txt";

  if (wxFileName::FileExists(filePath)) {
    wstring wstrFilePath = filePath.ToStdWstring();

    wifstream inFile(reinterpret_cast<const char *>(wstrFilePath.c_str()), ios::in | ios::binary);
    if (inFile.is_open()) {
      wstring wstrSavedEngine;
      getline(inFile, wstrSavedEngine, L'\n');
      inFile.close();

      wstrSavedEngine = trim(wstrSavedEngine);

      if (wstrSavedEngine.empty()) {
        wxLogError("No engine found in file: %s", filePath);
      }

      wxString wxStrSavedEngine(wstrSavedEngine.c_str());

      for (size_t i = 0; i < SEARCH_ENGINES_SIZE; ++i) {
        if (SEARCH_ENGINES[i] == wxStrSavedEngine) {
          m_searchEngineChoice->SetSelection(i);
          return;
        }
      }
    } else {
      wxLogError("Failed to open file: %s", filePath);
    }
  } else {
    wxLogError("File does not exist: %s", filePath);
  }
}