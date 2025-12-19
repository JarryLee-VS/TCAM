#!/bin/bash
ROOTPATH=`pwd`
TOOLCHAIN="${ROOTPATH}/arm-buildroot-linux-gnueabihf_sdk-buildroot/bin"
SYSROOT="${ROOTPATH}/arm-buildroot-linux-gnueabihf_sdk-buildroot/arm-buildroot-linux-gnueabihf/sysroot"

rm -rf build
mkdir build
cd build
cmake $ROOTPATH/TCAM -DROOTPATH=$ROOTPATH -DCMAKE_TOOLCHAIN_FILE=$ROOTPATH/TCAM/toolchain.cmake
make -j`nproc`

# compile BSOD

# Get all compiled files
if [ ! -d $ROOTPATH/UDISK ]; then
    mkdir $ROOTPATH/UDISK
fi
cp $ROOTPATH/build/TCAM $ROOTPATH/UDISK
