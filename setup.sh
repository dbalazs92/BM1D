#!/bin/bash

rm -rf bm1d_build
mkdir bm1d_build
cd bm1d_build
cmake ../
make
echo Setup complete.
