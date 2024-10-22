#include "Actions.h"

void HeliumFrame::OnSiteError(wxWebViewEvent& event) {
  if (!m_errorPageOpened) {
    m_errorPageOpened = true;
    return;
  }
}