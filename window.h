#ifndef WINDOW_H
#define WINDOW_H
#include"config.h"
#include<raylib.h>

extern char input[STR_BUF_LEN];
extern int letter_counter;
extern int current_selection; //changed by UP/DOWN arrows or j,k

extern int read_input(int matches_amount);
extern void draw_border(void);
#endif
