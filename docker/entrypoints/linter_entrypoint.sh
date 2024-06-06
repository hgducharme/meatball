#!/bin/sh -l
set -e

echo "Running linter_entrypoint.sh..."

echo "**************************************************************************************************************"
echo ""
echo "cppcheck output"
echo ""
echo "**************************************************************************************************************"
cppcheck src --enable=all --suppress=missingIncludeSystem --suppress=unusedFunction --suppress=unmatchedSuppression --check-level=exhaustive

echo "**************************************************************************************************************"
echo ""
echo "clang-tidy output"
echo ""
echo "**************************************************************************************************************"

# from chatgpt:
# find . -name '*.cpp' -o -name '*.h' | xargs clang-tidy

export CPP_SRC_FILES=$(find /usr/src/app/src -name "*.*" | grep -E "(\.cpp$|\.h$|$)")
if [ -n "$CPP_SRC_FILES" ]; then clang-tidy -checks='cppcoreguidelines-*,performance-*,readibility-*,modernize-*,misc-*,clang-analyzer-*,-modernize-use-trailing-return-type' --header-filter=*.h $CPP_SRC_FILES; echo $?; fi;