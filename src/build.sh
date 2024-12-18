#!/usr/bin/env bash
set -euxo pipefail

CC=gcc
CFLAGS="-Wall -Wextra -std=c99 -pedantic -ggdb"

if [[ $# == 0 ]]; then

    ${CC} ${CFLAGS} main.c -o out

elif [[ $# == 1 && $1 == "clean" ]]; then

    rm out

else
    echo "incorrect usage"
    exit 1
fi
