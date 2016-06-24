#include <stdio.h>
#include "../include/linux/sched.h"
#include "../lib/users.h"

// 포크는 선언부는 어디에
// 누가 포크 보신분

static struct task_struct *copy_process()
{
    printf("-copy_process");
    // http://lxr.free-electrons.com/source/kernel/fork.c#L1253
    
}

// fork -> clone -> do_fork
pid_t do_fork_o()
{
    printf("-do_fork_o");
    // 책 60페이지
    // http://lxr.free-electrons.com/source/kernel/fork.c#L1702
    struct task_struct *p;
    
    //p = copy_process();

    //p._tmp_name = "do_fork_o";
    //printf("%s\n", p._tmp_name);
}

// 1790라인 
pid_t kernel_thread()
{
    printf("-kernel_thread");
    
}