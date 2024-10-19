#include "Actions.h"

void PurrooserFrame::OnNewTab(wxCommandEvent& event) {
  CreateNewTab("https://purrooser-api.deno.dev/ui/index.html");
}
