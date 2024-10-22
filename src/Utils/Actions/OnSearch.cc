#include "Actions.h"

void HeliumFrame::OnSearch(wxCommandEvent& event) {
  wxString url = m_searchCtrl->GetValue();
  url.Replace(" ", "+");

  const std::regex tldRegex(R"((\.[a-z]{2,})$)");

  if (url.StartsWith("purr://")) {
    const wxString command = url.AfterFirst('/');
    if (command == "/newtab") {
      CreateNewTab("https://purrooser-api.deno.dev/ui/index.html");
      return;
    }
    if (command == "/error") {
      CreateNewTab("https://purrooser-api.deno.dev/ui/error.html");
      return;
    }
    if (command == "/about") {
      CreateNewTab("https://purrooser-api.deno.dev/ui/about.html");
      return;
    }
    if (command == "/kitty") {
      CreateNewTab("https://purrooser-api.deno.dev/ui/kitty.html");
      return;
    }
    if (command == "/settings") {
      CreateNewTab("https://purrooser-api.deno.dev/ui/settings.html");
      return;
    }
    if (command == "/weather") {
      CreateNewTab("https://purrooser-api.deno.dev/ui/weather.html");
      return;
    }
    Utils::Alert("Purr", "Unknown purr:// URL!");
    return;
  }
  if (!url.StartsWith("http://") && !url.StartsWith("https://")) {
    if (!std::regex_search(url.ToStdString(), tldRegex)) {
      url = "https://google.com/search?q=" + url;
    } else {
      url = "https://" + url;
    }
  }

  if (m_notebook->GetPageCount() > 0) {
    const auto webView = dynamic_cast<wxWebView*>(
        m_notebook->GetCurrentPage()->GetChildren()[0]);
    if (webView) {
      webView->LoadURL(url);
    }
  } else {
    CreateNewTab(url);
  }
}
