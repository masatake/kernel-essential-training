# podman run --privileged --rm -ti docker.io/library/ubuntu:noble /bin/bash

apt update
apt -y install autoconf automake make gcc git libdw-dev diffutils gawk
if ! [ -e ubuntu-noble-strace-kvm ]; then
    git clone --branch='kvm-snapshot#20251024-0'  --single-branch http://github.com/masatake/strace ubuntu-noble-strace-kvm
fi
(
    cd ubuntu-noble-strace-kvm
    bash ./bootstrap
    ./configure --disable-mpers
    make -j
    test -x ./src/strace
    cp src/strace ../strace-ubuntu-noble
)
