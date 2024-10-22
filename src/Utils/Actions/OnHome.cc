#include "Actions.h"

void HeliumFrame::OnHome(wxCommandEvent& event) {
  OnCloseTab(event);
  CreateNewTab("https://helium-api.deno.dev/ui/index.html");
}