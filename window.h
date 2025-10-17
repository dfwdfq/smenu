#ifndef WINDOW_H
#define WINDOW_H
#include"config.h"
#include<raylib.h>
#include<string.h>

#define STR_BUFFER_LEN 1024

extern char input[STR_BUFFER_LEN+1];
extern int letter_counter;


extern int read_input(void);

#endif
