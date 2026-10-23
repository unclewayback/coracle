#!/bin/sh
# Host-build Coracle with the cos3v3 engine: the ceiling test for heavy patches.
set -e
cd "$(dirname "$0")/.."
H=patches/cos3v3/c
mkdir -p build/host

for f in $H/*.c;   do cc  -O2 -Wall -Wno-unused-function -Wno-stringop-truncation -I$H -c $f -o build/host/hv_$(basename $f .c).o;  done
for f in $H/*.cpp; do c++ -O2 -I$H -c $f -o build/host/hv_$(basename $f .cpp).o;                                                     done

cc -O2 -Wall -Wno-unused-function -DDINGHY_HOST -DAPP_VER='"dev"' \
   -Ifirmware/src -Ifirmware/gen -I$H \
   -c firmware/src/dinghy.c -o build/host/app.o

c++ -o build/host/coracle build/host/*.o -lm
build/host/coracle build/host/coracle
