#!/bin/sh -l

echo "Running build_entrypoint.sh..."

make build $@ || exit