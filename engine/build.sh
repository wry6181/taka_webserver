#!/bin/bash
set -e

OS="$(uname)"
mkdir -p ../bin

if [ "$OS" = "Darwin" ]; then
    echo "Building engine for macOS"
    cFilenames=$(find . -type f -name "*.c" | grep -v platform_linux | grep -v platform_win32)
    cFilenames="$cFilenames $(find . -type f -name "*.m")"
    clang $cFilenames -g -shared -fPIC -fobjc-arc -D_DEBUG -DKEXPORT -DT_PLATFORM_MAC=1 -Isrc -lm -ldl -lpthread -Wl,-install_name,@rpath/libengine.dylib -Wl,-rpath,@executable_path -framework AppKit -framework Foundation -o ../bin/libengine.dylib

elif [ "$OS" = "Linux" ]; then
    echo "Building engine for Linux"
    cFilenames=$(find . -type f -name "*.c" | grep -v platform_mac | grep -v platform_win32)
    clang $cFilenames -g -shared -fPIC -D_DEBUG -DKEXPORT -DT_PLATFORM_LINUX=1 -Isrc -lm -ldl -lpthread -o ../bin/libengine.so
fi

echo "Engine built successfully."