/*
 *       .-"""-.__
 *      /      ' o'\    tiny spread sheet - main file.
 *   ,-;  '.  :   _c    Oct 15 2024
 *  :_."\._ ) ::-"
 *         ""m "m
 */
#include "include.h"
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

static void parse_arguments (struct TinySp *const, const int, char**);
static void print_usage (void);

static void read_file (const char *const, struct Sheet *const);

int main (int argc, char** argv)
{
    if (argc == 1) print_usage();

    struct TinySp tsp;
    memset(&tsp, 0, sizeof(tsp));

    parse_arguments(&tsp, argc, argv);
    read_file(tsp.spfilename, &tsp.sheet);

    return 0;
}

static void parse_arguments (struct TinySp *const tsp, const int nargs, char **vargs)
{
    opterr = 0; 
    signed int op;

    while ((op = getopt(nargs, vargs, ":S:s:h")) != -1) {
        switch (op) {
            case 'S': tsp->spfilename = optarg; break;
            case 's': tsp->separator = *optarg; break;
            case 'h': print_usage(); break;
            case '?': errx(0, "cannot continue due to '-%c' option which is unknown to TinySp", optopt);
            case ':': errx(0, "cannot continue due to '-%c' option which requieres an argument", optopt);
        }
    }

    if (!tsp->spfilename)
        errx(0, "cannot continue since no sheet was provided");
}

static void print_usage (void)
{
    printf("Tiny Spread Sheet engine - last compilation: %s %s\n", __DATE__, __TIME__);
    puts("usage: TinySp   -S <filename> [arguments]");
    puts("arguments:");
    puts("  -s <*>              use '*' as cell seperator");
    puts("  -h                  familiar?");
    exit(0);
}

static void read_file (const char *const spfilename, struct Sheet *const sheet)
{
    FILE *file = fopen(spfilename, "r");
    if (!file) err(1, "sheet given (%s) did not work", spfilename);

    fseek(file, 0, SEEK_END);
    sheet->length = ftell(file);
    fseek(file, 0, SEEK_SET);

    sheet->src = (char*) calloc(sheet->length + 1, sizeof(char));
    __check_mem(sheet->src);

    const size_t read = fread(sheet->src, 1, sheet->length, file);
    if (read != sheet->length)
        errx(0, "cannot continue; file not read at all (%ld/%ld B)", read, sheet->length);
    fclose(file);
}
