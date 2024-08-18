#include "PurrooserFrame.h"
#include <iostream>

using namespace std;

PurrooserFrame::PurrooserFrame(const wxString &title)
  : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(width, height)), m_currentTheme(Theme::LIGHT) {
  cout << "Creating main frame..." << endl;

  auto *sizer = new wxBoxSizer(wxVERTICAL);

  auto *topSizer = new wxBoxSizer(wxHORIZONTAL);
  m_searchCtrl = new wxSearchCtrl(this, wxID_ANY);
  m_searchCtrl->Bind(wxEVT_TEXT_ENTER, &PurrooserFrame::OnSearch, this);
  topSizer->Add(m_searchCtrl, 1, wxEXPAND | wxALL, 5);

  m_newTabButton = new wxButton(this, wxID_ANY, "New Tab");
  m_newTabButton->Bind(wxEVT_BUTTON, &PurrooserFrame::OnNewTab, this);
  topSizer->Add(m_newTabButton, 0, wxEXPAND | wxALL, 5);

  m_closeTabButton = new wxButton(this, wxID_ANY, "Close Tab");
  m_closeTabButton->Bind(wxEVT_BUTTON, &PurrooserFrame::OnCloseTab, this);
  topSizer->Add(m_closeTabButton, 0, wxEXPAND | wxALL, 5);

  sizer->Add(topSizer, 0, wxEXPAND);

  m_notebook = new wxNotebook(this, wxID_ANY);
  sizer->Add(m_notebook, 1, wxEXPAND | wxALL, 5);

  SetSizer(sizer);

  CreateNewTab("https://www.duckduckgo.com");

  auto *menuFile = new wxMenu;
  menuFile->Append(wxID_EXIT);
  m_toggleThemeItem = menuFile->Append(wxID_ANY, "Toggle Theme");
  Bind(wxEVT_MENU, &PurrooserFrame::OnToggleTheme, this, m_toggleThemeItem->GetId());

  auto *menuBar = new wxMenuBar;
  menuBar->Append(menuFile, "&File");
  wxFrameBase::SetMenuBar(menuBar);
  wxFrameBase::CreateStatusBar();
  Bind(wxEVT_MENU, &PurrooserFrame::OnQuit, this, wxID_EXIT);

  ApplyTheme();
  cout << "Main frame created!" << endl;
}

wxWebView *PurrooserFrame::CreateNewTab(const wxString &url) {
  auto *panel = new wxPanel(m_notebook);
  auto *sizer = new wxBoxSizer(wxVERTICAL);

  auto *webView = wxWebView::New(panel, wxID_ANY, url);
  if (!webView) {
    wxLogError("Failed to create wxWebView");
    return nullptr;
  }
  sizer->Add(webView, 1, wxEXPAND);

  panel->SetSizer(sizer);
  m_notebook->AddPage(panel, webView->GetCurrentTitle(), true);

  webView->Bind(wxEVT_WEBVIEW_TITLE_CHANGED, [this, webView](wxWebViewEvent &) {
    int pageIndex = m_notebook->FindPage(webView->GetParent());
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
  wxColour backgroundColor;
  wxColour textColor;

  if (m_currentTheme == Theme::DARK) {
    backgroundColor = wxColour(30, 30, 30);
    textColor = wxColour(255, 255, 255);
    m_notebook->SetBackgroundColour(backgroundColor);
    m_notebook->SetForegroundColour(textColor);
  } else {
    backgroundColor = wxColour(255, 255, 255);
    textColor = wxColour(0, 0, 0);
  }

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
}

void PurrooserFrame::OnSearch(wxCommandEvent &event) {
  wxString url = m_searchCtrl->GetValue();
  if (!url.StartsWith("https://") && !url.StartsWith("http://")) {
    if (url.find('.') == wxNOT_FOUND) {
      url = "https://www.duckduckgo.com/?q=" + url;
    } else {
      url = "https://" + url;
    }
  }
  CreateNewTab(url);
}

void PurrooserFrame::OnNewTab(wxCommandEvent &event) {
  CreateNewTab("https://www.duckduckgo.com");
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
