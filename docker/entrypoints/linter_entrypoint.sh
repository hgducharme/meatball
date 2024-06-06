#!/bin/sh -l

# cppcheck
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

export CPP_SRC_FILES=$(find /usr/src/app/src -name "*.*" | grep -E "(\.cpp$|\.h$|$)")
if [ -n "$CPP_SRC_FILES" ]; then clang-tidy -checks='cppcoreguidelines-*,performance-*,readibility-*,modernize-*,misc-*,clang-analyzer-*,-modernize-use-trailing-return-type' --header-filter=*.h --export-fixes=clang-tidy-fixes $CPP_SRC_FILES; echo $?; fi;


# find . -name '*.cpp' -o -name '*.h' | xargs clang-tidy