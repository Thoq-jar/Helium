# Tooling.py
# Tools for Purrooser
# MIT License

import argparse
import subprocess
import os
import shutil
import venv
import platform

def create_venv(venv_dir):
    venv.create(venv_dir, with_pip=True)

def install_package(venv_dir, package):
    pip_path = get_pip_path(venv_dir)
    try:
        subprocess.run([pip_path, 'install', package], check=True)
    except subprocess.CalledProcessError as e:
        print(f"Failed to install {package}: {e}")

def lint(venv_dir):
    flake8_path = get_flake8_path(venv_dir)
    core_directory = "core"

    try:
        subprocess.run(
            [flake8_path, core_directory, "--count", "--select=E9,F63,F7,F82", "--show-source", "--statistics"],
            check=True
        )

        subprocess.run(
            [flake8_path, core_directory, "--count", "--exit-zero", "--max-complexity=10", "--max-line-length=127", "--statistics"],
            check=True
        )
    except subprocess.CalledProcessError as e:
        print(f"Linting failed with error: {e}")

def gather_files(directory):
    files = []
    for root, _, filenames in os.walk(directory):
        for filename in filenames:
            files.append(os.path.join(root, filename))
    return files

def run_pyinstaller(venv_dir):
    pyinstaller_path = get_pyinstaller_path(venv_dir)
    core_files = gather_files('core')
    ui_files = gather_files('ui')

    command = [
        pyinstaller_path,
        '--onefile',
        '--windowed',
        '--icon=core/assets/icon.ico',
        'core/main.py'
    ] + core_files + ui_files

    try:
        subprocess.run(command, check=True)
    except subprocess.CalledProcessError as e:
        print(f"Failed to run PyInstaller: {e}")

def cleanup(venv_dir):
    shutil.rmtree(venv_dir)

def get_pip_path(venv_dir):
    if platform.system() == "Windows":
        return os.path.join(venv_dir, 'Scripts', 'pip')
    else:
        return os.path.join(venv_dir, 'bin', 'pip')

def get_flake8_path(venv_dir):
    if platform.system() == "Windows":
        return os.path.join(venv_dir, 'Scripts', 'flake8')
    else:
        return os.path.join(venv_dir, 'bin', 'flake8')

def get_pyinstaller_path(venv_dir):
    if platform.system() == "Windows":
        return os.path.join(venv_dir, 'Scripts', 'pyinstaller')
    else:
        return os.path.join(venv_dir, 'bin', 'pyinstaller')

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Run linting and other tasks.")
    parser.add_argument("--lint", action="store_true", help="Run the linter")
    parser.add_argument("--build", action="store_true", help="Build the application with PyInstaller")

    args = parser.parse_args()

    if args.lint:
        venv_dir = "temp_lint"
        create_venv(venv_dir)
        install_package(venv_dir, 'flake8')
        lint(venv_dir)
        cleanup(venv_dir)

    if args.build:
        venv_dir = "temp_build"
        create_venv(venv_dir)
        install_package(venv_dir, 'pyinstaller')
        run_pyinstaller(venv_dir)
        cleanup(venv_dir)
