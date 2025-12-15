#include "../include/header.h"
#include <stdio.h>
void hardchange(int *t,int *p){//调难度界面
    CLEAR();
    MOVETO(0,0);
    getchar();
    printf("    ┌────────────────────┐\n┌───│      难度选择      │───┐\n│   └────────────────────┘   │\n│  「1」简单(9s间隔)         │\n│  「2」一般(3s间隔)         │\n│  「3」困难(1s间隔)         │\n│  「4」自定义               │\n│  「其他按键」返回          │\n└────────────────────────────┘\n");
    switch (getchar()) {
        case '1':
            *t=TIME_EASY,*p=PER_EASY;
            return;
        case '2':
            *t=TIME_SIMPLE,*p=PER_SIMPLE;
            return;
        case '3':
            *t=TIME_HARD,*p=PER_HARD;
            return;
        case '4':
            printf("\n输入股票刷新间隔");
            scanf("%d",p);
            printf("\n输入单局游戏时长");
            scanf("%d",t);
            return;
    }
}