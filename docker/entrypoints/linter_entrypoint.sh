#!/bin/sh -l

echo "Running linter_entrypoint.sh..."

echo "**************************************************************************************************************"
echo ""
echo "cppcheck output"
echo ""
echo "**************************************************************************************************************"
cppcheck src --enable=all --suppress=missingIncludeSystem --suppress=unusedFunction --suppress=unmatchedSuppression --std=c++17 --check-level=exhaustive --error-exitcode=1 || exit

echo "**************************************************************************************************************"
echo ""
echo "clang-tidy output"
echo ""
echo "**************************************************************************************************************"

export CPP_SOURCE_FILES=$(find ./src/ -name *.cpp)
if [ -n "$CPP_SOURCE_FILES" ]; then
clang-tidy --config-file=.clang-tidy --verify-config || exit
clang-tidy --config-file=.clang-tidy -p './build' $CPP_SOURCE_FILES || exit
fi