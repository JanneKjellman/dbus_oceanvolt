The color control uses the dbus to obtain the values needed
for displaying / logging etc. Simple programs can then be
created to only deal with a specific bus / interface.

The repository vecan_driver_public contains projects which
wraps some third party CAN interfaces for Windows and linux
into a single format. It is already present on the ccgx (canhw.so).
To run this code on a pc the corresponding wrapper needs to
be build and installed separately. Libevent is used to be
non-blocking. If not enabled the dbus code is blocking.

Building depens on (the ccgx sdk contains these):
 - python
 - dbus libs + headers
 - libevent libs + headers

# After cloning the following commands must be run
git submodule init
git submodule update
./velib/mk/init_build.sh

# Build on a pc
export CC=gcc
make

# CCGX build
export CC=gcc
export CROSS_COMPILE=arm-ccgx-linux-gnueabi-
make

The resulting binary is located in a directory which depends
on the target, e.g. obj/ccgx-linux-arm-gnueabi-release
