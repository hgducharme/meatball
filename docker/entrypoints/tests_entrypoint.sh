#!/bin/sh -l
set -e

echo "Running tests_entrypoint.sh..."

make tests
./bin/tests