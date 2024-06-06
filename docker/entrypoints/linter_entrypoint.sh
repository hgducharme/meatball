#!/bin/sh -l
set -e

echo "Running linter_entrypoint.sh..."

echo "**************************************************************************************************************"
echo ""
echo "cppcheck output"
echo ""
echo "**************************************************************************************************************"
cppcheck src --enable=all --suppress=missingIncludeSystem --suppress=unusedFunction --suppress=unmatchedSuppression

echo "**************************************************************************************************************"
echo ""
echo "clang-tidy output"
echo ""
echo "**************************************************************************************************************"

export CPP_SRC_FILES=$(find ./src/ -name *.cpp)
if [ -n "$CPP_SRC_FILES" ]; then
clang-tidy --config-file=.clang-tidy --verify-config
clang-tidy --config-file=.clang-tidy $CPP_SRC_FILES --
echo $?;
fi