# A fixed environment for building the decompilation. It holds tools only: the repository and your
# disc are mounted at run time, so the image contains no game data. See "Building in a container" in
# the README.
#
#   docker build -t dw4-decomp docker/
#
# The base image is pinned by digest and the packages by an archive snapshot, so a later build gets
# the same toolchain. The compilers are fetched and checked by tools/download_tools.py.
FROM ubuntu:24.04@sha256:fe81560990fae86dc4743202b2cb4d3df98d0bcf949173cecef15ce1127ef852

ARG SNAPSHOT=20261101T000000Z
RUN apt-get update \
 && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends ca-certificates \
 && sed -i -E "s#http://(archive|security).ubuntu.com/ubuntu/#https://snapshot.ubuntu.com/ubuntu/${SNAPSHOT}/#" \
        /etc/apt/sources.list.d/ubuntu.sources \
 && dpkg --add-architecture i386 \
 && apt-get update \
 && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        binutils-mipsel-linux-gnu make git python3 libc6:i386 gcc-multilib \
 && rm -rf /var/lib/apt/lists/*

# ee-as copies with an overlapping memcpy; this makes that call safe.
COPY memmove_shim.c /usr/local/lib/
RUN gcc -m32 -O2 -fno-builtin -shared -fPIC -o /usr/local/lib/memmove_shim.so /usr/local/lib/memmove_shim.c
ENV DW4_EE_AS_SHIM=/usr/local/lib/memmove_shim.so

ENV HOME=/tmp
WORKDIR /work
