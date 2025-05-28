#!/bin/sh

readonly LANGUAGES="en ja fr de"
readonly DEFAULT_LANGUAGE=en

error()
{
    echo "ERROR: $@" 1>&2
    exit 1
}

warning()
{
    echo "WARNING: $@" 1>&2
}

internal_error()
{
    echo "INTERNAL ERROR: $@" 1>&2
    exit 1
}

is_function_available()
{
    type "$1" > /dev/null 2>&1
}

usage()
{
    echo "Usage:"
    echo "   $0 [options]"
    echo
    echo "Options:"
    echo "  -h, --help: print usage"
    echo "  -l, --language: language used in greeting ($(list_languages))"
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

list_languages()
{
    local lang
    local list

    for lang in $LANGUAGES; do
        if [ "$lang" = "$DEFAULT_LANGUAGE" ]; then
            lang="[${lang}]"
        fi
        list="${list}, ${lang}"
    done

    list="${list#, }"
    list="${list%, *}, or $lang"
    echo "$list"
}

greet_in_en()
{
    echo "hello"
}

greet_in_ja()
{
    echo "こんにちは"
}

greet_in_fr()
{
    echo "Bonjour"
}

greet_in_de()
{
    echo "Guten Tag"
}

main()
{
    local lang="${DEFAULT_LANGUAGE}"

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
                error "unexpected argument: $1"
                ;;
        esac
    done

    if ! member "$lang" $LANGUAGES; then
        warning "unknown language: $lang"
        warning "use \"en\" instead"
        lang=en
    fi

    local func="greet_in_$lang"
    if ! is_function_available "$func"; then
        internal_error "though lang $n is declared no implementation for it"
    fi

    "$func"

    return 0
}

main "$@"
