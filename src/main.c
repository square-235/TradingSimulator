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
        printf("游戏说明：模拟真实股票交易环境，在限定时间赚取尽可能多的收入！\n输入菜单选项：");
        switch (getchar()) {
            case '1':
                game(timelimit,per);//进入游戏
                break;
            case '2':
                parseFile("./data.txt");//读数据文件
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

