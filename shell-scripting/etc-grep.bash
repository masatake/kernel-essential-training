#!/bin/bash

DIR=/etc
PATTERN=$1

if [ -z "$PATTERN" ]; then
    echo "no pattern given" 1>&2
    exit 2
fi

if grep -q -s -r "$PATTERN" /etc; then
    echo FOUND
    exit 0
else
    echo NOT FOUND
    exit 1
fi


