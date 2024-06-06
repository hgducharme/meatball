#!/bin/sh -l

# TODO: can not mkdir -p ./build while inside Docker container. What's up with permissions?

CURRENT_DIR=$(dirname $0)
PARENT_DIR=$(dirname $(dirname "$0"))

docker build -t meatball/tests:0.1 -f ${CURRENT_DIR}/Dockerfile.tests ${PARENT_DIR}
docker run --rm -t --name=meatball-tests --mount type=bind,source=${PARENT_DIR},target=/usr/src/app meatball/tests:0.1