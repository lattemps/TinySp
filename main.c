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

static void read_sheet_content (const char *const, char **const, size_t *const);
static void determinate_sheet_dimensions (const char*, unsigned short *const, unsigned short *const);

int main (int argc, char **argv)
{
    if (argc == 1) print_usage();

    struct TinySp sp;
    memset(&sp, 0, sizeof(sp));

    parse_arguments(argc, argv, &sp);
    read_sheet_content(sp.spname, &sp.content, &sp.length);

    determinate_sheet_dimensions(sp.content, &sp.dims.rows, &sp.dims.cols);

    printf("%d %d\n", sp.dims.rows, sp.dims.cols);
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
            case ':': errx(1, "cannot continue since `-%c` option requieres an argument", optopt); break;
            case '?': errx(1, "cannot continue since `-%c` option is unknown", optopt); break;
        }
    }

    if (!sp->spname) errx(1, "cannot continue since no sheet was provided");
}

static void read_sheet_content (const char *const filename, char **const content, size_t *const length)
{
    FILE *sheet = fopen(filename, "r");
    if (!sheet)
        err(1, "cannot continue since '%s' file does not work", filename);

    fseek(sheet, 0, SEEK_END);
    *length = ftell(sheet);
    fseek(sheet, 0, SEEK_SET);

    *content = (char*) calloc(*length + 1, sizeof(char));
    __check_mem(*content);

    const size_t didread = fread(*content, 1, *length, sheet);

    if (didread != *length)
        errx(1, "cannot continue since not whole file was read: %ld/%ld bytes were read", didread, *length);
    fclose(sheet);
}

static void determinate_sheet_dimensions (const char *src, unsigned short *const rows, unsigned short *const cols)
{
    bool inStr = false;
    unsigned short Tcols = 0;

    while (*src) {
        register char a = *src++;
        if (a == '\n') {
            *cols = (Tcols > *cols) ? Tcols : *cols;
            Tcols = 0;
            *rows += 1;
        }
        else if (a == '"') inStr = !inStr;
        else if (a == '|' && !inStr) Tcols++;
    }

    *cols = (Tcols > *cols) ? Tcols : *cols;
}
