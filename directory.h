#ifndef DIRECTORY_H
#define DIRECTORY_H

#include<dirent.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

extern char* PATH;             //$PATH
extern char** bins;            //all executable files' names
extern int bins_amount;        //bins array's size
extern int current_dir_entry;  //current element in bins

static int _strcmp(const void *a, const void *b)
{
  return strcmp(*(const char **)a, *(const char **)b);
}

extern void read_path(void);    //read each dir from $PATH and record it in bins
extern int read_dir(char* dir); //read files in dir
extern void free_bins(void);

extern int get_fullpath(char* bin, char**output);
extern void launch_process(char* full_path);
#endif
