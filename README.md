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
bazel build //:Install
bazel build //:Postinstall
sudo mv buildDir/purrooser /usr/local/bin/purrooser
purrooser
```
