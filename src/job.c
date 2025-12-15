#include "../include/header.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
int job(){
    fd_set set;
    struct timeval timeout;
    printf("\n可回答1道数学题,答对得100元，限时5s，主游戏计时暂停\n");
    int job_earned = 0;
    srand(time(NULL));
      int num1, num2, correctAnswer;
      char op;
      num1 = rand() % 200 + 1;
      num2 = rand() % 200 + 1;
      int op_type = rand() % 3 + 1;
      if (op_type == 1) {
        op = '+';
        correctAnswer = num1 + num2;
      } else if (op_type == 2) {
        op = '-';
        if (num1<num2) {
          int a = num1;
          num1 = num2;
          num2 = a;
        }
        correctAnswer = num1 - num2;
      } else if (op_type == 3) {
        op = 'x';
        num1 = rand() % 20 + 1;
        num2 = rand() % 20 + 1;
        correctAnswer = num1 * num2;
      }
      printf("\n题目：%d%c%d=", num1, op, num2);
      fflush(stdout);
      int userAnswer;
      FD_ZERO(&set); // 限时输入代码（复用的）
      FD_SET(0, &set);
      timeout.tv_sec = 5;
      timeout.tv_usec = 0;
      int is_stdin = select(1, &set, NULL, NULL, &timeout);
      if (is_stdin != 0) {
        scanf("%d", &userAnswer);
      }
      while (getchar() != '\n')
        ;
      if (userAnswer == correctAnswer) {
        printf("答对了!+100元\n");
        job_earned += 100;
      } else {
        printf("\n答错或超时!答案是:%d\n", correctAnswer);
      }
      fflush(stdout);
    printf("打工结束，1s后继续");
    fflush(stdout);
    sleep(1);

    return job_earned;
}
