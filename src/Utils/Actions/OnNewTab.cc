#include "Actions.h"

void HeliumFrame::OnNewTab(wxCommandEvent& event) {
  CreateNewTab("https://purrooser-api.deno.dev/ui/index.html");
}
