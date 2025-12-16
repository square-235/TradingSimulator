#include "../include/header.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

//结构体
#define MAX_REC 100  
// 最大记录数
typedef struct {
    char line[BUFSIZ];  
    // 每行原始内容
    int profit;         
    // 盈亏值
} Rec;

// 盈亏值
static int getProfit(const char* s) {
    const char* p = strstr(s, "盈亏:");
    return p ? atoi(p+3) : 0;
}

// 冒泡排序
static void bubbleSort(Rec recs[], int n) {
    for (int i=0; i<n-1; i++)
        for (int j=0; j<n-1-i; j++)
            if (recs[j].profit < recs[j+1].profit)
            // 降序交换
             { 
                Rec t = recs[j];
                recs[j] = recs[j+1];
                recs[j+1] = t;
            }
}

// 解析data文件
void parseFile (const char* filename) {
    getchar();
    FILE* fp = fopen(filename, "r");
    // 如果失败，输出失败原因
    if (!fp) {
        printf ("%s open failed : %s\n", filename, strerror(errno));
        return ;
    }

    // 初始化记录数组
    Rec recs[MAX_REC] = {0};
    int rec_cnt = 0;

    // 定义缓冲区，用于储存fp文件中读取到的内容
    char buf[BUFSIZ];
    // read the file， 当fp文件读取结束后停止
    while (!feof(fp)) {
        // 一行一行读
        if (!fgets(buf, BUFSIZ, fp))  break;
        // 跳过UTF8文件 bom头    
        if (strstr(buf, "\xEF\xBB\xBF")) 
            strcpy (buf, buf + 3);
        // 跳过文件中注释 “#”
        if (buf[0] == '#')  continue;  

        //存储记录
        strcpy(recs[rec_cnt].line, buf);
        recs[rec_cnt++].profit = getProfit(buf);
    }

    // 冒泡排序 
    bubbleSort(recs, rec_cnt);
    for (int i=0; i<rec_cnt; i++) printf("%s", recs[i].line);

    printf("\n按回车返回...");
    getchar();
    fclose(fp);
}


void saveCurrentGamedata(int final_value) {
    // 打开文件
    FILE* fp = fopen("./data.txt", "a");
    //追加写入
    assert (fp != NULL);

    // 书写保存数据文件
    
    //写入时间区分记录（方法来自网络）
    time_t rawtime;
    struct tm *info;
    char buffer[80];
    time(&rawtime);
    info = localtime(&rawtime);
    strftime(buffer, 80, "%Y/%m/%d %H:%M:%S ", info);
    //格式化时间
    fprintf(fp, "%s", buffer);

    // 写入数据
    fprintf(fp, "盈亏:");
    if(final_value > 0){
        fprintf(fp, "+");
    }
    if(final_value < 0){
        fprintf(fp, "-");
    }
    fprintf(fp, "%d元\n", final_value);
    
    fclose(fp);
}