/*
 *       .-"""-.__
 *      /      ' o'\    tiny spread sheet - data types.
 *   ,-;  '.  :   _c    Oct 15 2024
 *  :_."\._ ) ::-"
 *         ""m "m
 */
#ifndef TINYSP_STRUCT_H
#define TINYSP_STRUCT_H
#include <err.h>
#include <stdio.h>

#define __check_mem(a)    do { if (a) break; err(1, "cannot continue (%s: %d)", __FILE__, __LINE__); } while (0)

struct Sheet
{
    char    *src;
    size_t  length;
};

struct TinySp
{
    struct Sheet    sheet;
    char            *spfilename;
    char            separator;
};

#endif
