#include "../include/main.h"
#include <bits/types/struct_timeval.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include "../include/game.h"

void update_ui(int resTime,int resPer,int money,int debt,int TotalUnpaidShares){//游戏界面更新
    /*
     * 游戏界面
     * 定时更新主界面（无论是否操作）
     */
    CLEAR();
    MOVETO(0,0);
    printf("    ┌──────────────────────────────────────────────────────────────────────────────────────────────────┐\n┌───│正在交易 剩余时间：%3ds 下次刷新：%3ds 当前余额:%7d 总资产:%7d 欠款:%7d 欠股票:%7d│───┐\n│   └──────────────────────────────────────────────────────────────────────────────────────────────────┘   │\n│    id:xxx 当前单价：xxx.xx 持有数量:xxxxx 持有价值:xxxxxxx 欠数量:xxxxx 欠价值:xxxxxxx                   │\n│    id:xxx 当前单价：xxx.xx 持有数量:xxxxx 持有价值:xxxxxxx 欠数量:xxxxx 欠价值:xxxxxxx                   │\n│    id:xxx 当前单价：xxx.xx 持有数量:xxxxx 持有价值:xxxxxxx 欠数量:xxxxx 欠价值:xxxxxxx                   │\n│    id:xxx 当前单价：xxx.xx 持有数量:xxxxx 持有价值:xxxxxxx 欠数量:xxxxx 欠价值:xxxxxxx                   │\n│    id:xxx 当前单价：xxx.xx 持有数量:xxxxx 持有价值:xxxxxxx 欠数量:xxxxx 欠价值:xxxxxxx                   │\n└──────────────────────────────────────────────────────────────────────────────────────────────────────────┘\n",resTime,resPer,money,money-debt-TotalUnpaidShares,debt,TotalUnpaidShares);
    printf("可用操作：「1」买入 「2」卖出 「3」借款 「4」借股票 「5」打工 「q」提前结算 「Ctrl+C」中途退出（系统）");
    fflush(stdout);
}

void game(int timelimit,int per){
    //初始化
    int resTime = timelimit,resPer = per;//剩余时间，下次刷新时间（重新计算价格的时间）
    int money = 1000;//初始余额1000
    int debt = 0;//欠款，每次刷新利率1%
    int TotalUnpaidShares = 0;//总欠股票价值计数
    //股票结构体还没有准备好

    //将使用select函数实现输入同时计时,相关声明和初始化：
    char u;//输入变量
    fd_set set;
    struct timeval timeout;
    timeout.tv_sec = 1;timeout.tv_usec = 0;//1s刷新界面
    FD_ZERO(&set);
    FD_SET(0,&set);//0指代的是输入缓冲区

    while (1) {
        update_ui(resTime,resPer,money,debt,TotalUnpaidShares);//参数还没准备完成(还差股票链表)

//将使用select函数实现输入同时计时
        int is_stdin = select(1,&set,NULL,NULL,&timeout);
        if (is_stdin == 0) {//无输入
            printf("\n无输入");
        }
        else {
            //处理输入
            scanf("%c",&u);
            printf("\n%c",u);
        }
        resTime--;resPer--;
        if(resPer == 0){
            resPer = per;
            //刷新和计算（代码还没写）
        }
        if(resTime == 0){
            //结算（代码还没写）
            return;
        }
    }
}
