#include "../Main.hpp"

using namespace std;

const string BANNER = R"(
+-----------------------------+
+    Welcome to Purrooser!    +
+      Developed by Thoq      +
+-----------------------------+
)";

bool Purrooser::OnInit() {
  cout << BANNER << endl;
  cout << "Starting Purrooser..." << endl;
  wxLog::AddTraceMask("all");
  wxLog::SetLogLevel(wxLOG_Trace);

  auto *frame = new PurrooserFrame("Purrooser");
  frame->Show(true);
  wxCommandEvent event;
  cout << "Purrooser started successfully!" << endl;
  return true;
}
