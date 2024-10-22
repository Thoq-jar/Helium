#ifndef HELIUM_H
#define HELIUM_H

// ReSharper disable once CppUnusedIncludeDirective
#include "../Main.h"
using namespace std;
const string BANNER = R"(
+-----------------------------+
+      Welcome to Helium      +
+           by Thoq           +
+       &  Contributors       +
+-----------------------------+
)";

class Helium final : public wxApp {
public:
  bool OnInit() override;
};

#endif // HELIUM_H
