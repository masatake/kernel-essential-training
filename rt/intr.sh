#!/bin/sh

if ! [ -x intr ]; then
    echo "no intr command found" 1>&2
    exit 1
fi

target_cpu=3
taskset -c "${target_cpu}" ./intr
