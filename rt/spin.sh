#!/bin/sh

if ! [ -x spin ]; then
    echo "no spin command found" 1>&2
    exit 1
fi

target_cpu=3
taskset -c "${target_cpu}" ./spin
