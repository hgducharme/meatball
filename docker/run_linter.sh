#!/bin/sh -l
set -e

IMAGE_NAME=linter

CURRENT_DIR=$(dirname $0)
PARENT_DIR=$(dirname $(dirname "$0"))

docker build -t meatball/${IMAGE_NAME}:0.1 -f ${CURRENT_DIR}/Dockerfile.${IMAGE_NAME} ${PARENT_DIR}
docker run --rm -t --name=meatball-${IMAGE_NAME} --mount type=bind,source=${PARENT_DIR},target=/usr/src/app meatball/${IMAGE_NAME}:0.1