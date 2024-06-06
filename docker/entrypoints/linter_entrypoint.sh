#!/bin/sh -l

# cppcheck
cppcheck src --enable=all --suppress=missingIncludeSystem --suppress=unusedFunction --suppress=unmatchedSuppression --check-level=exhaustive

# TODO: clang-tidy