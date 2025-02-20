# pdmQt

PDM is an encrypted notebook app that uses pdm encryption core module.

## Building

To install pdmQt, you need to have Qt installed on your system. You can download Qt from https://www.qt.io/download.

You also need to clone the pdm-crypt-module repository from https://github.com/2042Third/pdm-crypt-module and follow the instructions there to build and install the module.

Then, you can clone this repository and open the pdmQt.pro file in Qt Creator. Build and run the project to launch the application.

### MacOS

**Updated on: Jan 23, 2025**

If you have issues building in cmake, make sure to build the cmake module of lib/cryptoSQLite and
lib/cryptoSQLite/external/securememory first.

## Usage

pdmQt allows you to encrypt and decrypt files using pdm-core-module. You can select a file to encrypt or decrypt, choose a password, and specify an output file name. The application will show you the progress and status of the encryption or decryption process.

## Credit
cryptoSQLite, SQLite wrapper for custom encryption: https://github.com/viaduck/crypto_sqlite

cryptoSQLite's secure memory: https://github.com/viaduck/secure_memory

Material design SVG icons: https://pictogrammers.com/libraries/

"date.h" date/time library: https://github.com/HowardHinnant/date

## License

pdmQt is licensed under the GPL-3 License made by Yi Yang. See LICENSE file for more details.