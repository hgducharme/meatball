#!/bin/sh -l
set -e

IMAGE_NAME=linter
VERSION=0.1

CURRENT_DIR=$(dirname $0)
PARENT_DIR=$(dirname $(dirname "$0"))

docker build -t meatball/${IMAGE_NAME}:${VERSION} -f ${CURRENT_DIR}/Dockerfile.${IMAGE_NAME} ${PARENT_DIR}
docker run --rm -t --name=meatball-${IMAGE_NAME} meatball/${IMAGE_NAME}:${VERSION}