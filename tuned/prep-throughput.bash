#!/bin/sh

if ! [ -d strace ];  then
    git clone --depth 1 --branch v6.1 https://github.com/strace/strace.git
fi

if ! [ -d ctags ];  then
    git clone --depth 1 --branch v6.0.0 https://github.com/universal-ctags/ctags.git
fi

sudo dnf builddep strace
sudo dnf builddep ctags
