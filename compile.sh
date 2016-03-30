#!/usr/bin/env bash

rm -f solution.tmp solution.c

echo "/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * solution.c:  Build a calculator that takes normal calculator input and    *
 *              gives the answer (solution to Intermediate problem #4)       *
 *                                                                           *
 *              Alternatively, 'why we don't like doing things like this     *
 *              in C'                                                        *
 *                                                                           *
 * Author:      946336 (https://www.github.com/946336)                       *
 *                                                                           *
 * Compiling:   gcc -Wall -Wextra -pedantic -std=c99 solution.c -o calc -lm  *
 *                                                                           *
 * Running:     ./calc                                                       *
 *                                                                           *
 * Notes:       - This calculator reads from standard input and terminates   *
 *                on EOF (CTRL+D if not piping or redirecting)               *
 *              - This file is a conglomeration of multiple source files.    *
 *                It's not normally this ugly and convoluted                 *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

" >> solution.tmp

cat \
    operator.h \
    ast.h \
    tokenize.h \
    explist.h \
    parse.h \
    main.c \
    operator.c \
    ast.c \
    tokenize.c \
    explist.c \
    parse.c \
    >> solution.tmp

mv solution.tmp solution.c

sed -i 's/#include ".*/\/\/\0/g' solution.c

make solution
