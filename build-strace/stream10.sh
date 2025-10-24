# podman pull quay.io/centos/centos:stream10
set -xe

$SUDO dnf -y install \
     --enablerepo=baseos \
     --enablerepo=appstream \
     diffutils autoconf automake git

$SUDO dnf -y \
     --enablerepo=baseos \
     --enablerepo=appstream \
     --enablerepo=crb \
     builddep strace

if ! [ -e stream10-strace-kvm ]; then
    git clone --branch='kvm-snapshot#20251024-0'  --single-branch http://github.com/masatake/strace stream10-strace-kvm
fi
(
    cd stream10-strace-kvm
    bash ./bootstrap
    ./configure
    make -j
    test -x ./src/strace
    cp src/strace ../strace-stream10
)
