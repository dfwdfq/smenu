#ifndef WINDOW_H
#define WINDOW_H
#include"config.h"
#include<raylib.h>

extern char input[STR_BUF_LEN];
extern int letter_counter;    //current letter in input
extern int current_selection; //changed by UP/DOWN arrows

/*
 reads keyboard input
 1  - stops reading
 0  - keep reading
 -1 - ?
*/
extern int read_input(int matches_amount);
extern void draw_border(void);
#endif
