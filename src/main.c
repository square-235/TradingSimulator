#include "../include/header.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    // 初始化程序（设置参数）
    int timelimit=TIME_SIMPLE,per=PER_SIMPLE;
    while (1) {
        CLEAR();
        MOVETO(0,0);
        printf("    ┌────────────────────┐\n┌───│股票交易模拟器小游戏│───┐\n│   └────────────────────┘   │\n│  「1」开始游戏             │\n│  「2」查看游玩历史         │\n│  「3」难度选择             │\n│  「q」退出                 │\n└────────────────────────────┘\n");
        switch (getchar()) {
            case '1':
                game(timelimit,per);//进入游戏
                break;
            case '2':
                exit(-10086);//还没写程序，用这行便于部分调试
                break;
            case '3':
                hardchange(&timelimit,&per);//设置：难易程度/限时，HARD/SIMPLE/EASY/SIMPLE三挡或自己输入
                break;
            case 'q':
                exit(0);
                break;
            default:
                break;
        }
    }
}

