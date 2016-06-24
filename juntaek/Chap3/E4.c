#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <linux/unistd.h>
#include <sys/stat.h>
#include <errno.h>

typedef struct statstruct_proc {
	int           pid;                      /** The process id. **/
	char          exName [_POSIX_PATH_MAX]; /** The filename of the executable **/
	char          state; /** 1 **/          /** R is running, S is sleeping, 
	D is sleeping in an uninterruptible wait,
	Z is zombie, T is traced or stopped **/
	
	//unsigned      euid,                      /** effective user id **/
	//egid;                      /** effective group id */					     
	int           ppid;                     /** The pid of the parent. **/
	int           pgrp;                     /** The pgrp of the process. **/
	int           session;                  /** The session id of the process. **/
	int           tty;                      /** The tty the process uses **/
	int           tpgid;                    /** (too long) **/
	unsigned int	flags;                    /** The flags of the process. **/
	unsigned int	minflt;                   /** The number of minor faults **/
	unsigned int	cminflt;                  /** The number of minor faults with childs **/
	unsigned int	majflt;                   /** The number of major faults **/
	unsigned int  cmajflt;                  /** The number of major faults with childs **/
	unsigned int           utime;                    /** user mode jiffies **/
	unsigned int           stime;                    /** kernel mode jiffies **/
	int		cutime;                   /** user mode jiffies with childs **/
	int           cstime;                   /** kernel mode jiffies with childs **/
	int           counter;                  /** process's next timeslice **/
	int           priority;                 /** the standard nice value, plus fifteen **/
} procinfo;

int get_proc_info(pid_t pid, procinfo * pinfo)
{
	char szFileName [_POSIX_PATH_MAX],
	szStatStr [2048],
	*s, *t;
	FILE *fp;
	struct stat st;
	
	if (NULL == pinfo) {
		errno = EINVAL;
		return -1;
	}

	sprintf (szFileName, "/proc/%u/stat", (unsigned) pid);
	
	if (-1 == access (szFileName, R_OK)) {
		return (pinfo->pid = -1);
	} /** if **/
	
	/*
	if (-1 != stat (szFileName, &st)) {
		pinfo->euid = st.st_uid;
		pinfo->egid = st.st_gid;
	} else {
		pinfo->euid = pinfo->egid = -1;
	}
	*/


	if ((fp = fopen (szFileName, "r")) == NULL) {
		return (pinfo->pid = -1);
	} /** IF_NULL **/

	if ((s = fgets (szStatStr, 2048, fp)) == NULL) {
		fclose (fp);
		return (pinfo->pid = -1);
	}
	
	//printf("PROC INFO = %s", szStatStr);
	
	/** pid **/
	sscanf (szStatStr, "%u", &(pinfo->pid));
	s = strchr (szStatStr, '(') + 1;
	t = strchr (szStatStr, ')');
	strncpy (pinfo->exName, s, t - s);
	pinfo->exName [t - s] = '\0';
	
	sscanf (t + 2, "%c %d %d %d %d %d %u %u %u %u %u %d %d %d %d %d %d",
	/*               1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33*/
	&(pinfo->state), //1
	&(pinfo->ppid), //2
	&(pinfo->pgrp), //3
	&(pinfo->session), //4
	&(pinfo->tty), //5
	&(pinfo->tpgid), //6
	&(pinfo->flags), //7
	&(pinfo->minflt),
	&(pinfo->cminflt),
	&(pinfo->majflt),
	&(pinfo->cmajflt), //11
	&(pinfo->utime), //12
	&(pinfo->stime), //13
	&(pinfo->cutime),
	&(pinfo->cstime),
	&(pinfo->counter),
	&(pinfo->priority)
	);
	fclose (fp);
	return 0;
}



void *t_function(void *data)
{
	procinfo *pinfo= malloc(sizeof(procinfo));
	
	int id, ret=0;
	volatile int result=0;
	int i=0;
	pthread_t t_id;
	id=*((int *)data);
	printf("TGID(%d), PID(%d), pthread_self(%d) : Thread Number = %d \n", getpid(), syscall(__NR_gettid), pthread_self(), id);
	
	

	while(1){
		sleep(1);
		
		for(i=0; i< 100000000; i++)
			result+=i;

		get_proc_info(syscall(__NR_gettid), pinfo);
		//get_proc_info(getpid(), pinfo);
		printf("PID(%d) utime = %u stime = %u PROCESS STATE = %c NAME = %s \n", pinfo->pid, pinfo->utime, pinfo->stime, pinfo->state, pinfo->exName);

	}

}

int main(void)
{
	int pid, status;
	int ret=0;

	int a=1, b=2;

	int i;

	pthread_t p_thread[10];

   if((pid=fork())< 0){ 
	   printf("fork error \n");
      exit(-2);
   }else if(pid==0){
		for(i=0; i<7; i++)
			if((pid=pthread_create(&p_thread[i], NULL, t_function, (void*)&a))<0){
				perror("thread create error: ");
				exit(1);
			}
  	}else{
		for(i=0; i<3; i++)
			if((pid=pthread_create(&p_thread[i], NULL, t_function, (void*)&b))<0){
				perror("thread create error: ");
				exit(1);
			}
	  	sleep(2);
	}

	pthread_join(p_thread[0], (void **)&status);
	printf("pthread_join(%d) \n", status);
	pthread_join(p_thread[1], (void **)&status);
	printf("pthread_join(%d) \n", status);

	return 0;
}
		

