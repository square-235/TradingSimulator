#include "../include/header.h"
#include <stdio.h>
#include <unistd.h>
bool autoInvest(double money, int auto_invest_amount, bool auto_invest) {//自动投资
  getchar();
  if (auto_invest == false) {
    if (money >= auto_invest_amount) {
      printf("\n智能投资：每次刷新将自动把500元平均投入到5只股票（四舍五入）,"
             "资金不足自动关闭，无需手动操作，是否开启？(Y/n)");
      char confirm;
      scanf("%c", &confirm);
      if (confirm == 'Y' || confirm == '\n') {
        auto_invest = true;
        printf("\n智能投资已开启，");
      } else {
        printf("未进行更改，");
      }
    } else {
      printf("\n资金不足，无法开启，\n");
    }
  } else {
    printf("关闭智能投资？(Y/n)");
    char confirm;
    scanf("%c", &confirm);
    if (confirm == 'Y' || confirm == '\n') {
      auto_invest = false;
      printf("\n智能投资已关闭,");
    }
  }
  printf("按回车键继续......");
  sleep(1);
  fflush(stdout);
  getchar();
  return auto_invest;
}
