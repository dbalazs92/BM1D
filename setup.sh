#!/bin/bash
#
# Author: Balázs Demeter (balazsdemeter92@gmail.com)
# Version: 1.0
#
# Script for build and make Brownian movement in one dimension

mkdir bm1d_build
cd bm1d_build
cmake ../
make
echo Setup complete.
