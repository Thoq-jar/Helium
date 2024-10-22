#include "Helium.h"

bool Helium::OnInit() {
  cout << BANNER << endl;
  cout << "Starting" << space << name << space << version << space << type << "..." << endl;
  wxLog::SetLogLevel(wxLOG_FatalError);

  auto *frame = new HeliumFrame("Helium");

  wxIcon icon;
#ifdef __WXMSW__
  icon.LoadFile("assets/icon.ico", wxBITMAP_TYPE_ICO);
#elif defined(__WXGTK__)
  icon.LoadFile("assets/icon.png", wxBITMAP_TYPE_PNG);
#elif defined(__WXOSX__)
  icon.LoadFile("assets/icon.icns", wxBITMAP_TYPE_ANY);
#else
  icon.LoadFile("assets/icon.png", wxBITMAP_TYPE_PNG);
#endif
  frame->SetIcon(icon);

  ActionsInit();

  frame->Show(true);
  wxCommandEvent event;
  cout << name << space << "started successfully!" << endl;
  return true;
}