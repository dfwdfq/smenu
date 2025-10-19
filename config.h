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
#include<string.h>
#include<stdio.h>

//based on /usr/include/bits/posix1_lim.h
#define STR_BUF_LEN 256 //len of dirent's d_name size

extern unsigned int top, left, width, height;
extern unsigned int font_size;
extern unsigned int x_start,y_start; //position of user's query

#define GET_MAX_VISIBLE(text_h) (int)((height-y_start-2)/text_h)-1

extern Color selection_color,
             background_color,
             text_color;

#define check_hex_color_len if(strlen(optarg) != 6){ fprintf(stderr,"Error: hex color should have 6 digits!\n");exit(-1);}
#define parse_hex_color(str) sscanf(str, "%02x%02x%02x", &r, &g, &b);

extern void parse_argv(int argc, char** argv);

#endif
