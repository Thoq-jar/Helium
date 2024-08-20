#include "../Main.hpp"

using namespace std;

PurrooserFrame::PurrooserFrame(const wxString &title)
  : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(WIDTH, HEIGHT)), m_currentTheme(Theme::DARK) {
  cout << "Creating main frame..." << endl;

  auto *sizer = new wxBoxSizer(wxVERTICAL);
  auto *topSizer = new wxBoxSizer(wxHORIZONTAL);

  m_backButton = new wxButton(this, wxID_ANY, "←", wxDefaultPosition, wxSize(30, 30));
  m_backButton->Bind(wxEVT_BUTTON, &PurrooserFrame::OnBack, this);
  topSizer->Add(m_backButton, 0, wxEXPAND | wxALL, 5);

  m_forwardButton = new wxButton(this, wxID_ANY, "→", wxDefaultPosition, wxSize(30, 30));
  m_forwardButton->Bind(wxEVT_BUTTON, &PurrooserFrame::OnForward, this);
  topSizer->Add(m_forwardButton, 0, wxEXPAND | wxALL, 5);

  m_homeButton = new wxButton(this, wxID_ANY, "⌂", wxDefaultPosition, wxSize(30, 30));
  m_homeButton->Bind(wxEVT_BUTTON, &PurrooserFrame::OnHome, this);
  topSizer->Add(m_homeButton, 0, wxEXPAND | wxALL, 5);

  m_reloadButton = new wxButton(this, wxID_ANY, "↻", wxDefaultPosition, wxSize(30, 30));
  m_reloadButton->Bind(wxEVT_BUTTON, &PurrooserFrame::OnReload, this);
  topSizer->Add(m_reloadButton, 0, wxEXPAND | wxALL, 5);

  m_searchCtrl = new wxSearchCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
  m_searchCtrl->Bind(wxEVT_TEXT_ENTER, &PurrooserFrame::OnSearch, this);
  topSizer->Add(m_searchCtrl, 1, wxEXPAND | wxALL, 5);

  m_closeTabButton = new wxButton(this, wxID_ANY, "⌕", wxDefaultPosition, wxSize(30, 30));
  m_closeTabButton->Bind(wxEVT_BUTTON, &PurrooserFrame::OnSearch, this);
  topSizer->Add(m_closeTabButton, 0, wxEXPAND | wxALL, 5);

  m_newTabButton = new wxButton(this, wxID_ANY, "+", wxDefaultPosition, wxSize(30, 30));
  m_newTabButton->Bind(wxEVT_BUTTON, &PurrooserFrame::OnNewTab, this);
  topSizer->Add(m_newTabButton, 0, wxEXPAND | wxALL, 5);

  m_closeTabButton = new wxButton(this, wxID_ANY, "-", wxDefaultPosition, wxSize(30, 30));
  m_closeTabButton->Bind(wxEVT_BUTTON, &PurrooserFrame::OnCloseTab, this);
  topSizer->Add(m_closeTabButton, 0, wxEXPAND | wxALL, 5);

  wxArrayString searchEngines;
  searchEngines.Add("DuckDuckGo");
  searchEngines.Add("Qwant");
  searchEngines.Add("Searx (.work)");
  searchEngines.Add("Ecosia");
  searchEngines.Add("StartPage");

  m_searchEngineChoice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, searchEngines);
  m_searchEngineChoice->SetSelection(0);
  m_searchEngineChoice->Bind(wxEVT_CHOICE, &PurrooserFrame::OnSearchEngineChange, this);
  topSizer->Add(m_searchEngineChoice, 0, wxEXPAND | wxALL, 5);

  sizer->Add(topSizer, 0, wxEXPAND);

  m_notebook = new wxNotebook(this, wxID_ANY);
  sizer->Add(m_notebook, 1, wxEXPAND | wxALL, 0);

  SetSizer(sizer);

  LoadSearchEngine();
  m_notebook->Bind(wxEVT_WEBVIEW_NAVIGATED, &PurrooserFrame::OnSiteNavigated, this);

  CreateNewTab("https://www." + DEFAULT_SEARCH + "." + SEARCH_TLD);

  auto *menuFile = new wxMenu;

  menuFile->Append(wxID_EXIT);
  m_toggleThemeItem = menuFile->Append(wxID_ANY, "Toggle Theme");
  Bind(wxEVT_MENU, &PurrooserFrame::OnToggleTheme, this, m_toggleThemeItem->GetId());

  auto *menuNavigation = new wxMenu;
  menuNavigation->Append(wxID_BACKWARD, "Back\tAlt+Left");
  menuNavigation->Append(wxID_NEW, "New Tab\tCtrl+T");
  menuNavigation->Append(wxID_CLOSE, "Close Tab\tCtrl+W");
  menuNavigation->Append(wxID_REFRESH, RELOAD_STOP_KEYBIND);
  Bind(wxEVT_MENU, &PurrooserFrame::OnBack, this, wxID_BACKWARD);
  Bind(wxEVT_MENU, &PurrooserFrame::OnForward, this, wxID_FORWARD);
  Bind(wxEVT_MENU, &PurrooserFrame::OnReload, this, wxID_REFRESH);
  Bind(wxEVT_MENU, &PurrooserFrame::OnNewTab, this, wxID_NEW);
  Bind(wxEVT_MENU, &PurrooserFrame::OnCloseTab, this, wxID_CLOSE);

  Bind(wxEVT_MENU, &PurrooserFrame::OnSaveSearchEngine, this, ID_SAVE_SEARCH_ENGINE);

  auto *menuBar = new wxMenuBar;
  menuBar->Append(menuFile, "&File");
  menuBar->Append(menuNavigation, "&Navigation");
  wxFrameBase::SetMenuBar(menuBar);
  wxFrameBase::CreateStatusBar();
  Bind(wxEVT_MENU, &PurrooserFrame::OnQuit, this, wxID_EXIT);

  ApplyTheme();
  cout << "Main frame created!" << endl;
}
