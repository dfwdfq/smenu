#ifndef PREFIX_MATCH_SEARCH_H
#define PREFIX_MATCH_SEARCH_H
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

int collect_prefix_matches(
    char * const *bins,
    int n,
    const char *prefix,
    char ***out_matches, 
    int *out_count       
);
#endif
