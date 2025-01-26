FROM mcr.microsoft.com/devcontainers/cpp:1-debian-12
ARG SDCC_VERSION=3.6.0
ARG GPUTILS_VERSION=1.4.2
ENV \
    # Do not generate certificate
    DOTNET_GENERATE_ASPNET_CERTIFICATE=false \
    # Do not show first run text
    DOTNET_NOLOGO=true \
    # SDK version
    DOTNET_SDK_VERSION=9.0.102 \
    # Enable correct mode for dotnet watch (only mode supported in a container)
    DOTNET_USE_POLLING_FILE_WATCHER=true

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
RUN curl -fSL --output dotnet.tar.gz https://builds.dotnet.microsoft.com/dotnet/Sdk/$DOTNET_SDK_VERSION/dotnet-sdk-$DOTNET_SDK_VERSION-linux-x64.tar.gz \
    && dotnet_sha512='f093507ef635c3f8e572bf7b6ea7e144b85ccf6b7c6f914d3f182f782200a6088728663df5c9abe0638c9bd273fde3769ec824a6516f5fce734c4a4664ce3099' \
    && echo "$dotnet_sha512  dotnet.tar.gz" | sha512sum -c - \
    && mkdir -p /usr/share/dotnet \
    && tar -oxzf dotnet.tar.gz -C /usr/share/dotnet ./packs ./sdk ./sdk-manifests ./templates ./LICENSE.txt ./ThirdPartyNotices.txt \
    && rm dotnet.tar.gz \
    # Trigger first run experience by running arbitrary cmd
    && dotnet help


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

