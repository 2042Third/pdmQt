@echo off

rem Ensure you set these variables according to your setup!
set SDK_DIR_PATH=C:\Qt\6.4.2\msvc2019_64
set INSTALL_PATH_=framlesshelperBuild
set PATH_TO_THE_REPOSITORY=../framelesshelper

rmdir /s /q %INSTALL_PATH_% && ^
mkdir %INSTALL_PATH_% && ^
cd %INSTALL_PATH_% && ^
cmake -DCMAKE_PREFIX_PATH=%SDK_DIR_PATH% -DCMAKE_INSTALL_PREFIX=./ -DCMAKE_BUILD_TYPE=Release -GNinja %PATH_TO_THE_REPOSITORY% && ^
cmake --build . --config Release --target all --parallel && ^
cmake --install . --config Release --strip &&^
cd ../

