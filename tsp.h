/*
 *       .-"""-.__
 *      /      ' o'\    tiny spread sheet - includes.
 *   ,-;  '.  :   _c    Oct 22 2024
 *  :_."\._ ) ::-"
 *         ""m "m
 */
#ifndef TSP_TSP_H
#define TSP_TSP_H
#include <err.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define __check_ptr(a)  do { if (a) break; err(EXIT_FAILURE, "fatal internal error %s %d", __FILE__, __LINE__); } while (0)

enum TokenType
{
    tokens_eof          = 0,
    tokens_newline      = 1,
    tokens_delimiter    = 2,
};

enum CellType
{
    cells_empty     = 0,
    cells_number    = 1,
    cells_string    = 2,
    cells_date      = 3,
    cells_boolean   = 4,
    cells_error     = 5
};

struct Cell
{
    enum    CellType type;
};

struct Dimensions
{
    unsigned short  *widths;
    unsigned short  rows, cols;
};

struct TSP
{
    struct  Cell *grid;
    struct  Dimensions dim;
    char    *sheet;
    char    *filename;
    size_t  length;
};

#endif
