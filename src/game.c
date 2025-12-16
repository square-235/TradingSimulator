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
    double money = 10000.0;//初始余额10000 
    double debt = 0.0;//欠款，每次刷新利率1% 
    double TotalUnpaidShares = 0.0;//总欠股票资产计数 
    int id_input;
    int num_input;
    //定义智能投资相关变量
    bool auto_invest = false;
    int auto_invest_amount = 500;//每次智能投资的资金
    //创建结构体
    Stock pool[5];
    srand(time(NULL)); 
    for(int i=0;i<5;i++){
        pool[i].code=1+i;
        pool[i].current_price=(rand()%9000+1000)/100.0;
        pool[i].have_volumn=0;
        pool[i].owe_volumn=0;
        pool[i].have_value=0.0;
        pool[i].owe_value=0.0;
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
                    while(getchar()!='\n');
                    id_input--;//将id转换为数组下标
                    if (id_input<0 || id_input>4) {
                        printf("\n输入id错误");
                        fflush(stdout);
                        sleep(1);
                        continue;
                    }
                    printf("\n输入买入数量：");
                    scanf("%d",&num_input);
                    while(getchar()!='\n');
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
                    printf("\n输入要卖出的id（输入0全卖出）:");
                    scanf("%d",&id_input);
                    while(getchar()!='\n');
                    id_input--;//将id转换为数组下标
                    if (id_input==-1) {//全卖出
                        for (int i=0;i<5;i++) {
                            if (pool[i].have_volumn>0) {
                                num_input=pool[i].have_volumn;//用num_input暂存
                                money+=pool[i].current_price*num_input;
                                pool[i].have_volumn-=num_input;
                                pool[i].have_value=pool[i].current_price*pool[i].have_volumn;
                            }
                        }
                        continue;
                    }
                    else if (id_input<-1 || id_input>4) {
                        printf("\n输入id错误");
                        fflush(stdout);
                        sleep(1);
                        continue;
                    }
                    printf("\n输入卖出数量：");
                    scanf("%d",&num_input);
                    while(getchar()!='\n');
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
                    while(getchar()!='\n');
                    borrow(&money,&debt,num_input);//借款操作函数
                    break;
                case '4':
                    {
                        int stock_id,borrow_num;
                        printf("\n做空：高价时借股票来卖，低价时买股票来还");
                        printf("\n可借的股票: (输入负数量来归还)\n");
                        for(int i=0;i<5;i++){
                            printf("股票%d-价格:%.2f 已欠:%d股\n",i+1,
                                pool[i].current_price,pool[i].owe_volumn);
                        }
                        printf("\n输入要借的股票id(1-5,输0退出):");
                        scanf("%d",&stock_id);
                        stock_id--;
                        while(getchar()!='\n');
                        if(stock_id==-1){
                            continue;
                        }
                        else if(stock_id<-1||stock_id>4){
                            printf("输入id错误\n");
                            fflush(stdout);
                            sleep(1);
                            continue;
                        }
                        printf("输入借股票的数量:(最大1000股)");
                        scanf("%d",&borrow_num);
                        while(getchar()!='\n');
                        
                        //借股票
                        if(borrow_num > 0&&borrow_num<1000){
                            // 借入股票后立即卖出，获得现金
                            double sell_value = pool[stock_id].current_price * borrow_num;
                            money += sell_value; // 卖出股票获得现金
                            pool[stock_id].owe_volumn += borrow_num; // 记录欠的股票数量
                            printf("\n做空开仓成功！\n");
                            printf("股票%d:借入%d股并卖出，获得现金%.2f元\n",
                                stock_id+1,borrow_num,sell_value);
                        }
                        else if (borrow_num>=1000) {
                            printf("数量超过上限");
                            fflush(stdout);
                            sleep(1);
                            continue;
                        }
                        // 还股票
                        else if(borrow_num < 0){
                            int return_num = -borrow_num; // 要归还的股票数量
                            // 归还数量不能超过已欠数量
                            if(return_num > pool[stock_id].owe_volumn){
                                printf("归还数量大于已欠数量，输入错误\n");
                                fflush(stdout);
                                sleep(1);
                                continue;
                            }
                            // 买入股票归还，消耗现金
                            double buy_value = pool[stock_id].current_price * return_num;
                            if(money < buy_value){
                                printf("现金不足，无法买入股票归还！\n");
                                fflush(stdout);
                                sleep(1);
                                continue;
                            }
                            money -= buy_value; // 买入股票消耗现金
                            pool[stock_id].owe_volumn -= return_num; // 减少欠的股票数量
                            printf("\n做空平仓成功！\n");
                            printf("股票%d:买入%d股归还，消耗现金%.2f元\n",
                                stock_id+1,return_num,buy_value);
                        }
                        // 输入0则无操作
                        else{
                            printf("输入数量为0，无操作\n");
                            fflush(stdout);
                            sleep(1);
                            continue;
                        }
                        
                        printf("该股票累计欠%d股\n",pool[stock_id].owe_volumn);
                        printf("按回车键继续");
                        fflush(stdout);
                        getchar();
                    }
                    break;
                case '5':
                    money+=job();//打工（单独拆分的模块）
                    break;
                case '6'://智能投资
                    auto_invest = autoInvest(money,auto_invest_amount,auto_invest);
                    break;
                case 'q':
                    resTime=1;//计时=1以跳转到结算
                    break;
            }
        }
        resTime--;resPer--;
        if(resPer == 0){
            resPer = per;
            if (auto_invest == true) {//智能投资
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
                }else{
                    auto_invest = false;//资金不足自动关闭智能投资
                }
            }
            //刷新和计算
            for(int i=0;i<5;i++){//随机刷新股票价格
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
            printf("现金余额:%.2f元\n",money);
            printf("欠款+欠股票:%.2f元\n",debt+TotalUnpaidShares);
            
            double final_value=money-debt+pool[0].have_value+pool[1].have_value+pool[2].have_value+pool[3].have_value+pool[4].have_value-TotalUnpaidShares;//最终总资产(含欠股票抵扣)
            //还得还股票的价值
            printf("最终总资产:%.2f元，减去初始的10000元，",final_value);
            final_value-=10000.0;
            if (final_value>0) {
                printf("你获得了%.2f元的利润\n",final_value);
            }
            else if (final_value==0) {
                printf("你没有获得利润或亏损\n");
            }
            else {
                printf("你亏损了%.2f元\n",-final_value);
            }
            //存储游戏记录(未完成)
            saveCurrentGamedata(final_value);
            printf("记录已保存，10s后继续\n");
            sleep(10);
            return;
        }
    }
}