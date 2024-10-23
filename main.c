/*
 *       .-"""-.__
 *      /      ' o'\    tiny spread sheet - starting point.
 *   ,-;  '.  :   _c    Oct 22 2024
 *  :_."\._ ) ::-"
 *         ""m "m
 */
#include "lexer.h"
#include <getopt.h>

static void print_usage (void);
static void read_sheet_contents (const char *const, size_t *const, char **const);

static void det_table_dimensions (const char*, unsigned short *const, unsigned short *const);

int main (int argc, char **argv)
{
    if (argc == 1) print_usage();

    struct TSP tsp;
    memset(&tsp, 0, sizeof(tsp));

    int arg;
    while ((arg = getopt(argc, argv, ":s:")) != -1)
    {
        switch (arg)
        {
            case 's': tsp.filename = optarg; break;
            case 'h': print_usage(); break;
            case '?': errx(EXIT_FAILURE, "fatal error since '-%c' is not a known option", optopt); break;
            case ':': errx(EXIT_FAILURE, "fatal error since '-%c' does require an argument", optopt); break;
        }
    }

    if (!tsp.filename) errx(EXIT_FAILURE, "fatal error since no sheet was given");
    read_sheet_contents(tsp.filename, &tsp.length, &tsp.sheet);

    det_table_dimensions(tsp.sheet, &tsp.dim.rows, &tsp.dim.cols);

    tsp.grid = (struct Cell*) calloc(tsp.dim.rows * tsp.dim.cols, sizeof(*tsp.grid));
    __check_ptr(tsp.grid);

    tsp.dim.widths = (unsigned short*) calloc(tsp.dim.cols, sizeof(*tsp.dim.widths));
    __check_ptr(tsp.dim.widths);

    lexer_start(&tsp);

    free(tsp.sheet);
    free(tsp.grid);
    free(tsp.dim.widths);
    return 0;
}

static void print_usage (void)
{
    printf("\n\tTSP - Tiny Spread Sheet engine (%s %s)\n", __DATE__, __TIME__);
    puts("\tusage: tsp    -s <sheet> [arguments]");
    puts("\targuments:");
    puts("\t    -s *      specify sheet to be interpreted");
    puts("\t    -h        print this message\n");
    exit(EXIT_SUCCESS);
}

static void read_sheet_contents (const char *const filename, size_t *const bytes, char **const content)
{
    FILE *sheet = fopen(filename, "r");
    if (!sheet) err(EXIT_FAILURE, "fatal error since '%s' sheet does not work!", filename);

    fseek(sheet, 0, SEEK_END);
    *bytes = ftell(sheet);
    fseek(sheet, 0, SEEK_SET);

    *content = (char*) calloc(*bytes + 1, sizeof(**content));
    __check_ptr(*content);

    const size_t read = fread(*content, 1, *bytes, sheet);
    if (read != *bytes) errx(EXIT_FAILURE, "fatal error since not whole file was read: %ld/%ld bytes total", read, *bytes);

    fclose(sheet);
}

static void det_table_dimensions (const char *a, unsigned short *const r, unsigned short *const c)
{
    unsigned short mc = 0;

    while (*a)
    {
        const char this = *a++;
        if (this == '|') *c += 1;
        else if (this == '\n')
        {
            mc = (mc > *c) ? mc : *c;
            *r += 1;
            *c = 0;
        }
    }

    *c = mc;
}
