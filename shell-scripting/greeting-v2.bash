#!/bin/bash

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

all_greet_functions()
{
    declare -F | grep greet_in_
}

list_languages()
{
    local lang
    local list

    local _k _f func

    list=$( all_greet_functions | while read _k _f func; do
                lang="${func#greet_in_}"
                if [ "$lang" = "$DEFAULT_LANGUAGE" ]; then
                    lang="[${lang}]"
                fi
                echo -n ", ${lang}"
            done )

    list="${list#, }"

    last="${list##*, }"
    list="${list%, *}, or $last"
    echo $list
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

    local func="greet_in_$lang"
    if ! is_function_available "$func"; then
        warning "unknown language: $lang"
        warning "use \"${DEFAULT_LANGUAGE}\" instead"
        lang=${DEFAULT_LANGUAGE}
        func="greet_in_$lang"
    fi

    "$func"

    return 0
}

main "$@"
