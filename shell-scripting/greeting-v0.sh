#!/bin/sh

error()
{
    echo "ERROR: $@" 1>&2
    exit 1
}

warning()
{
    echo "WARNING: $@" 1>&2
}

usage()
{
    echo "Usage:"
    echo "   $0 [options]"
    echo
    echo "Options:"
    echo "  -h, --help: print usage"
    echo "  -l, --language: language used in greeting (ja, fr, or [en])"
    echo
    echo "Examples:"
    echo "   $0 --language ja"
}

member()
{
    local elt=$1
    shift
    local x

    for x in "$@"; do
        if [ "$x" = "$elt" ]; then
            return 0
        fi
    done
    return 1
}

main()
{
    local lang=en

    while [ $# -gt 0 ]; do
        case "$1" in
            -h|--help)
                usage
                exit 0
                ;;
            --language|-l)
                shift
                lang=$1
                shift
                ;;
            --language=*)
                lang=${1#--language=}
                shift
                ;;
            -*)
                error "unknown option: $1"
                ;;
            *)
                error "unexpecged argument: $1"
                ;;
        esac
    done

    if ! member "$lang" en ja fr; then
        warning "unknown language: $lang"
        warning "use \"en\" instead"
        lang=en
    fi

    case "$lang" in
        en)
            echo "hello"
            ;;
        ja)
            echo "こんにちは"
            ;;
        fr)
            echo "Bonjour"
            ;;
    esac

    return 0
}

main "$@"
