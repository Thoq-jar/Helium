#include "../Main.hpp"

const string BANNER = R"(
+-----------------------------+
+    Welcome to Purrooser!    +
+      Developed by Thoq      +
+-----------------------------+
)";

bool Purrooser::OnInit() {
  cout << BANNER << endl;
  cout << "Starting Purrooser..." << endl;
  wxLog::SetLogLevel(wxLOG_FatalError);

  auto *frame = new PurrooserFrame("Purrooser");
  frame->Show(true);
  wxCommandEvent event;
  cout << "Purrooser started successfully!" << endl;
  return true;
}
