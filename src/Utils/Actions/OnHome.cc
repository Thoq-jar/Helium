#include "Actions.h"

void PurrooserFrame::OnHome(wxCommandEvent& event) {
  OnCloseTab(event);
  CreateNewTab("https://purrooser-api.deno.dev/ui/index.html");
}