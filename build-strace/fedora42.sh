# podman run --privileged --rm -ti fedora:42 /bin/bash
set -xe

dnf -y install diffutils git autoconf automake gcc make gawk
dnf -y builddep strace
if ! [ -e fedora42-strace-kvm ]; then
    git clone --branch='kvm-snapshot#20251024-0'  --single-branch http://github.com/masatake/strace fedora42-strace-kvm
fi
(
    cd fedora42-strace-kvm
    bash ./bootstrap
    ./configure
    make -j
    test -x ./src/strace
    cp src/strace ../strace-fedora42
)
