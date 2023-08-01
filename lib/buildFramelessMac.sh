#!/bin/zsh
#Build the framelesshelper project on macOS
mkdir framelesshelperBuild
cd framelesshelperBuild || exit
cmake -DCMAKE_PREFIX_PATH=/Users/mikeyang/Qt/6.5.1/macos/lib/cmake -DCMAKE_INSTALL_PREFIX=./ -DCMAKE_BUILD_TYPE=Release -GNinja ../framelesshelper
cmake --build . --config Release --target all --parallel
cmake --install . --config Release
