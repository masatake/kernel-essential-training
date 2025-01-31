#!/bin/bash

usage()
{
    echo "Usage:"
    echo "  $0 [-d|--downcase] WORD..."
    echo "  $0 [-v|--version]"    
    echo "  $0 [-h|--help]"
}

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

upcase()
{
    echo "$1" |  tr a-z A-Z
}
downcase()
{
    echo "$1" |  tr A-Z a-z
}

for w in "$@"; do "$action" "$w"; done
