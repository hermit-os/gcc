#!/bin/bash

OS_NAME=$1
OS_VERSION=$2

if [ "$OS_NAME" = "centos" ]; then

# Clean the yum cache
yum -y clean all
yum -y clean expire-cache

# First, install all the needed packages.
yum install -y wget gettext flex bison binutils gcc gcc-c++ texinfo kernel-headers rpm-build kernel-devel boost-devel cmake git tar gzip make autotools

wget http://checkinstall.izto.org/files/source/checkinstall-1.6.2.tar.gz
tar xzvf checkinstall-1.6.2.tar.gz
cd checkinstall-1.6.2
./configure
make
make install
cd ..
rm -rf checkinstall*

mkdir -p build
cd build
../configure --target=x86_64-hermit --prefix=/opt/hermit --disable-shared --disable-nls --disable-gdb --disable-libdecnumber --disable-readline --disable-sim --disable-libssp --enable-tls --disable-multilib
make
checkinstall -R -y --exclude=build --pkggroup=main --maintainer=stefan@eonerc.rwth-aachen.de --pkgsource=https://hermitcore.org --pkgname=binutils-hermit --pkgversion=2.30.51 --pkglicense=GPL2 make install

else

export DEBIAN_FRONTEND="noninteractive"

apt-get -qq update || exit 1
apt-get install -y --no-install-recommends bison checkinstall flex gawk gcc g++ libc-dev libgmp-dev libisl-dev libmpc-dev libmpfr-dev libtool texinfo || exit 1

echo "deb [trusted=yes] http://dl.bintray.com/hermitcore/ubuntu bionic main" >> /etc/apt/sources.list
apt-get update || exit 1
apt-get install -y --allow-unauthenticated binutils-hermit gcc-hermit-bootstrap newlib-hermit-rs pte-hermit-rs || exit 1

# Some GCC configure scripts (e.g. libbacktrace) check whether the C compiler can compile executables, even if it later just compiles a static library.
# However, our target C compiler cannot build an executable without a libhermit.a present.
# So we have to install a (possibly older) version of HermitCore-rs for building the C compiler that later compiles HermitCore-rs :)
apt-get install -y --allow-unauthenticated libhermit-rs

export PATH=/opt/hermit/bin:$PATH

# don't run fixincludes, this is accidentally done by dh and kinda broken
#  reference: https://gcc.gnu.org/ml/gcc/2013-04/msg00171.html
#  reference: https://ewontfix.com/12/
sed -i 's/STMP_FIXINC=stmp-fixinc/STMP_FIXINC=/g' gcc/configure

mkdir -p build
cd build
../configure --target=x86_64-hermit --prefix=/opt/hermit --with-newlib --disable-multilib --without-libatomic --with-tune=generic --enable-languages=c,c++,go,fortran,lto --disable-nls --disable-shared --disable-libssp --enable-threads=posix --disable-libgomp --enable-tls --enable-lto --disable-symvers || exit 1
make -j2 || exit 1
apt-get remove -y gcc-hermit-bootstrap
checkinstall -D -y --exclude=build --pkggroup=main --maintainer=stefan@eonerc.rwth-aachen.de --pkgsource=https://hermitcore.org --pkgname=gcc-hermit-rs --pkgversion=6.3.0 --conflicts=gcc-hermit --pkglicense=GPL2 make install || exit 1

cd ..
mkdir -p tmp
dpkg-deb -R build/gcc-hermit-rs_6.3.0-1_amd64.deb tmp
rm -f build/gcc-hermit-rs_6.3.0-1_amd64.deb

fi
