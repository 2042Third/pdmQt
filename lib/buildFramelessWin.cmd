@echo off

SETLOCAL

:: Backup the original PATH
SET ORIGINAL_PATH=%PATH%

:: Modify the PATH
SET PATH=C:\VulkanSDK\1.3.231.1\Bin;C:\WINDOWS\system32;C:\WINDOWS;C:\WINDOWS\System32\OpenSSH\;C;C:\msys64\mingw64\bin;C:\Users\18604\AppData\Local\Microsoft\WindowsApps;C:\Program Files\CMake\bin\;C:\Program Files (x86)\Windows Kits\10;C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\um;%ORIGINAL_PATH%

:: Ensure you set these variables according to your setup!
set SDK_DIR_PATH=C:\Qt\6.5.2\mingw_64
set INSTALL_PATH_=framlesshelperBuild
set PATH_TO_THE_REPOSITORY=../framelesshelper

rmdir /s /q %INSTALL_PATH_% && ^
mkdir %INSTALL_PATH_% && ^
cd %INSTALL_PATH_% && ^
cmake -DCMAKE_PREFIX_PATH=%SDK_DIR_PATH%  -DCMAKE_INSTALL_PREFIX=./ -DCMAKE_BUILD_TYPE=Release -GNinja %PATH_TO_THE_REPOSITORY% && ^
cmake --build . --config Release --target all --parallel && ^
cmake --install . --config Release --strip &&^
cd ../

:: Restore the original PATH (if necessary)
SET PATH=%ORIGINAL_PATH%

ENDLOCAL