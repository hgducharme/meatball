#!/bin/sh -l

make tests || exit
./bin/tests || exit