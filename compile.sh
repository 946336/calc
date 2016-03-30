#!/usr/bin/env bash

rm -f solution.tmp solution.c

echo "/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * solution.c:  Build a calculator that takes normal calculator input and    *
 *              gives the answer (solution to Intermediate problem #4)       *
 *                                                                           *
 *              Alternatively, 'why we don't do things like this in C'       *
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

cat main.c operator.h operator.c ast.h ast.c tokenize.h tokenize.c \
    explist.h explist.c parse.h parse.c >> solution.tmp

mv solution.tmp solution.c

make solution
