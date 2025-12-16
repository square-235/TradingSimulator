#include "../include/header.h"
#include <stdio.h>
#include <unistd.h>

void borrow(double *money,double *debt,const int num_input){

                    if (num_input>0 && num_input+*debt>1000) {
                        printf("\n输入金额大于最大借款金额，失败");
                        fflush(stdout);
                        sleep(1);
                    }
                    else if (*money+num_input<0) {
                        printf("\n现金不足，无法还款");
                        fflush(stdout);
                        sleep(1);
                    }
                    else if (*debt+num_input<0) {
                        printf("\n输入金额大于欠款，失败");
                        fflush(stdout);
                        sleep(1);
                    }
                    else {
                        *money+=num_input;
                        *debt+=num_input;                    
                    }
}