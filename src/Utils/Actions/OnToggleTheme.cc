#include "Actions.h"

void HeliumFrame::OnToggleTheme(wxCommandEvent& event) {
  m_currentTheme =
      (m_currentTheme == Theme::LIGHT) ? Theme::DARK : Theme::LIGHT;
  ApplyTheme();
}