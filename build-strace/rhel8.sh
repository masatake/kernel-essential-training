set -xe

sudo dnf -y install \
     --enablerepo=rhel-8-for-x86_64-baseos-rpms \
     --enablerepo=rhel-8-for-x86_64-appstream-rpms \
     diffutils autoconf automake git

sudo dnf -y \
     --enablerepo=rhel-8-for-x86_64-baseos-rpms \
     --enablerepo=rhel-8-for-x86_64-appstream-rpms \
     --enablerepo=codeready-builder-for-rhel-8-x86_64-rpms \
     --enablerepo=rhel-8-for-x86_64-baseos-source-rpms \
     --enablerepo=rhel-8-for-x86_64-appstream-source-rpms \
     --enablerepo=codeready-builder-for-rhel-8-x86_64-source-rpms \
     builddep strace

if ! [ -e rhel8-strace-kvm ]; then
    git clone --branch='kvm-snapshot#20251024-0'  --single-branch http://github.com/masatake/strace rhel8-strace-kvm
fi
(
    cd rhel8-strace-kvm
    bash ./bootstrap
    ./configure
    make
    test -x ./src/strace
    cp src/strace ../strace-rhel8
)
