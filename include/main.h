#ifndef MAIN_H
#define MAIN_H

#define TIME_HARD 20 //总限时
#define PER_HARD 1 //刷新间隔

#define TIME_SIMPLE 60
#define PER_SIMPLE 3

#define TIME_EASY 180
#define PER_EASY 9

#include <stdio.h>
#include <stdlib.h>

void game(int timelimit,int per);
void hardchange(int *t,int *q);

#endif
