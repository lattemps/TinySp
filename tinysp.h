/*
 *       .-"""-.__
 *      /      ' o'\    tiny spread sheet - program's structure.
 *   ,-;  '.  :   _c    Oct 21 2024
 *  :_."\._ ) ::-"
 *         ""m "m
 */
#ifndef TINY_SP_H
#define TINY_SP_H
#include <stdio.h>
#include <stdbool.h>

#define __check_mem(a)  do { if (a) break; err(1, "[%s:%d]: internal error", __FILE__, __LINE__); } while (0)

enum TokenKind
{
    tkind_unknown   = -1,
    tkind_eof       = 0,
    tkind_new_line  = '\n',
    tkind_delimiter = '|',
};

struct Cell
{
    int a;
};

struct Dimensions
{
    unsigned short  rows, cols;
    unsigned short  *widths;
};

struct TinySp
{
    struct Dimensions   dims;
    struct Cell         *grid;
    char                *content;
    char                *spname;
    size_t              length;
};

#endif
