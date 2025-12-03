#include "../include/main.h"
#include <stdio.h>

void update_ui(){//游戏界面更新
    /*
     * 游戏界面
     * 定时更新主界面（无论是否操作）
     */
    CLEAR();
    MOVETO(0,0);
    printf("    ┌──────────────────────────────────────────────────────────────────────────────────────────────────┐\n┌───│正在交易 剩余时间：xxxs 下次刷新：xxxs 当前余额:xxxxxxx 总资产:xxxxxxx 欠款:xxxxxxx 欠股票:xxxxxxx│───┐\n│   └──────────────────────────────────────────────────────────────────────────────────────────────────┘   │\n│    id:xxx 当前单价：xxx.xx 持有数量:xxxxx 持有价值:xxxxxxx 欠数量:xxxxx 欠价值:xxxxxxx                   │\n│    id:xxx 当前单价：xxx.xx 持有数量:xxxxx 持有价值:xxxxxxx 欠数量:xxxxx 欠价值:xxxxxxx                   │\n│    id:xxx 当前单价：xxx.xx 持有数量:xxxxx 持有价值:xxxxxxx 欠数量:xxxxx 欠价值:xxxxxxx                   │\n│    id:xxx 当前单价：xxx.xx 持有数量:xxxxx 持有价值:xxxxxxx 欠数量:xxxxx 欠价值:xxxxxxx                   │\n│    id:xxx 当前单价：xxx.xx 持有数量:xxxxx 持有价值:xxxxxxx 欠数量:xxxxx 欠价值:xxxxxxx                   │\n└──────────────────────────────────────────────────────────────────────────────────────────────────────────┘\n");
    printf("可用操作：「1」买入 「2」卖出 「3」借款 「4」借股票 「5」打工 「q」提前结算 「Ctrl+C」中途退出（系统）");
}

void game(int timelimit,int per){
    //初始化
    int resTime,resPer;
    int money = 1000;//初始余额1000
    int debt = 0;//欠款，每次刷新利率1%
    int TotalUnpaidShares = 0;//总欠股票计数
    //股票结构体还没有准备好
    while (1) {
        update_ui();//参数还没准备完成
        //每秒刷新（代码还没写）&用户有输入就接收（代码还没写）
        switch (getchar()) {
            case '1':
                break;
            case '2':
                break;
            case '3':
                break;
            case '4':
                break;
        }
    }
}
