#!/bin/bash

CC="gcc"
CFLAGS="-pipe -O3 -Wall -Wextra -Wpedantic -Werror -std=c89 -ansi"
LFLAGS=""

${CC} ${CFLAGS} yoyo.c ${LFLAGS} -o yoyo.bin
${CC} ${CFLAGS} yoyo_asm.c ${LFLAGS} -o yoyo_asm.bin

echo "done."

