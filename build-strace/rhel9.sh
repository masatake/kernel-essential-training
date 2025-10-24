set -xe

$SUDO dnf -y install \
     --enablerepo=rhel-9-for-x86_64-baseos-rpms \
     --enablerepo=rhel-9-for-x86_64-appstream-rpms \
     diffutils autoconf automake git

$SUDO dnf -y \
     --enablerepo=rhel-9-for-x86_64-baseos-rpms \
     --enablerepo=rhel-9-for-x86_64-appstream-rpms \
     --enablerepo=codeready-builder-for-rhel-9-x86_64-rpms \
     --enablerepo=rhel-9-for-x86_64-baseos-source-rpms \
     --enablerepo=rhel-9-for-x86_64-appstream-source-rpms \
     --enablerepo=codeready-builder-for-rhel-9-x86_64-source-rpms \
     builddep strace

if ! [ -e rhel9-strace-kvm ]; then
    git clone --branch='kvm-snapshot#20251024-0'  --single-branch http://github.com/masatake/strace rhel9-strace-kvm
fi
(
    cd rhel9-strace-kvm
    bash ./bootstrap
    ./configure
    make -j
    test -x ./src/strace
    cp src/strace ../strace-rhel9
)
