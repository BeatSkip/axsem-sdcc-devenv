FROM debian:12-slim
ARG SDCC_VERSION=3.6.0
ARG GPUTILS_VERSION=1.4.2

# Install build dependencies

RUN apt-get update && \
    apt-get install -y \
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
WORKDIR /build

COPY scripts/install-sdcc.sh /opt/src/scripts/sdcc.sh
RUN /opt/src/scripts/sdcc.sh


ENV PATH="/opt/sdcc/bin:${PATH}"

# Copy platform libraries
COPY axsem-libs/ /opt/axsem
WORKDIR /workspace

