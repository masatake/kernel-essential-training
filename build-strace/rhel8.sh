set -xe

sudo dnf install \
     --enablerepo=rhel-8-for-x86_64-baseos-rpms \
     --enablerepo=rhel-8-for-x86_64-appstream-rpms \
     autoconf automake git

sudo dnf \
     --enablerepo=rhel-8-for-x86_64-baseos-rpms \
     --enablerepo=rhel-8-for-x86_64-appstream-rpms \
     --enablerepo=codeready-builder-for-rhel-8-x86_64-rpms \
     --enablerepo=rhel-8-for-x86_64-baseos-source-rpms \
     --enablerepo=rhel-8-for-x86_64-appstream-source-rpms \
     --enablerepo=codeready-builder-for-rhel-8-x86_64-source-rpms \
     builddep strace

if ! [ -e rhel8-strace-kvm ]; then
    git clone --branch=kvm-snapshot'#20250910' --single-branch http://github.com/masatake/strace rhel8-strace-kvm
fi
(
    cd rhel8-strace-kvm
    bash ./bootstrap
    ./configure
    make
    test -x ./strace
    cp strace ../strace-rhel8
)
