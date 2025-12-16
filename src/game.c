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
    int money = 10000;//初始余额10000
    int debt = 0;//欠款，每次刷新利率1%
    int TotalUnpaidShares = 0;//总欠股票资产计数
    int id_input;
    int num_input;
    //新增定投的变量
    

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
        for(int i=0;i<5;i++){
            pool[i].owe_value=pool[i].owe_volumn*pool[i].current_price;
        }
        TotalUnpaidShares=pool[0].owe_value+pool[1].owe_value+pool[2].owe_value+pool[3].owe_value+pool[4].owe_value;
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
                case '1'://买入
                    printf("\n输入要买入的id:");
                    scanf("%d",&id_input);
                    id_input--;//将id转换为数组下标
                    if (id_input<0 || id_input>4) {
                        printf("\n输入id错误");
                        fflush(stdout);
                        sleep(1);
                        continue;
                    }
                    printf("\n输入买入数量：");
                    scanf("%d",&num_input);
                    if (num_input*pool[id_input].current_price>money) {
                        printf("余额不足");
                        fflush(stdout);
                        sleep(1);
                        continue;
                    }
                    else if (num_input<0) {
                        printf("\n输入数量错误,买入数量不能为负");
                        fflush(stdout);
                        sleep(1);
                        continue;
                    }
                    else {
                        money-=pool[id_input].current_price*num_input;
                        //写入持有数据
                        pool[id_input].have_volumn+=num_input;//增加持有数量
                        pool[id_input].have_value=pool[id_input].current_price*pool[id_input].have_volumn;//价值=价格*数量（更新）
                    }
                    break;
                case '2'://卖出
                    printf("\n输入要卖出的id:");
                    scanf("%d",&id_input);
                    id_input--;//将id转换为数组下标
                    if (id_input<0 || id_input>4) {
                        printf("\n输入id错误");
                        fflush(stdout);
                        sleep(1);
                        continue;
                    }
                    printf("\n输入卖出数量：");
                    scanf("%d",&num_input);
                    if (num_input>pool[id_input].have_volumn) {
                        printf("输入数量大于持有数量，错误");
                        fflush(stdout);
                        sleep(1);
                        continue;
                    }
                    else if (num_input<0) {
                        printf("\n输入数量错误,卖出数量不能为负");
                        fflush(stdout);
                        sleep(1);
                        continue;
                    }
                    else {
                        money+=pool[id_input].current_price*num_input;
                        pool[id_input].have_volumn-=num_input;//减少持有数量
                        pool[id_input].have_value=pool[id_input].current_price*pool[id_input].have_volumn;//价值=价格*数量（更新）
                    }
                    break;
                case '3':
                    printf("\n输入借款金额(每次刷新利率1%%，输入负数来还款,最大借款金额为1000):");
                    scanf("%d",&num_input);
                    if (num_input>0 && num_input+debt>1000) {
                        printf("\n输入金额大于最大借款金额，失败");
                        fflush(stdout);
                        sleep(1);
                        continue;
                    }
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
                        printf("\n可借的股票: (输入负数量来归还)\n");
                        for(int i=0;i<5;i++){
                            printf("股票%d-价格:%.2f 已欠:%d股\n",i+1,pool[i].current_price,pool[i].owe_volumn);
                        }
                        printf("\n输入要借的股票id(1-5):");
                        scanf("%d",&stock_id);
                        stock_id--;
                        while(getchar()!='\n');
                        if(stock_id<0||stock_id>4){
                            printf("输入id错误\n");
                            fflush(stdout);
                            sleep(1);
                            continue;
                        }
                        printf("输入借股票的数量:");
                        scanf("%d",&borrow_num);
                        while(getchar()!='\n');
                        if(borrow_num<-(int)pool[stock_id].owe_volumn){///归还数量不能大于已欠数量
                            printf("输入数量错误\n");
                            fflush(stdout);
                            sleep(1);
                            continue;
                        }
                        int borrow_value=pool[stock_id].current_price*borrow_num;
                        pool[stock_id].owe_volumn+=borrow_num;
                        pool[stock_id].have_volumn+=borrow_num;
                        pool[stock_id].have_value+=borrow_value;
                        printf("\n完成\n");
                        printf("股票%d:借了%d股,价值%d元\n",stock_id,borrow_num,borrow_value);
                        printf("该股票累计欠%d股\n",pool[stock_id].owe_volumn);
                        printf("按回车键继续");
                        fflush(stdout);
                        getchar();
                    }
                    break;
                case '6'://定投
                    if (auto_invest == 0) {
                        if (money >= auto_invest_amount) {
                            auto_invest = 1;
                            printf("\n定投已开启，每次刷新将自动投入500元\n");
                        }else{
                            printf("\n资金不足，无法开启定投\n");
                        }
                    }else{
                        auto_invest = 0;
                        printf("\n定投已关闭\n");
                    }
                    printf("按回车继续");
                    fflush(stdout);
                    getchar();
                    break;
                case '5':
                    money+=job();//打工（单独拆分的模块）
                    break;
                case 'q':
                    resTime=1;//计时=1准备结算
                    break;
            }
        }
        resTime--;resPer--;
        if(resPer == 0){
            resPer = per;
            if (auto_invest == 1) {
                if (money >= auto_invest_amount) {//看资金够不够
                    int invest_per_stock = auto_invest_amount / 5;//均分资金
                    for (int i = 0; i < 5; i++) {
                        int can_buy = (int)(invest_per_stock / pool[i].current_price);//计算每股买多少
                        if (can_buy > 0) {
                            pool[i].have_volumn += can_buy;
                            pool[i].have_value += can_buy * pool[i].current_price;
                            money -= can_buy * pool[i].current_price;
                        }
                    }
                    printf("\n已自动投资500元\n");
                }else{
                    auto_invest = 0;//资金不足自己关闭
                    printf("\n资金不足，定投已关闭\n");
                }
            }
            //刷新和计算
            for(int i=0;i<5;i++){//随机刷新股票价格
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
            //结算
            printf("游戏结束\n");
            printf("现金余额:%d元\n",money);
            printf("欠款+欠股票:%d元\n",debt+TotalUnpaidShares);
            int final_value=money-debt+pool[0].have_value+pool[1].have_value+pool[2].have_value+pool[3].have_value+pool[4].have_value;//最终总资产(不含欠股票)
            //还得还股票的价值
            printf("最终总资产:%d元，减去初始的10000元，",final_value);
            final_value-=10000;
            if (final_value>0) {
                printf("你获得了%d元的利润\n",final_value);
            }
            else if (final_value==0) {
                printf("你没有获得利润或亏损\n");
            }
            else {
                printf("你亏损了%d元\n",-final_value);
            }
            //存储游戏记录(未完成)
            saveCurrentGamedata(final_value);
            printf("记录已保存，10s后继续\n");
            sleep(10);
            return;
        }
    }
}
