#!/bin/bash

rm -rf ../bm1d_build
mkdir ../bm1d_build
cd ../bm1d_build
cmake -DCMAKE_BUILD_TYPE=Release  ../BM1D
make
echo Setup complete.
