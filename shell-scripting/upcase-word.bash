#!/bin/bash

usage()
{
    echo "Usage:"
    echo "  $0 [-d|--downcase] WORD"
    echo "  $0 [-v|--version]"    
    echo "  $0 [-h|--help]"
}

action=upcase
word=

while [ $# -gt 0 ]; do
    if [ "$1" = -h ] || [ "$1" = --help ]; then
	usage
	exit 0
    elif [ "$1" = -v ] || [ "$1" = --version ]; then
	echo 0.0
	exit 0
    elif [ "$1" = "-d" ] || [ "$1" = --downcase ]; then
	action=downcase
	shift
    elif echo "$1" | grep -q -e "^-.*"; then
	echo "no such option: $1" 1>&2
	exit 1
    else
	break
    fi
done

word=$1
shift

if [ -z "$word" ]; then
   echo "no word given"
fi

if [ "$action" = upcase ]; then
    echo "$word" |  tr a-z A-Z
else
    echo "$word" |  tr A-Z a-z 
fi
