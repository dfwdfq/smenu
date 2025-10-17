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
#include<stdlib.h>
#include<stdio.h>

extern unsigned int top, left, width, height;
extern unsigned int font_size;
extern unsigned int x_start,y_start; //position of user's query

extern Color background_color,
             selection_color,
             text_color,
             selected_text_color;


extern void parse_argv(int argc, char** argv);

#endif
