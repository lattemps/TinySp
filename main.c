/*
 *       .-"""-.__
 *      /      ' o'\    tiny spread sheet - starting point.
 *   ,-;  '.  :   _c    Oct 21 2024
 *  :_."\._ ) ::-"
 *         ""m "m
 */
#include "tinysp.h"
#include <err.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>

static void print_usage (void);
static void parse_arguments (int, char**, struct TinySp *const);

int main (int argc, char **argv)
{
    if (argc == 1) print_usage();

    struct TinySp sp;
    memset(&sp, 0, sizeof(sp));

    parse_arguments(argc, argv, &sp);

    return 0;
}

static void print_usage (void)
{
    printf("TinySp - Tiny spread sheet engine (unique version) [%s %s]\n\n", __DATE__, __TIME__);
    puts("usage: tsp [-s <sheetname>] [arguments]");
    puts("arguments:");
    exit(EXIT_SUCCESS);
}

static void parse_arguments (int argc, char **argv, struct TinySp *const sp)
{
    int opt;

    while ((opt = getopt(argc, argv, ":s:")) != -1) {
        switch (opt) {
            case 's': sp->spname = optarg; break;
            case ':': errx(EXIT_FAILURE, "cannot continue since `-%c` option requieres an argument", optopt); break;
            case '?': errx(EXIT_FAILURE, "cannot continue since `-%c` option is unknown", optopt); break;
        }
    }

    if (!sp->spname) errx(EXIT_FAILURE, "cannot continue since no sheet was provided");
}
