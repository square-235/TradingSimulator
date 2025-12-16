#ifndef INCLUDE_H
#define INCLUDE_H

// 控制台光标控制宏
// 清除屏幕
#define CLEAR() printf("\033[2J")
// 定位光标
#define MOVETO(x,y) printf("\033[%d;%dH", (x), (y))
//清屏
#define CLEAR_LINE() printf("\033[K")

#define TIME_HARD 20 //总限时
#define PER_HARD 1 //刷新间隔

#define TIME_SIMPLE 60
#define PER_SIMPLE 3

#define TIME_EASY 180
#define PER_EASY 9

void game(int timelimit,int per);
void hardchange(int *t,int *q);
void update_price();
int job();

    //股票结构体
typedef struct{
    double current_price;//当前价
    int code;//ID
    int have_volumn;//持有量
    int have_value;//持有价值
    int owe_volumn;//欠有量
    int owe_value;//欠有价值
}Stock;

void update_ui(int resTime,int resPer,int money,int debt,int TotalUnpaidShares,Stock *pool);

void parseFile(const char* filename);//解析data文件
void saveCurrentGamedata(int final_value);//保存当前游戏数据
#endif
