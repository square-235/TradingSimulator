#include <stdio.h>
typedef struct {
    float price;  // 股票当前单价
} Stock;

typedef struct {
    float cash;   // 账户可用现金
    int hold;     // 持有股票的数量
    Stock stock;  // 关联的股票信息
} Account;

int buyStock(Account *acc, int buy_amount) {
    // 校验买入数量
    if (buy_amount <= 0) {
        printf("[买入数量必须为正整数\n");
        return 1;
    }

    // 计算买入成本
    float total_cost = buy_amount * acc->stock.price;

    // 校验现金是否充足
    if (total_cost > acc->cash) {
        printf("需%.2f元，当前仅%.2f元\n", total_cost, acc->cash);
        return 2;
    }

    //买入
    acc->cash -= total_cost;   // 扣减现金
    acc->hold += buy_amount;   // 增加持仓
    printf("[买入成功] 已买入%d股，花费%.2f元，剩余现金%.2f元\n", 
           buy_amount, total_cost, acc->cash);
    return 0;
}

int sellStock(Account *acc, int sell_amount) {
    // 校验抛售数量
    if (sell_amount <= 0) {
        printf("抛售数量必须为正整数\n");
        return 1;
    }

    // 校验持仓是否充足
    if (sell_amount > acc->hold) {
        printf("当前仅持有%d股,无法抛售%d股\n", 
               acc->hold, sell_amount);
        return 2;
    }

    // 抛售操
    float total_income = sell_amount * acc->stock.price;
    acc->cash += total_income; 
    acc->hold -= sell_amount;  
    printf("已卖出%d股,获得%.2f元，剩余现金%.2f元\n", 
           sell_amount, total_income, acc->cash);
    return 0;
}