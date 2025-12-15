#include <stdio.h>

typedef struct {
    float price; 
} Stock;

typedef struct {
    float cash;          
    int hold;            
    Stock stock;         
    float borrowed_money;
} Account;

// 借款配置
#define MAX_BORROW_AMOUNT 10000.0f

int buyStock(Account *acc, int buy_amount) {
    if (buy_amount <= 0) {
        printf("买入数量必须为正整数\n");
        return 1;
    }

    float total_cost = buy_amount * acc->stock.price;
    if (total_cost > acc->cash) {
        printf("需%.2f元，当前仅%.2f元\n", total_cost, acc->cash);
        return 2;
    }

    //买入
    acc->cash -= total_cost;
    acc->hold += buy_amount;

    printf("已买入%d股，花费%.2f元，剩余现金%.2f元\n",
           buy_amount, total_cost, acc->cash);
    return 0;
}

int sellStock(Account *acc, int sell_amount) {
    if (sell_amount <= 0) {
        printf("抛售数量必须为正整数\n");
        return 1;
    }

    if (sell_amount > acc->hold) {
        printf("当前仅持有%d股，无法抛售%d股\n",acc->hold, sell_amount);
        return 2;
    }

    //抛售
    float total_income = sell_amount * acc->stock.price;
    acc->cash += total_income;
    acc->hold -= sell_amount;

    printf("已卖出%d股，获得%.2f元，剩余现金%.2f元\n",sell_amount, total_income, acc->cash);
    return 0;
}
int borrowMoney(Account *acc, float borrow_amount) {

    if (borrow_amount <= 0) {
        printf("[借款金额必须大于0\n");
        return 1;
    }

    if (acc->borrowed_money > 0) {
        printf("已有未还借款（本金%.2f元），请先还款\n",acc->borrowed_money);
        return 2;
    }


    if (borrow_amount > MAX_BORROW_AMOUNT) {
        printf("最大借款额度为%.2f元，当前申请%.2f元\n",
               MAX_BORROW_AMOUNT, borrow_amount);
        return 3;
    }

    //借款
    acc->cash += borrow_amount;
    acc->borrowed_money = borrow_amount;

    printf("已借款%.2f元，账户现金为%.2f元\n",borrow_amount, acc->cash);
    return 0;
}

int repayMoney(Account *acc) {
    if (acc->borrowed_money <= 0) {
        printf("暂无未还借款！\n");
        return 1;
    }

    if (acc->cash < acc->borrowed_money) {
        printf("现金不足，需还本金%.2f元，当前仅%.2f元\n",acc->borrowed_money, acc->cash);
        return 2;
    }

    // 还款
    acc->cash -= acc->borrowed_money;
    float repaid_amount = acc->borrowed_money;
    acc->borrowed_money = 0;

    printf("已还清借款本金%.2f元，剩余现金%.2f元\n",
           repaid_amount, acc->cash);
    return 0;
}