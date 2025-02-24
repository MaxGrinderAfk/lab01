#include "libraries.h"

#define OPT_L (1 << 0) 
#define OPT_D (1 << 1)  
#define OPT_F (1 << 2)  
#define OPT_S (1 << 3)

extern int options;

void parseOptions(int argc, char *argv[], char **startDir);
int compare(const FTSENT **a, const FTSENT **b);
int filterEntry(const FTSENT *entry);
