#include "../Main.h"

using namespace std;

#ifdef defined__WXGTK__
wxSize buttonSize(35, 35);
#elif defined(__WXOSX__)
wxSize buttonSize(30, 30);
#elif __WXMSW__
wxSize buttonSize(35, 35);
#else
wxSize buttonSize(35, 35);
#endif

PurrooserFrame::PurrooserFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition,
              wxSize(WIDTH, HEIGHT)),
      m_currentTheme(Theme::DARK) {
  cout << "Creating main frame..." << endl;

  auto* sizer = new wxBoxSizer(wxVERTICAL);
  auto* topSizer = new wxBoxSizer(wxHORIZONTAL);

  m_backButton = new wxButton(this, ID_BACK_BUTTON, wxString::FromUTF8("←"),
                              wxDefaultPosition, buttonSize);
  m_forwardButton =
      new wxButton(this, ID_FORWARD_BUTTON, wxString::FromUTF8("→"),
                   wxDefaultPosition, buttonSize);
  m_homeButton = new wxButton(this, ID_HOME_BUTTON, wxString::FromUTF8("⌂"),
                              wxDefaultPosition, buttonSize);
  m_reloadButton =
      new wxButton(this, ID_RELOAD_BUTTON, wxString::FromUTF8(RELOAD_ICON),
                   wxDefaultPosition, buttonSize);
  m_searchButton = new wxButton(this, ID_SEARCH_BUTTON, wxString::FromUTF8("⌕"),
                                wxDefaultPosition, buttonSize);
  m_newTabButton =
      new wxButton(this, ID_NEW_TAB_BUTTON, wxString::FromUTF8("+"),
                   wxDefaultPosition, buttonSize);
  m_closeTabButton =
      new wxButton(this, ID_CLOSE_TAB_BUTTON, wxString::FromUTF8("-"),
                   wxDefaultPosition, buttonSize);
  m_searchCtrl =
      new wxSearchCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition,
                       wxDefaultSize, wxTE_PROCESS_ENTER);

  m_backButton->Bind(wxEVT_BUTTON, &PurrooserFrame::OnBack, this);
  m_forwardButton->Bind(wxEVT_BUTTON, &PurrooserFrame::OnForward, this);
  m_homeButton->Bind(wxEVT_BUTTON, &PurrooserFrame::OnHome, this);
  m_reloadButton->Bind(wxEVT_BUTTON, &PurrooserFrame::OnReload, this);
  m_searchButton->Bind(wxEVT_BUTTON, &PurrooserFrame::OnSearch, this);
  m_newTabButton->Bind(wxEVT_BUTTON, &PurrooserFrame::OnNewTab, this);
  m_closeTabButton->Bind(wxEVT_BUTTON, &PurrooserFrame::OnCloseTab, this);
  m_searchCtrl->Bind(wxEVT_TEXT_ENTER, &PurrooserFrame::OnSearch, this);

  topSizer->Add(m_backButton, 0, wxEXPAND | wxALL, 5);
  topSizer->Add(m_forwardButton, 0, wxEXPAND | wxALL, 5);
  topSizer->Add(m_homeButton, 0, wxEXPAND | wxALL, 5);
  topSizer->Add(m_reloadButton, 0, wxEXPAND | wxALL, 5);
  topSizer->Add(m_searchCtrl, 1, wxEXPAND | wxALL, 5);
  topSizer->Add(m_searchButton, 0, wxEXPAND | wxALL, 5);
  topSizer->Add(m_newTabButton, 0, wxEXPAND | wxALL, 5);
  topSizer->Add(m_closeTabButton, 0, wxEXPAND | wxALL, 5);

  sizer->Add(topSizer, 0, wxEXPAND);

  m_notebook = new wxNotebook(this, wxID_ANY);
  sizer->Add(m_notebook, 1, wxEXPAND | wxALL, 0);

  SetSizer(sizer);

  m_notebook->Bind(wxEVT_WEBVIEW_NAVIGATED, &PurrooserFrame::OnSiteNavigated,
                   this);

  CreateNewTab("https://purrooser-api.deno.dev/ui/index.html");

  auto* menuFile = new wxMenu;
  menuFile->Append(wxID_EXIT, QUIT_KEYBIND);
  m_toggleThemeItem = menuFile->Append(ID_THEME_TOGGLE, "Toggle Theme");
  Bind(wxEVT_MENU, &PurrooserFrame::OnToggleTheme, this,
       m_toggleThemeItem->GetId());

  auto* menuNavigation = new wxMenu;
  menuNavigation->Append(wxID_FORWARD, "Forward\tAlt+Right");
  menuNavigation->Append(wxID_BACKWARD, "Back\tAlt+Left");
  menuNavigation->Append(wxID_NEW, "New Tab\tCtrl+T");
  menuNavigation->Append(wxID_CLOSE, "Close Tab\tCtrl+W");
  menuNavigation->Append(wxID_REFRESH, RELOAD_STOP_KEYBIND);
  menuNavigation->Append(ID_FULLSCREEN_TOGGLE, FULLSCREEN_KEYBIND);

  Bind(wxEVT_MENU, &PurrooserFrame::OnForward, this, wxID_FORWARD);
  Bind(wxEVT_MENU, &PurrooserFrame::OnBack, this, wxID_BACKWARD);
  Bind(wxEVT_MENU, &PurrooserFrame::OnReload, this, wxID_REFRESH);
  Bind(wxEVT_MENU, &PurrooserFrame::OnNewTab, this, wxID_NEW);
  Bind(wxEVT_MENU, &PurrooserFrame::OnCloseTab, this, wxID_CLOSE);
  Bind(wxEVT_MENU, &PurrooserFrame::FullScreenToggle, this,
       ID_FULLSCREEN_TOGGLE);

  auto* menuBar = new wxMenuBar;
  menuBar->Append(menuFile, "&File");
  menuBar->Append(menuNavigation, "&Navigation");
  wxFrameBase::SetMenuBar(menuBar);
  wxFrameBase::CreateStatusBar();
  Bind(wxEVT_MENU, &PurrooserFrame::OnQuit, this, wxID_EXIT);

  ApplyTheme();
  cout << "Main frame created!" << endl;
}
