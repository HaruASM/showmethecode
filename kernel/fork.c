#include <stdio.h>
#include "../include/linux/sched.h"
#include "../lib/users.h"

// 포크는 선언부는 어디에
// 누가 포크 보신분
void fork_o(void) {} 


void clone_o(){}

// 
void do_fork_o(){
    struct task_struct tmp;
    tmp._tmp_name = "do_fork_o";

    printf("%s\n", tmp._tmp_name);
}
