set -xe

sudo yum install \
     --enablerepo=rhel-7-server-rpms \
     --enablerepo=rhel-7-server-optional-rpms \
     yum-utils autoconf automake git
sudo yum-builddep \
     --enablerepo=rhel-7-server-rpms \
     --enablerepo=rhel-7-server-optional-rpms \
     --enablerepo=rhel-7-server-source-rpms \
     --enablerepo=rhel-7-server-optional-source-rpms \
     strace

if ! [ -e rhel7-strace-kvm ]; then
    git clone --branch=kvm-snapshot --single-branch http://github.com/masatake/strace rhel7-strace-kvm
fi
(
    cd rhel7-strace-kvm
    bash ./bootstrap
    ./configure
    make
    test -x ./strace
    cp strace ../strace-rhel7
)
