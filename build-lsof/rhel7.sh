set -xe

sudo yum install \
     --enablerepo=rhel-7-server-rpms \
     --enablerepo=rhel-7-server-optional-rpms \
     yum-utils git
sudo yum-builddep \
     --enablerepo=rhel-7-server-rpms \
     --enablerepo=rhel-7-server-optional-rpms \
     --enablerepo=rhel-7-server-source-rpms \
     --enablerepo=rhel-7-server-optional-source-rpms \
     lsof

if ! [ -e rhel7-lsof-kvm ]; then
    git clone --single-branch http://github.com/lsof-org/lsof rhel7-lsof-kvm
fi
(
    cd rhel7-lsof-kvm
    bash ./Configure -n linux
    make
    test -x ./lsof
    cp lsof ../lsof-rhel7
)
