// ## Linux/include/linux/sched.h ##
// ## 태스크 관리 관련 자료구조

#ifndef _LINUX_SCHED_H_O
#define _LINUX_SCHED_H_O

#include "./types.h" // pid_t 

/*  비트마스킹용
 * 
 * 
 */
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

// http://lxr.free-electrons.com/source/include/linux/sched.h#L290
#define set_task_state(tsk, state_value)                      \
        (tsk)->state = (state_value);
        
#define set_current_state(state_value)            \
        current->state = (state_value);





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


//## Process Descriptor
// 67페이지  태스크 구조체, 
// http://lxr.free-electrons.com/source/include/linux/sched.h#L1394
struct task_struct {

char* _tmp_name; // 디버그용..


//# 가. task identification    
pid_t pid;  //태스크 PID
pid_t tgid; //스레드 그룹 리더 PID

    
    
//# 나. state
// state는 runnability관련, exit_state는 exiting관련
volatile long state; // -1unrunable, 0 runnable, 0> stopped

int exit_state; // EXIT_DEAD ,EXIT_ZOMBIE
int exit_code; // exit_signal



//# 다. task relationshpip

struct list_head tasks;

//http://lxr.free-electrons.com/source/include/linux/sched.h#L1514
struct task_struct *real_parent; // 생성 부모, 없으면 init(1)이 부모
struct task_struct *parent; //종료시 signal 받을 부모
struct list_head children;
struct list_head sibling;

struct task_struct *group_leader;

// PID hash table 링크
//struct pid_link pids[PIDTYPE_MAX];
struct list_head thread_group;
struct list_head thread_node;

//# 라. scheduling information
    
//# 마. signal information

//# 바. memory information

//# 사. file information

//# 아. thread structure

//# 자. time information

//# 차. format

//# 카. resource limits

};

//http://lxr.free-electrons.com/source/include/linux/sched.h#L2454
extern struct task_struct init_task; // process 0, swapper

#endif /* _LINUX_SCHED_H_O */