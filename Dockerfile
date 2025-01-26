FROM mcr.microsoft.com/devcontainers/cpp:1-debian-12
ARG SDCC_VERSION=3.6.0
ARG GPUTILS_VERSION=1.4.2
ENV DOTNET_SDK_VERSION=9.0.102

RUN apt update \
    && apt install -y --no-install-recommends \
        curl \
        tar \
        bzip2 \
        gzip \
        git \
        libatomic1 \
        wget \
    && rm -rf /var/lib/apt/lists/*

# Install .NET SDK
WORKDIR /tmp
RUN wget https://dot.net/v1/dotnet-install.sh -O dotnet-install.sh
RUN chmod +x ./dotnet-install.sh
RUN ./dotnet-install.sh --runtime dotnet --version 6.0.0 --install-dir /home/vscode/.dotnet
RUN chown -R vscode:vscode /home/vscode/.dotnet


RUN apt update && \
    apt install -y \
    build-essential \
    gputils \
    zlib1g-dev \
    bison \
    flex \
    g++ \
    libboost-dev \
    texinfo \
    make \
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

