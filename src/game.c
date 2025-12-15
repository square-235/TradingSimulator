#include "../include/header.h"
#include <bits/types/struct_timeval.h>
#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

void game(int timelimit,int per){
    //初始化
    int resTime = timelimit,resPer = per;//剩余时间，下次刷新时间（重新计算价格的时间）
    int money = 1000;//初始余额1000
    int debt = 0;//欠款，每次刷新利率1%
    int TotalUnpaidShares = 0;//总欠股票价值计数
    int id_input;
    int num_input;

    Stock pool[5];
            srand(time(NULL));
    for(int i=0;i<5;i++){

        pool[i].code=1+i;
        pool[i].current_price=(rand()%9000+1000)/100.0;
        pool[i].have_volumn=0;
        pool[i].owe_volumn=0;
        pool[i].have_value=0;
        pool[i].owe_value=0;
    }
    //将使用select函数实现输入同时计时,相关声明：
    char u;//输入变量
    fd_set set;
    struct timeval timeout;

    while (1) {
        update_ui(resTime,resPer,money,debt,TotalUnpaidShares,&pool[0]);//更新界面
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
                    if (id_input<0 || id_input>5) {
                        printf("\n输入id错误");
                        fflush(stdout);
                        sleep(1);
                        continue;
                    }
                    printf("\n输入买入数量：");
                    scanf("%d",&num_input);
                    if (num_input>money) {
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
                    if (id_input<0 || id_input>5) {
                        printf("\n输入id错误");
                        fflush(stdout);
                        sleep(1);
                        continue;
                    }
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
                            printf("股票%d-价格:%.2f 已欠:%d股\n",i,pool[i].current_price,pool[i].owe_volumn);
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
                        pool[stock_id].have_volumn+=borrow_num;
                        pool[stock_id].owe_value+=borrow_value;
                        pool[stock_id].have_value+=borrow_value;
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
                    resTime=1;
                    break;
            }
        }
        resTime--;resPer--;
        if(resPer == 0){
            resPer = per;
            //刷新和计算
        for(int i=0;i<5;i++){
            srand(time(NULL));
            double change_rate=(rand()%100-50)/1000.0;//涨跌幅
            double new_price=pool[i].current_price*(1+change_rate);
            if(new_price<1.0){
                new_price=1.0;
            }
            pool[i].current_price=(float)((int)(new_price*100+0.5))/100.0;
            pool[i].have_value=pool[i].have_volumn*pool[i].current_price;
        }
            debt=debt*1.01;

}
        if(resTime == 0){
            //结算（代码还没写）
            printf("游戏结束\n");
            printf("现金余额:%d元\n",money);
            printf("欠款+欠股票:%d元\n",debt+TotalUnpaidShares);
            printf("最终总价值:%d元\n",money-debt+pool[0].have_value+pool[1].have_value+pool[2].have_value+pool[3].have_value+pool[4].have_value);
            sleep(10);
            return;
        }
    }
}
