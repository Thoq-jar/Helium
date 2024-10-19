#include "Actions.h"

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
