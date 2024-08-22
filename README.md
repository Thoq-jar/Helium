# Purrooser

Purrooser is a simple, lightweight, and easy-to-use web browser.

## Prerequisites
- Meson
- Ninja
- wxWidgets

## Installation
Linux/macOS (Bash):
```bash
bazel build //:install --spawn_strategy=standalone
sudo mv buildDir/Purrooser /usr/local/bin/purrooser
bazel build //:post-install --spawn_strategy=standalone
```
