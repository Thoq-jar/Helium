import argparse
import subprocess
import os
import shutil
import venv
import platform

def create_venv(venv_dir):
    venv.create(venv_dir, with_pip=True)

def install_flake8(venv_dir):
    pip_path = get_pip_path(venv_dir)
    try:
        subprocess.run([pip_path, 'install', 'flake8'], check=True)
    except subprocess.CalledProcessError as e:
        print(f"Failed to install flake8: {e}")

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

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Run linting and other tasks.")
    parser.add_argument("--lint", action="store_true", help="Run the linter")

    args = parser.parse_args()

    if args.lint:
        venv_dir = "temp_lint"
        create_venv(venv_dir)
        install_flake8(venv_dir)
        lint(venv_dir)
        cleanup(venv_dir)
