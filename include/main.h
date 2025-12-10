#ifndef MAIN_H
#define MAIN_H

// 控制台光标控制
// 清除屏幕
#define CLEAR() printf("\033[2J")
// 上移光标
#define MOVEUP(x) printf("\033[%dA", (x))
// 下移光标
#define MOVEDOWN(x) printf("\033[%dB", (x))
// 左移光标
#define MOVELEFT(y) printf("\033[%dD", (y))
// 右移光标
#define MOVERIGHT(y) printf("\033[%dC",(y))
// 定位光标
#define MOVETO(x,y) printf("\033[%d;%dH", (x), (y))

#define CLEAR_LINE() printf("\033[K")

#define TIME_HARD 20 //总限时
#define PER_HARD 1 //刷新间隔

#define TIME_SIMPLE 60
#define PER_SIMPLE 3

#define TIME_EASY 180
#define PER_EASY 9

void game(int timelimit,int per);
void hardchange(int *t,int *q);

#endif
