FROM debian:12-slim

# Install build dependencies
RUN apt-get update && apt-get install -y \
    wget \
    make \
    gcc \
    && rm -rf /var/lib/apt/lists/*

# Install SDCC 3.6.0
WORKDIR /tmp
RUN wget -q https://sourceforge.net/projects/sdcc/files/sdcc/3.6.0/sdcc-3.6.0.tar.bz2 \
    && tar xf sdcc-3.6.0.tar.bz2 \
    && cd sdcc-3.6.0 \
    && ./configure --prefix=/opt/sdcc \
    && make \
    && make install \
    && cd .. \
    && rm -rf sdcc-3.6.0*

ENV PATH="/opt/sdcc/bin:${PATH}"

# Copy platform libraries
COPY platform-libs/ /opt/axsem
WORKDIR /workspace

