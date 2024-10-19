#ifndef PURROOSER_H
#define PURROOSER_H

// ReSharper disable once CppUnusedIncludeDirective
#include "../Main.h"
using namespace std;
const string BANNER = R"(
+-----------------------------+
+       Welcome to Purr!      +
+      Developed by Thoq      +
+       &  Contributors       +
+-----------------------------+
)";

class Purrooser final : public wxApp {
public:
  bool OnInit() override;
};

#endif // PURROOSER_H
