#!/bin/sh -l

CURRENT_DIR=$(dirname $0)
PARENT_DIR=$(dirname $(dirname "$0"))

docker build -t meatball/linter:0.1 -f ${CURRENT_DIR}/Dockerfile.linter ${PARENT_DIR}
docker run --rm -t --name=meatball-linter --mount type=bind,source=${PARENT_DIR},target=/usr/src/app meatball/linter:0.1