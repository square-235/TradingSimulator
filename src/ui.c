#include "../include/header.h"
#include <stdio.h>
void update_ui(int resTime,int resPer,int money,int debt,int TotalUnpaidShares,Stock *pool){//游戏界面更新
    /*
     * 游戏界面
     * 定时更新主界面
     */
    CLEAR();
    MOVETO(0,0);
    printf("    ┌──────────────────────────────────────────────────────────────────────────────────────────────────┐\n");
    printf("┌───│正在交易 剩余时间：%3ds 下次刷新：%3ds 当前余额:%7d 总资产:%7d 欠款:%7d 欠股票:%7d│───┐\n│   └──────────────────────────────────────────────────────────────────────────────────────────────────┘   │\n",        resTime,resPer,money,money-debt+pool[0].have_value+pool[1].have_value+pool[2].have_value+pool[3].have_value+pool[4].have_value,debt,TotalUnpaidShares);
    for (int i=0;i<5;i++) {
        printf("│    id:%d 当前单价：%6.2f 持有数量:%4d 持有价值:%7d 欠数量:%4d 欠价值:%7d                       │",pool[i].code,pool[i].current_price,pool[i].have_volumn,pool[i].have_value,pool[i].owe_volumn,pool[i].owe_value);
        if(i!=4) printf("\n");
    }
    printf("\n└──────────────────────────────────────────────────────────────────────────────────────────────────────────┘\n");
    printf("可用操作：「1」买入 「2」卖出 「3」借款 「4」借股票 「5」打工 「6」智能投资开关 「q」提前结算 「Ctrl+C」退出程序\n");
    printf("说明：一次输入一个字符，输入后按下回车生效,操作过程中计时暂停 ");
    fflush(stdout);//强制更新缓冲区
}
