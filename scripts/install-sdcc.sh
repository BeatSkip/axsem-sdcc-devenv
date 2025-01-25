#!/bin/bash
SDCC_VERSION=3.6.0


echo "Installing SDCC ${SDCC_VERSION}..."
wget --no-verbose http://downloads.sourceforge.net/project/sdcc/sdcc/${SDCC_VERSION}/sdcc-src-${SDCC_VERSION}.tar.bz2

echo "Extracting SDCC ${SDCC_VERSION}..."
tar -xjf sdcc-src-${SDCC_VERSION}.tar.bz2

echo "Building SDCC ${SDCC_VERSION}..."
cd sdcc-${SDCC_VERSION} 
./configure 

echo "Installing SDCC ${SDCC_VERSION}..."
make -s 
make -s install 
cd .. 

echo "Cleaning up..."
rm -rf sdcc-*

echo "Done."
 