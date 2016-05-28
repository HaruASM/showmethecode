// ## 태스크 관리 관련 자료구조

// 아는거 일단 적고 이후 필요에 따라 정리하겠슴돠

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
    
char* __tmp_name; // 디버그용..
    
//# 가. task identification    
    
//# 나. state

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