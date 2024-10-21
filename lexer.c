/*
 *       .-"""-.__
 *      /      ' o'\    tiny spread sheet - lexer.
 *   ,-;  '.  :   _c    Oct 21 2024
 *  :_."\._ ) ::-"
 *         ""m "m
 */
#include "lexer.h"
#include <string.h>
#include <ctype.h>

struct Lexer
{
    struct Cell     *cc;
    char            *content;
    size_t          pos, len;
    unsigned short  nline, nrow, ncols;
    short           offset;
};

static void lexer (struct Lexer *const);
static enum TokenKind kind_of_this_char (const char, const char);

static void handle_newline (struct Lexer *const);

void lexer_start_lexer (struct TinySp *const sp)
{
    struct Lexer lex;
    memset(&lex, 0, sizeof(lex));

    lex.content = sp->content;
    lex.pos = 0;
    lex.len = sp->length;
    lex.nline = 1;

    /* `row` is gonna be used as an offset to advance through cells when
     * newlines are found; first cell in the next row is gonna be `row`
     * times the number of columns (ncols) */
    lex.nrow = 0;

    lex.ncols = sp->dims.cols;
    lex.offset =  -1;

    lex.cc = &sp->grid[lex.nrow * lex.ncols + 0];
    lexer(&lex);
}

static void lexer (struct Lexer *const lex)
{
    while (lex->pos < lex->len) {
        enum TokenKind kind = kind_of_this_char(lex->content[lex->pos], lex->content[++lex->pos]);
        lex->offset++;

        switch (kind) {
            case tkind_new_line: handle_newline(&lex); break;
        }
    }
}

static enum TokenKind kind_of_this_char (const char this, const char next)
{
    switch (this) {
        case '\n':
        case '\0':
        case '|':   return this;
    }

    return tkind_unknown;
}

static void handle_newline (struct Lexer *const lex)
{
    lex->offset = -1;
}

