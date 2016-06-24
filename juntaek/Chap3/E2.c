#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/unistd.h>

void *t_function(void *data)
{
	int id, ret=0;
	int i=0;
	pthread_t t_id;
	id=*((int *)data);
//	printf("TGID(%d), PID(%d), pthread_self(%d) : Child \n", getpid(), syscall(__NR_gettid), pthread_self());

	if(ret=execl("/usr/bin/whoami","", (char *)0)==-1)
			printf("Error in exec\n"); 
}

int main(void)
{
	int pid, status;
	int ret=0;

	int a=1, b=2;
	pthread_t p_thread[2];
	printf("before pthread_create \n\n");
	
	if((pid=pthread_create(&p_thread[0], NULL, t_function, (void*)&a))<0){
		perror("thread create error: ");
		exit(1);
	}

	if((pid=pthread_create(&p_thread[1], NULL, t_function, (void*)&b))<0){
		perror("thread create error: ");
		exit(1);
	}


	pthread_join(p_thread[0], (void **)&status);
	printf("pthread_join(%d) \n", status);
	pthread_join(p_thread[1], (void **)&status);
	printf("pthread_join(%d) \n", status);

	return 0;
}
		

