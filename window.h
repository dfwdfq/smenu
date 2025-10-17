#ifndef WINDOW_H
#define WINDOW_H
#include"config.h"
#include<raylib.h>

#define STR_BUFFER_LEN 1024

extern char input[STR_BUFFER_LEN+1];
extern int letter_counter;

extern int current_selection;

extern int read_input(int matches_amount);
#endif
