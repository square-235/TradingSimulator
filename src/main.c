#include "../include/main.h"
int main(){
    // 初始化程序（设置参数）
    int timelimit=TIME_SIMPLE,per=PER_SIMPLE;
    while (1) {
#ifdef OP_LINUX
        system("clear");
#endif
#ifdef OP_WINDOWS
        system("cls");
#endif
        printf(" 股票交易模拟器小游戏\n\n 「1」开始游戏\n 「2」查看游玩历史\n 「3」难度选择\n 「q」退出\n");
        switch (getchar()) {
            case '1':
                game(timelimit,per);//进入游戏
                break;
            case '2':
                exit(-10086);//还没写程序时用这行，便于部分调试
                break;
            case '3':
                hardchange(&timelimit,&per);//设置：难易程度/限时，HARD/SIMPLE/EASY/SIMPLE三挡或自己输入
                break;
            case 'q':
                exit(0);
                break;
            default:
                break;
        }
    }
}

void hardchange(int *t,int *p){//调难度界面
    getchar();
    printf("\n 难度选择:\n\n 「1」简单(9s间隔)\n 「2」一般(3s间隔)\n 「3」困难(1s间隔)\n 「4」自定义\n 「其他按键」返回\n");
    switch (getchar()) {
        case '1':
            *t=TIME_EASY,*p=PER_EASY;
            return;
        case '2':
            *t=TIME_SIMPLE,*p=PER_SIMPLE;
            return;
        case '3':
            *t=TIME_HARD,*p=PER_HARD;
            return;
        case '4':
            printf("\n输入股票刷新间隔");
            scanf("%d",p);
            printf("\n输入单局游戏时长");
            scanf("%d",t);
            return;
    }
}

void game(int timelimit,int per){
    printf("%d %d",timelimit,per);//debug
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


