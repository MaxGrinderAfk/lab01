#include "functions.h"

int options = 0;

void parseOptions(int argc, char *argv[], char **startDir) {
    int opt;
    struct option longOptions[] = {
        {"sort", no_argument, NULL, 's'},
        {"links", no_argument, NULL, 'l'},
        {"directory", no_argument, NULL, 'd'},
        {"file", no_argument, NULL, 'f'},
        {NULL, 0, NULL, 0}
    };

    while ((opt = getopt_long(argc, argv, "ldfs", longOptions, NULL)) != -1) {
        switch (opt) {
            case 'l': options |= OPT_L; break;
            case 'd': options |= OPT_D; break;
            case 'f': options |= OPT_F; break;
            case 's': options |= OPT_S; break;
            default:
                fprintf(stderr, "Usage: %s [-ldfs] [dir]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    *startDir = (optind < argc) ? strdup(argv[optind]) : strdup(".");
}

int compare(const FTSENT **a, const FTSENT **b) {
    return strcoll((*a)->fts_name, (*b)->fts_name);
}

int filterEntry(const FTSENT *entry) {
    if ((options & (OPT_L | OPT_D | OPT_F)) == 0) return 1; 

    switch (entry->fts_info) {
        case FTS_SL:  return options & OPT_L;
        case FTS_D:   return options & OPT_D;
        case FTS_F:   return options & OPT_F;
        default:      return 0;
    }
}
