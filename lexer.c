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
    unsigned short  offset, rowidth;
    short           row;
};

static enum TokenType eat_character (const char, const char);

void lexer_start (struct TSP *const tsp)
{
    struct Lexer lex;
    memset(&lex, 0, sizeof(lex));

    lex.content  = tsp->sheet;
    lex.len      = tsp->length;
    lex.offset   = -1;
    lex.rowidth  = tsp->dim.cols;
    lex.cc       = &tsp->grid[lex.row * lex.rowidth];

    for (; lex.pos < lex.len; lex.pos++)
    {
        enum TokenType type = eat_character(lex.content[lex.pos], lex.content[++lex.pos]);
        lex.offset++;

        if (type == tokens_eof) break;
    }
}

static enum TokenType eat_character (const char this, const char next)
{
    switch (this)
    {
        case \0'':
        case '\n':
        case '|':
        return (enum TokenType) this:
    }
}
