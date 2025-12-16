#include "../include/header.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <time.h>
#include <unistd.h>

// 解析data文件
void parseFile (const char* filename) {
    getchar();
    // open the file
    FILE* fp = fopen(filename, "r");
    // 如果失败，输出失败原因
    if (!fp) {
        printf ("%s open failed : %s\n", filename, strerror(errno));
        return ;
    }

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
        // 输出文件读取到的数据
        printf ("%s", buf);
    }
    printf("\n按回车返回...");
    getchar();
    fclose(fp);
}

// 保存游戏数据于continueGame.txt中
void saveCurrentGamedata(int final_value) {
    // 打开文件
    FILE* fp = fopen("./data.txt", "a");//追加写入
    assert (fp != NULL);

    // 书写保存数据文件
    
    //写入时间区分记录
    time_t rawtime;
    struct tm *info;
    char buffer[80];
    time(&rawtime);
    info = localtime(&rawtime);
    strftime(buffer, 80, "%Y/%m/%d %H:%M:%S ", info);//格式化时间
    fprintf(fp, "%s", buffer);

    // 写入数据
    fprintf(fp, "盈亏:%d元\n", final_value);
    
    fclose(fp);
}