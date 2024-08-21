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
chmod +x build-utils/native_build.sh
sh build-utils/native_build.sh
sudo mv buildDir/Purrooser /usr/local/bin/purrooser
cd ~
rm -rf .purroosertemp
purrooser
```
