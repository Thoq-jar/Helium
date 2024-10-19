#include "Actions.h"

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