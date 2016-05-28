#include <stdio.h>
#include "../include/linux/sched.h"

// 포크는 선언부는 어디에
// 누가 포크 보신분
void fork(void) {} 

void clone(){}

// 
void do_fork(){
    struct task_struct _tmp;
    _tmp.__tmp_name = "do_fork";
    printf("%s\n", _tmp.__tmp_name);
}
