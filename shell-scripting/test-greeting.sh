#!/bin/sh

DEFAULT_TARGET=greeting-v0.sh

usage()
{
    echo "Usage:"
    echo "   $0 [TEST-TARGET]"
}

error()
{
    echo "ERROR: $@" 1>&2
    exit 2
}

test_start()
{
    printf "test: %s..." "$1"
}

test_end()
{
    case "$1" in
	0)
	    echo ok
	    ;;
	*)
	    echo "failed $1"
	    STATUS=1
	    ;;
    esac
}

case "$1" in
    -h|--help)
	usage
	exit 1
	;;
esac

TARGET=${1:-${DEFAULT_TARGET}}
STATUS=0

if [ ! -e "$TARGET" ]; then
    error "no such file: ${TARGET}"
fi

if [ ! -x "$TARGET" ]; then
    error "not an executable: ${TARGET}"
fi

case "$TARGET" in
    */*) ;;			# do nothing
    *)
	TARGET="./$TARGET" ;;
esac


test_start en
[ $("$TARGET") = "hello" ]
test_end "$?"

test_start "-l ja"
[ $("$TARGET" -l ja) = "こんにちは" ]
test_end "$?"

test_start "-l de"
[ "$("$TARGET" -l de)" = "Guten Tag" ]
test_end "$?"

exit $STATUS
