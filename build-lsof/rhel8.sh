set -xe

sudo dnf install \
     --enablerepo=rhel-8-for-x86_64-baseos-rpms \
     --enablerepo=rhel-8-for-x86_64-appstream-rpms \
     git

sudo dnf \
     --enablerepo=rhel-8-for-x86_64-baseos-rpms \
     --enablerepo=rhel-8-for-x86_64-appstream-rpms \
     --enablerepo=codeready-builder-for-rhel-8-x86_64-rpms \
     --enablerepo=rhel-8-for-x86_64-baseos-source-rpms \
     --enablerepo=rhel-8-for-x86_64-appstream-source-rpms \
     --enablerepo=codeready-builder-for-rhel-8-x86_64-source-rpms \
     builddep lsof

if ! [ -e rhel8-lsof-kvm ]; then
    git clone --single-branch http://github.com/lsof-org/lsof rhel8-lsof-kvm
fi
(
    cd rhel8-lsof-kvm
    bash ./Configure -n linux
    make
    test -x ./lsof
    cp lsof ../lsof-rhel8
)
