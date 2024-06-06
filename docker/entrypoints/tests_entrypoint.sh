#!/bin/sh -l
set -e

echo "Running tests_entrypoint.sh..."

ls -al

touch test.txt
make tests
./bin/tests