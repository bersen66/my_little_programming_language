#!/bin/bash

cmake .
make
cd build 
cd compiler 
cp COMPILER ../../
cd ../../

cd build
cd interpreter
cp INTERPRETER ../../
cd ../../

rm -r build
rm Makefile




