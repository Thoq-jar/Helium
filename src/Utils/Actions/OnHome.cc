#include "Actions.h"

void HeliumFrame::OnHome(wxCommandEvent& event) {
  OnCloseTab(event);
  CreateNewTab("https://purrooser-api.deno.dev/ui/index.html");
}