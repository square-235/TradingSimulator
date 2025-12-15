#ifndef GAME_H
#define GAME_H

void update_price();
int job();


    //股票结构体
typedef struct{
    int current_price;//当前价
    int code;//ID
    int have_volumn;//持有量
    int have_value;//持有价值
    int owe_volumn;//欠有量
    int owe_value;//欠有价值
}Stock;
#endif
