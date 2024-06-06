#!/bin/sh -l

echo "Running tests_entrypoint.sh..."

make tests || exit
./bin/tests || exit