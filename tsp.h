/*
 *       .-"""-.__
 *      /      ' o'\    tiny spread sheet - includes.
 *   ,-;  '.  :   _c    Oct 22 2024
 *  :_."\._ ) ::-"
 *         ""m "m
 */
#ifndef TSP_TSP_H
#define TSP_TSP_H
#include <stdio.h>

#define __check_ptr(a)  do { if (a) break; err(EXIT_FAILURE, "fatal internal error %s %d", __FILE__, __LINE__); } while (0)

struct Dimensions
{
    unsigned short  *widths;
    unsigned short  rows, cols;
};

struct TSP
{
    struct  Dimensions dim;
    char    *sheet;
    char    *filename;
    size_t  length;
};

#endif
