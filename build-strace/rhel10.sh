set -xe

$SUDO dnf -y install \
     --enablerepo=rhel-10-for-x86_64-baseos-rpms \
     --enablerepo=rhel-10-for-x86_64-appstream-rpms \
     diffutils autoconf automake git

$SUDO dnf -y \
     --enablerepo=rhel-10-for-x86_64-baseos-rpms \
     --enablerepo=rhel-10-for-x86_64-appstream-rpms \
     --enablerepo=codeready-builder-for-rhel-10-x86_64-rpms \
     --enablerepo=rhel-10-for-x86_64-baseos-source-rpms \
     --enablerepo=rhel-10-for-x86_64-appstream-source-rpms \
     --enablerepo=codeready-builder-for-rhel-10-x86_64-source-rpms \
     builddep strace

if ! [ -e rhel10-strace-kvm ]; then
    git clone --branch='kvm-snapshot#20251024-0'  --single-branch http://github.com/masatake/strace rhel10-strace-kvm
fi
(
    cd rhel10-strace-kvm
    bash ./bootstrap
    ./configure
    make -j
    test -x ./src/strace
    cp src/strace ../strace-rhel10
)
