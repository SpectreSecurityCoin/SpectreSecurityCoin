#!/bin/sh

# Let's compile compile SpectreSecurityCoin GUI wallet
chmod 775 * -R
chmod 755 src/leveldb/build_detect_platform
chmod 755 src/secp256k1/autogen.sh
cd src/leveldb
make libleveldb.a libmemenv.a
cd ../..
qmake SpectreSecurityCoin.pro
make
