### I AM AWARE THIS IS NOT STARLARK,
### I HAVE PLANS TO CONVERT THIS TO STARLARK IN THE FUTURE

# Windows crosscompile
if [ -d "buildWindows" ]; then
    rm -rf buildWindows
fi

meson setup buildWindows --cross-file windows_cross.txt
cd buildWindows || exit
ninja
cd ..