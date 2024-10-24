#include "Actions.h"

void HeliumFrame::ApplyTheme() {
  const wxColor backgroundColor;
  const wxColor textColor;

  if (m_currentTheme == Theme::DARK) {
    SetBackgroundColour(wxColour(30, 30, 30));
    SetForegroundColour(wxColour(255, 255, 255));
    m_backButton->SetBackgroundColour(wxColour(50, 50, 50));
    m_backButton->SetForegroundColour(wxColour(255, 255, 255));
    m_forwardButton->SetBackgroundColour(wxColour(50, 50, 50));
    m_forwardButton->SetForegroundColour(wxColour(255, 255, 255));
    m_homeButton->SetBackgroundColour(wxColour(50, 50, 50));
    m_homeButton->SetForegroundColour(wxColour(255, 255, 255));
    m_reloadButton->SetBackgroundColour(wxColour(50, 50, 50));
    m_reloadButton->SetForegroundColour(wxColour(255, 255, 255));
    m_searchButton->SetBackgroundColour(wxColour(50, 50, 50));
    m_searchButton->SetForegroundColour(wxColour(255, 255, 255));
    m_newTabButton->SetBackgroundColour(wxColour(50, 50, 50));
    m_newTabButton->SetForegroundColour(wxColour(255, 255, 255));
    m_closeTabButton->SetBackgroundColour(wxColour(50, 50, 50));
    m_closeTabButton->SetForegroundColour(wxColour(255, 255, 255));
    m_searchCtrl->SetBackgroundColour(wxColour(70, 70, 70));
    m_searchCtrl->SetForegroundColour(wxColour(255, 255, 255));
  } else if (m_currentTheme == Theme::LIGHT) {
    SetBackgroundColour(wxColour(255, 255, 255));
    SetForegroundColour(wxColour(0, 0, 0));
    m_backButton->SetBackgroundColour(wxColour(240, 240, 240));
    m_backButton->SetForegroundColour(wxColour(0, 0, 0));
    m_forwardButton->SetBackgroundColour(wxColour(240, 240, 240));
    m_forwardButton->SetForegroundColour(wxColour(0, 0, 0));
    m_homeButton->SetBackgroundColour(wxColour(240, 240, 240));
    m_homeButton->SetForegroundColour(wxColour(0, 0, 0));
    m_reloadButton->SetBackgroundColour(wxColour(240, 240, 240));
    m_reloadButton->SetForegroundColour(wxColour(0, 0, 0));
    m_searchButton->SetBackgroundColour(wxColour(240, 240, 240));
    m_searchButton->SetForegroundColour(wxColour(0, 0, 0));
    m_newTabButton->SetBackgroundColour(wxColour(240, 240, 240));
    m_newTabButton->SetForegroundColour(wxColour(0, 0, 0));
    m_closeTabButton->SetBackgroundColour(wxColour(240, 240, 240));
    m_closeTabButton->SetForegroundColour(wxColour(0, 0, 0));
    m_searchCtrl->SetBackgroundColour(wxColour(255, 255, 255));
    m_searchCtrl->SetForegroundColour(wxColour(0, 0, 0));
  } else {
    Utils::Alert("Helium (FATAL ERROR)",
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
      if (const auto panel = dynamic_cast<wxPanel*>(m_notebook->GetPage(i))) {
        panel->SetForegroundColour(textColor);
      }
    }

    Refresh();
    Update();
    Layout();
  } else {
    cout << "Invalid color detected in ApplyTheme" << endl;
  }
}