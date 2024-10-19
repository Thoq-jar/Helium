#include "Actions.h"

void PurrooserFrame::OnSiteError(wxWebViewEvent& event) {
  if (!m_errorPageOpened) {
    m_errorPageOpened = true;
    return;
  }
}