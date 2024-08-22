# Purrooser

Purrooser is a simple, lightweight, and easy-to-use web browser.

## Prerequisites
- Meson
- Ninja
- wxWidgets

## Installation
Linux/macOS (Bash):
```bash
cd ~
mkdir .purroosertemp
cd .purroosertemp
git clone https://github.com/Thoq-jar/Purrooser.git
cd Purrooser
bazel build //:install --spawn_strategy=standalone
sudo mv buildDir/Purrooser /usr/local/bin/purrooser
bazel build //:postinstall --spawn_strategy=standalone
```
