#!/bin/bash

source ./common.bash

action=upcase

while [ $# -gt 0 ]; do
    case "$1" in
	-h|--help)
	    usage
	    exit 0;;
	-v|--version)
	    echo 0.0
	    exit 0;;
	-d|--downcase)
	    action=downcase
	    shift;;
	-*)
	    echo "no such option: $1" 1>&2
	    exit 1;;
	*)
	    break;;
    esac
done

doit()
{
    sleep 1
    "$action" "$1"
}

for w in "$@"; do
    doit "$w" &
done

for w in "$@"; do
    pid=
    wait -np pid
    echo $pid: $?
done
