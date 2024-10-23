/*
 *       .-"""-.__
 *      /      ' o'\    tiny spread sheet - lexer.
 *   ,-;  '.  :   _c    Oct 22 2024
 *  :_."\._ ) ::-"
 *         ""m "m
 */
#include "lexer.h"

struct Lexer
{
    struct          Cell *cc;
    char            *content;
    size_t          pos, len;
    unsigned short  offset, row;
};

void lexer_start (struct TSP *const tsp)
{
    struct Lexer lex;
    memset(&lex, 0, sizeof(lex));

    lex.content  = tsp->sheet;
    lex.len      = tsp->length;
    lex.cc       = &tsp->grid[lex.row * tsp->dim.cols];

    for (; lex.pos < lex.len; lex.pos++)
    {
        enum TokenType thistype = tokens_unknown;

        switch (lex.content[lex.pos++])
        {
            case '\0':
                lex.pos = lex.len + 1;
                break;

            case '\n':
                lex.cc = &tsp->grid[++lex.row * tsp->dim.cols];
                lex.offset = 0;
                continue;

            case '|':
                lex.cc++;
                break;
        }

        lex.offset++;
    }

    puts("ok!");
}

