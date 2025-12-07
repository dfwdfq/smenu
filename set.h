#ifndef SET_H
#define SET_H
#include<stdbool.h>
#include"uthash.h"
#include"config.h"

struct PathSet
{
  char element[STR_BUF_LEN];
  UT_hash_handle hh;
};


#endif
