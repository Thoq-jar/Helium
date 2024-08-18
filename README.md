# Purrooser

Purrooser is a simple, lightweight, and easy-to-use web browser.

## Installation
Linux/macOS (Bash):
```bash
cd ~
mkdir .purroosertemp
cd .purroosertemp
git clone https://github.com/Thoq-jar/Purrooser.git
cd Purrooser
chmod +x utils/build.sh
./utils/build.sh
sudo mv cmake-build-debug/Purrooser /usr/local/bin/purrooser
source ~/.bashrc
cd ~
rm -rf .purroosertemp
purrooser
```