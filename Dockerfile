FROM mcr.microsoft.com/devcontainers/cpp:1-debian-12
ARG SDCC_VERSION=3.6.0
ARG GPUTILS_VERSION=1.4.2

# Install build dependencies
RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        ca-certificates \
        curl \
        \
        # .NET dependencies
        libc6 \
        libgcc-s1 \
        libicu74 \
        libssl3t64 \
        libstdc++6 \
        tzdata \
    && rm -rf /var/lib/apt/lists/*

# Latest download URLs and SHA512 hashes can be found in releases.json:
# https://github.com/dotnet/core/blob/main/release-notes/9.0/releases.json
ENV DOTNET_URL="https://download.visualstudio.microsoft.com/download/pr/ebc433c4-8f01-43c8-a1e2-bbe1291ba857/e073f3f679d7a4067a56e8f5d12fc0e5/dotnet-runtime-8.0.10-linux-x64.tar.gz"
ENV DOTNET_SHA512="7fb813677720d125c2337fedc6131b230daf1c1d79d5912a1ca6b5e08bf7802b412de3248d645b6483ab23f3fae837ed02a0e520e33020cfef2c888c54f474ac"

# Install .NET
RUN curl -fSL --output dotnet.tar.gz $DOTNET_URL \
    && dotnet_sha512=$DOTNET_SHA512 \
    && echo "$DOTNET_SHA512 dotnet.tar.gz" | sha512sum -c - \
    && mkdir -p /usr/share/dotnet \
    && tar -zxf dotnet.tar.gz -C /usr/share/dotnet \
    && rm dotnet.tar.gz \
    && ln -s /usr/share/dotnet/dotnet /usr/bin/dotnet


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

