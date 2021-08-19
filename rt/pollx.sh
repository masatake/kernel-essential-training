##!/bin/sh

if ! [ -x pollx ]; then
    echo "no pollx command found" 1>&2
    exit 1
fi

if ! ulimit -n 1010000; then
    echo "failed in calling ulimit" 1>&2
    exit 1
fi

target_cpu=3
taskset -c "${target_cpu}" ./pollx
