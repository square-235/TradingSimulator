#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

void parseFile (const char* filename);
void saveCurrentGamedata();

int main() {
    parseFile ("./DATA/Test.txt"); // 解析游戏历史数据
    saveCurrentGamedata();
    return 0;
}

// 解析data文件
void parseFile (const char* filename) {

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
        printf ("%s\n", buf);
    }

    // close the file
    fclose(fp);
}

// 保存游戏数据于continueGame.txt中
void saveCurrentGamedata() {
    // 打开文件
    FILE* fp = fopen("./DATA/continueGame.txt", "w");
    assert (fp != NULL);

    // 书写保存数据文件的注释
    fprintf(fp, "#中途退出的游戏数据\n");


    fclose(fp);
}