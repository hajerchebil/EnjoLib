#!/bin/bash

MAKE=make
GEN="CodeBlocks - Unix Makefiles"
BUILD_DIR="build/gcc"





mkdir -p $BUILD_DIR && cd $BUILD_DIR

cmake -G "${GEN}" ../.. \
 \
 \
-DUSE_STATIC="OFF" \
-DUSE_UNITY="ON" \
&& ${MAKE} -j `nproc` || ${MAKE} && ${MAKE} -j `nproc` install
ctest --verbose -R EnjoLibTest
ctest --output-on-failure -j `nproc`

