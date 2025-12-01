#include "../include/main.h"
int main(){
    // 初始化程序（设置参数）
    int timelimit=TIME_SIMPLE,per=PER_SIMPLE;
    /* 主界面:
     * 开始游戏
     * 查看记录
     * 设置：难易程度/限时
     * 退出
     */
    while (1) {
    printf(" 股票交易模拟器小游戏\n\n 「1」开始游戏\n 「2」查看游玩历史\n 「3」设置\n 「q」退出\n");
    switch (getchar()) {
        case '1':
            game(timelimit,per);//进入游戏
            break;
        case '2':
//
            break;
        case '3':
//设置：难易程度/限时，HARD/SIMPLE/EASY/SIMPLE三挡或自己输入
            hardchange(&timelimit,&per);
            break;
        case 'q':
            exit(0);
            break;
        default:
            break;
    }
    }
}

//调难度界面
void hardchange(int *t,int *q){
    exit(-10086);//还没写程序时用这行，便于部分调试
}

void game(int timelimit,int per){
    /*
     * 游戏界面
     * 股票信息：名称/单价/涨跌幅
     * 用户信息：持有价值/现金余额/欠款/欠股票
     * 操作选项：买入/卖出/借款/借股票（做空）/打工
     * 5s定时更新主界面（无论是否操作）+ 计时器显示
     * 操作后需要等待下次更新才能操作
     */
    exit(-10086);//还没写程序时用这行，便于部分调试
}


