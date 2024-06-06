#!/bin/sh -l
set -e

mkdir -p ./build/.src/
make tests
./bin/tests