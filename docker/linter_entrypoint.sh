#!/bin/sh -l

echo Hello $1
time=$(date)
echo time=$time >> $GITHUB_OUTPUT

# cppcheck
cppcheck src --enable=all --suppress=missingIncludeSystem --suppress=unusedFunction --suppress=unmatchedSuppression --check-level=exhaustive

# TODO: clang-tidy