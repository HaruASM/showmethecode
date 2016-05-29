// ## Linux/include/linux/sched.h ##
// ## 태스크 관리 관련 자료구조

#ifndef _LINUX_SCHED_H
#define _LINUX_SCHED_H

#include "./types.h" // pid_t 


// Runqueue
struct rq {};

// FIFO & RR
struct rt_rq {};

// DEADLINE
struct dl_rq {};

// 
struct sched_domain ;

// CFS
struct cfs_rq {};


// 67페이지  태스크 구조체
struct task_struct {
    
char* _tmp_name; // 디버그용..
    
//# 가. task identification    
pid_t pid;  //태스크 ID
pid_t tgid; //그룹 ID
    
    
//# 나. state
#define TASK_RUNNING            0
#define TASK_INTERRUPTIBLE      1
#define TASK_UNINTERRUPTIBLE    2
//#define __TASK_STOPPED          4 // 원본
//#define __TASK_TRACED           8 // 원본
//#define TASK_STOPPED            (TASK_WAKEKILL | __TASK_STOPPED) // 원본
//#define TASK_TRACED             (TASK_WAKEKILL | __TASK_TRACED)  // 원본
#define TASK_STOPPED            4 // oo
#define TASK_TRACED             8 // oo

/* in tsk->exit_state */
#define EXIT_DEAD               16
#define EXIT_ZOMBIE             32
//#define EXIT_TRACE              (EXIT_ZOMBIE | EXIT_DEAD) // 원본
/* in tsk->state again */
#define TASK_DEAD               64
#define TASK_WAKEKILL           128
#define TASK_WAKING             256
#define TASK_PARKED             512
#define TASK_NOLOAD             1024
#define TASK_STATE_MAX          2048



//# 다. task relationshpip

//# 라. scheduling information
    
//# 마. signal information

//# 바. memory information

//# 사. file information

//# 아. thread structure

//# 자. time information

//# 차. format

//# 카. resource limits

};

#endif /* _LINUX_SCHED_H */