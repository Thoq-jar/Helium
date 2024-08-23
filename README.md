# Purrooser

Purrooser is a simple, lightweight, and easy-to-use web browser.

## Prerequisites
- Meson (or Bazelisk a.k.a. Bazel)
- Ninja (Only for Meson)
- wxWidgets (Required)

## Installation
Linux/macOS (Bash):
```bash
cd ~
mkdir .purroosertemp
cd .purroosertemp
git clone https://github.com/Thoq-jar/Purrooser.git
cd Purrooser
bazel build //:PurrooserBuild --spawn_strategy=standalone
sudo mv bazel-Purrooser/buildDir/Purrooser /usr/local/bin/purrooser
cd ~
rm -rf .purroosertemp
purrooser
```
