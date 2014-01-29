The color control (ccgx) uses the dbus to obtain the values
needed for displaying / logging etc. Simple programs can then be
created to only deal with a specific bus / interface.

The repository vecan_driver_public contains projects which
wraps some third party CAN interfaces for Windows and linux
into a single format. It is already present on the ccgx (canhw.so).
To run this code on a pc the corresponding wrapper needs to
be build and installed separately. Libevent is used to be
non-blocking. If not enabled the dbus code is blocking.

Building depens on:
 - python
 - dbus libs + headers
 - libevent libs + headers

For crosscompiling, installing the ccgx sdk is sufficient, it
contains above dependencies. For a normal compile, to run 
the project on a pc, Google will help you :).

# After cloning the following commands must be run
git submodule init
git submodule update
./velib/mk/init_build.sh

# Build on a pc, to run on a pc
export CC=gcc
make

# Build on a pc, to run on a ccgx (cross compiling)

# first setup the environment:
. /opt/bpp3/current/environment-setup-armv7a-vfp-neon-bpp3-linux-gnueabi
export CC=gcc
export CROSS_COMPILE=arm-bpp3-linux-gnueabi-
export TARGET=bpp3

# and then compile:
make

The resulting binary is located in a directory which depends
on the target, e.g. obj/ccgx-linux-arm-gnueabi-release
