#include "functions.h"

int main (int argc, char *argv[]) {
    char *startDir;
    parseOptions(argc, argv, &startDir);

    char *paths[] = { startDir, NULL };
    FTS *ftsp = fts_open(paths, FTS_NOCHDIR | FTS_COMFOLLOW, 
                         (options & OPT_S) ? compare : NULL);
    if (!ftsp) {
        perror("fts_open");
        exit(EXIT_FAILURE);
    }

    FTSENT *entry;
    while ((entry = fts_read(ftsp)) != NULL) {
        if (entry->fts_level > 0 && entry->fts_name[0] == '.') continue;
        if (filterEntry(entry)) {
            printf("%s\n", entry->fts_path);
        }
    }

    fts_close(ftsp);

    free(startDir);

    return EXIT_SUCCESS;
}



