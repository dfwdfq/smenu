/*
  the application follows suckless approach,
  so nothing external is required by application
  to run and it's configuration is stored in-memory.
  To configure the app you can change values in config.c
  or use CLI arguments.

  This header contains config definitions and CLI arguments
  processing procedures.
*/
#ifndef CONFIG_H
#define CONFIG_H
#include<raylib.h>  
#include<getopt.h>  
#include<dirent.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

extern char* PATH;
extern char** bins; //contains all executable files from $PATH
extern int bins_amount;
extern int current_dir_entry;

extern void free_bins(void);

extern void read_path(void);
extern int read_dir(char* dir);

extern unsigned int top,left, width, height;
extern unsigned int font_size;

extern Color background_color, selection_color, text_color, selected_text_color;


extern void parse_argv(int argc, char** argv);

#endif
