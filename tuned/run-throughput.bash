#!/bin/bash
target=ctags
#
# run-throughput.bash <profile> <cpus> <count>
#
profile=${1?no profile given}
cpus=${2:-4}
count=${3:-2}

if ! [ -d ${target} ]; then
    echo "no ${target} source code"
    exit 1
fi

d=${target}-"$profile"
rm -rf "$d"
cp -r ${target} "$d"

log=${target}-${profile}-${cpus}.time

sudo tuned-adm profile "$profile"
sudo -s eval 'echo 3 > /proc/sys/vm/drop_caches'


CMDLINE=

#
# target: strace
#
pre_strace()
{
    :
}

post_strace()
{
    :
}
cmdline_strace()
{
    CMDLINE+='./bootstrap > /dev/null 2>&1;'
    CMDLINE+='./configure > /dev/null 2>&1;'
    CMDLINE+='make -j '"$cpus"' > /dev/null 2>&1;'
    CMDLINE+='ls -l src/strace;'
    CMDLINE+='free -h;'
    CMDLINE+='make  -j '"$cpus"' maintainer-clean > /dev/null 2>&1;'
}

#
# target: ctags
#
prep_ctags()
{
    ./autogen.sh > /dev/null 2>&1
    ./configure > /dev/null 2>&1
}

cmdline_ctags()
{
    CMDLINE+='make -j '"$cpus"' > /dev/null 2>&1;'
}

post_ctags()
{
    ls -l ctags
    make clean > /dev/null 2>&1
}

cmdline_$target
(
    cd "$d"
    free -h

    prep_$target
    rm -f ../"$log"
    echo $log
    for (( i = 0; i < count; i++ )); do
	/bin/time -o ../"$log" -a bash -c "$CMDLINE"
	post_$target
    done
    cat ../"$log"
)
