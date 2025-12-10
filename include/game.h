#ifndef GAME_H
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define GAME_H

void update_ui(int resTime,int resPer,int money,int debt,int TotalUnpaidShares);

void seed(){
    srand((unsigned int)time(NULL));//初始化种子
    for(int i=0;i<10000;i++){
        pool[i].code=10001+i;
        pool[i].current_price=(rand()%9000+1000)/100.0;
        pool[i].have_volumn=0;
        pool[i].owe_volumn=0;
        pool[i].have_value=0.0;
        pool[i].owe_value=0.0;
    }
}

void update_price(){//更新价格
    for(int i=0;i<10000;i++){
        double change_rate=(rand()%100-50)/1000.0;//涨跌幅
        double new_price=pool[i].current_price*(1+change_rate);
        if(new_price<1.0){
            new_price=1.0;
        }
        pool[i].current_price=(float)((int)(new_price*100+0.5))/100.0;
        pool[i].have_value=pool[i].have_volumn*pool[i].current_price;
    }
}


#endif
