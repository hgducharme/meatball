FROM alpine:latest as pre-build

USER root

RUN apk update && \
    apk add --no-cache \
    build-base \
    cmake \
    g++ \
    clang \
    llvm

# Install googletest
RUN cd /tmp && \
    wget https://github.com/google/googletest/archive/refs/tags/v1.13.0.tar.gz && \
    tar xf v1.13.0.tar.gz && \
    cd googletest-1.13.0 && \
    mkdir install && \
    cd install && \
    cmake .. && \
    make && \
    make install && \
    cd ../../ && \
    rm -rf googletest-1.13.0 && \
    rm -rf v1.13.0.tar.g

COPY . /workspace
WORKDIR /workspace

RUN make clean

CMD ["make" "docker-build"]

LABEL Name=build-environment