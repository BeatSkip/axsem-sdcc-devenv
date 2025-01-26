FROM mcr.microsoft.com/devcontainers/cpp:1-debian-12
ARG SDCC_VERSION=3.6.0
ARG GPUTILS_VERSION=1.4.2

# Install build dependencies

RUN apt update && \
    apt install -y \
    build-essential \
    curl \
    gputils \
    zlib1g-dev \
    bison \
    flex \
    g++ \
    libboost-dev \
    texinfo \
    wget \
    make \
    tar \
    bzip2 \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
RUN mkdir -p /usr/src/sdcc
WORKDIR /usr/src/sdcc
RUN curl -L http://downloads.sourceforge.net/project/sdcc/sdcc/3.6.0/sdcc-src-3.6.0.tar.bz2 | \
    tar xvj --strip-components=1 && \
    ./configure --prefix=/usr && \
    make && \
    make install && \
    rm -rf /usr/src/sdcc


ENV PATH="/opt/sdcc/bin:${PATH}"

# Copy platform libraries
COPY axsem-libs/ /opt/axsem
WORKDIR /workspace

