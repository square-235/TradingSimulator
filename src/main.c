#include "../include/main.h"
int main(){
    // 初始化程序

    /* 主界面:
     * 开始游戏
     * 查看记录
     * 设置：难易程度/限时
     * 退出
     */
    main:
    printf(" 股票交易模拟器小游戏\n\n「1」开始游戏\n 「2」查看游玩历史\n 「3」设置\n 「q」退出");
    switch (getchar()) {
        case '1':
            break;
        case '2':
            break;
        case '3':
            break;
        case 'q':
            exit(0);
            break;
        default:
            goto main;
    }
}
/*
 * 游戏界面
 * 股票信息：名称/单价/涨跌幅
 * 用户信息：持有价值/现金余额/欠款/欠股票
 * 操作选项：买入/卖出/借款/借股票（做空）/打工
 * 5s定时更新主界面（无论是否操作）+ 计时器显示
 * 操作后需要等待下次更新才能操作
 */
