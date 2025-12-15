#include "../include/main.h"
#include "../include/game.h"
#include <bits/types/struct_timeval.h>
#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>
void update_ui(int resTime,int resPer,int money,int debt,int TotalUnpaidShares,Stock *pool){//游戏界面更新
    /*
     * 游戏界面
     * 定时更新主界面（无论是否操作）
     */
    CLEAR();
    MOVETO(0,0);
    printf("    ┌──────────────────────────────────────────────────────────────────────────────────────────────────┐\n┌───│正在交易 剩余时间：%3ds 下次刷新：%3ds 当前余额:%7d 总资产:%7d 欠款:%7d 欠股票:%7d│───┐\n│   └──────────────────────────────────────────────────────────────────────────────────────────────────┘   │\n│    id:%d 当前单价：xxx.xx 持有数量:xxxxx 持有价值:xxxxxxx 欠数量:xxxxx 欠价值:xxxxxxx                   │\n│    id:%d 当前单价：xxx.xx 持有数量:xxxxx 持有价值:xxxxxxx 欠数量:xxxxx 欠价值:xxxxxxx                   │\n│    id:%d 当前单价：xxx.xx 持有数量:xxxxx 持有价值:xxxxxxx 欠数量:xxxxx 欠价值:xxxxxxx                   │\n│    id:%d 当前单价：xxx.xx 持有数量:xxxxx 持有价值:xxxxxxx 欠数量:xxxxx 欠价值:xxxxxxx                   │\n│    id:%d 当前单价：xxx.xx 持有数量:xxxxx 持有价值:xxxxxxx 欠数量:xxxxx 欠价值:xxxxxxx                   │\n└──────────────────────────────────────────────────────────────────────────────────────────────────────────┘\n",resTime,resPer,money,money-debt-TotalUnpaidShares,debt,TotalUnpaidShares,pool[0].code,pool[1].code,pool[2].code,pool[3].code,pool[4].code);
    printf("可用操作：「1」买入 「2」卖出 「3」借款 「4」借股票 「5」打工 「q」提前结算 「Ctrl+C」退出程序\n");
    printf("说明：一次输入一个字符，输入后按下回车生效 ");
    fflush(stdout);//强制更新缓冲区
}

void game(int timelimit,int per){
    //初始化
    int resTime = timelimit,resPer = per;//剩余时间，下次刷新时间（重新计算价格的时间）
    int money = 1000;//初始余额1000
    int debt = 0;//欠款，每次刷新利率1%
    int TotalUnpaidShares = 0;//总欠股票价值计数
    int id_input;
    int num_input;

    Stock pool[5];
    for(int i=0;i<5;i++){
        pool[i].code=1+i;
        pool[i].current_price=(rand()%9000+1000)/100.0;
        pool[i].have_volumn=0;
        pool[i].owe_volumn=0;
        pool[i].have_value=0;
        pool[i].owe_value=0;
    }
}
    //将使用select函数实现输入同时计时,相关声明：
    char u;//输入变量
    fd_set set;
    struct timeval timeout;

    while (1) {
        update_ui(resTime,resPer,money,debt,TotalUnpaidShares,&pool[5]);//参数还没准备完成(还差股票链表)
        FD_ZERO(&set);
        FD_SET(0,&set);//0指代的是输入缓冲区
        timeout.tv_sec = 1;timeout.tv_usec = 0;//1s刷新界面
//将使用select函数实现输入同时计时
        int is_stdin = select(1,&set,NULL,NULL,&timeout);
        if (is_stdin != 0) {
            //处理输入
            u=getchar();
            switch (u) {
                case '1':
                    printf("\n输入要买入的id:");
                    scanf("%d",&id_input);
                    printf("\n输入买入数量：");
                    scanf("%d",&num_input);
                    // if (/*价格*/*num_input>money) {
                    //      printf("余额不足");
                    //      fflush(stdout);
                    //      sleep(1);
                    // }
                    // else {
                            // money-=/*价格*/*num_input;
                    //     //写入持有数据
                    // }
                    break;
                case '2':
                    printf("\n输入要卖出的id:");
                    scanf("%d",&id_input);
                    printf("\n输入卖出数量：");
                    scanf("%d",&num_input);
                    //  if (num_input>持有) {
                    //      printf("输入数量大于持有数量，失败");
                    //      fflush(stdout);
                    //      sleep(1);
                    //  }
                    //  else {
                    //  money+=/*价格*/*num_input;
                    //      //写入持有数据
                    //  }
                    break;
                case '3':
                    printf("\n输入借款金额(输入负数来还款):");
                    scanf("%d",&num_input);
                    if (money+num_input<0) {
                        printf("\n现金不足，无法还款");
                        fflush(stdout);
                        sleep(1);
                    }
                    else if (debt+num_input<0) {
                        printf("\n输入金额大于欠款，失败");
                        fflush(stdout);
                        sleep(1);
                    }
                    else {
                        money+=num_input;
                       debt+=num_input;                    
                    }
                    break;
                case '4':
                    {
                        int stock_id,borrow_num;
                        printf("\n可借的股票\n");
                        for(int i=0;i<5;i++){
                            printf("股票%d-价格:%d 已欠:%d股\n",i,pool[i].current_price,pool[i].owe_volumn);
                        }
                        printf("\n输入要借的股票id(0-4):");
                        scanf("%d",&stock_id);
                        while(getchar()!='\n');
                        if(stock_id<0||stock_id>4){
                            printf("输入id错误\n");
                            fflush(stdout);
                            sleep(1);
                        }
                        printf("输入借股票的数量:");
                        scanf("%d",&borrow_num);
                        while(getchar()!='\n');
                        if(borrow_num<=0){
                            printf("输入数量错误\n");
                            fflush(stdout);
                            sleep(1);
                        }
                        int borrow_value=pool[stock_id].current_price*borrow_num;
                        pool[stock_id].owe_volumn+=borrow_num;
                        pool[stock_id].owe_value+=borrow_value;
                        TotalUnpaidShares+=borrow_value;
                        printf("\n借入完成\n");
                        printf("股票%d:借了%d股,价值%d元\n",stock_id,borrow_num,borrow_value);
                        printf("该股票累计欠%d股,价值%d元\n",pool[stock_id].owe_volumn,pool[stock_id].owe_value);
                        printf("总欠股价值:%d元\n",TotalUnpaidShares);
                        printf("按回车键继续");
                        fflush(stdout);
                        getchar();
                    }
                    break;
                case '5':
                    money+=job();
                    break;
                case 'q':
                    break;
            }
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
