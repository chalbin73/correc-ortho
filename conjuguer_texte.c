#include "read_with_mmap.h"
#include "tableau_dyn.h"



size_t size;
char* adresse = open_mmapfile(argv[2], &size);