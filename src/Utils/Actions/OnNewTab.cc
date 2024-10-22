#include "Actions.h"

void HeliumFrame::OnNewTab(wxCommandEvent& event) {
  CreateNewTab("https://helium-api.deno.dev/ui/index.html");
}
