#include "../Main.hpp"

using namespace std;

PurrooserFrame::PurrooserFrame(const wxString &title)
  : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(WIDTH, HEIGHT)), m_currentTheme(Theme::DARK) {
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

  wxArrayString searchEngines;
  searchEngines.Add("DuckDuckGo");
  searchEngines.Add("Qwant");
  searchEngines.Add("Ecosia");
  searchEngines.Add("Searx");
  searchEngines.Add("StartPage");

  m_searchEngineChoice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, searchEngines);
  m_searchEngineChoice->SetSelection(0);
  m_searchEngineChoice->Bind(wxEVT_CHOICE, &PurrooserFrame::OnSearchEngineChange, this);
  topSizer->Add(m_searchEngineChoice, 0, wxEXPAND | wxALL, 5);

  sizer->Add(topSizer, 0, wxEXPAND);

  m_notebook = new wxNotebook(this, wxID_ANY);
  sizer->Add(m_notebook, 1, wxEXPAND | wxALL, 5);

  SetSizer(sizer);

  CreateNewTab("https://www." + DEFAULT_SEARCH + "." + SEARCH_TLD);

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
