#include "Actions.h"

void HeliumFrame::FullScreenToggle(wxCommandEvent& event) {
  if (m_notebook->GetPageCount() > 0) {
    const auto webView = dynamic_cast<wxWebView*>(
        m_notebook->GetCurrentPage()->GetChildren()[0]);
    if (webView) {
      const bool isFullScreen = IsFullScreen();
      ShowFullScreen(!isFullScreen,
                     wxFULLSCREEN_NOBORDER | wxFULLSCREEN_NOCAPTION);
      ToggleUIElements(isFullScreen);
    }
  }
}

