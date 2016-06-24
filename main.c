#include <stdlib.h>
#include <stdio.h>
#include "./lib/users.h"

#include <sched.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

struct alarm {
    int sec;
    char message[64];
};

void *alarm_th (void *arg)
{
    struct alarm *al = (struct alarm*)arg;
    int status;
    
    status = pthread_detach(pthread_self());
    if( status != 0)
        puts("err");
    sleep(al->sec);
    printf("%d %s\n",al->sec, al->message);
    free(al);
    return NULL;
}

// 컴파일용 Entry point
int main()
{
    puts("main");
    fork_o();
    clone_o();
    
    int status;
    char in[128];
    struct alarm *al;
    pthread_t th;
    
    while(1){
        printf(">> ");
        if(fgets(in, sizeof(in), stdin)==NULL) exit(0);
        if(strlen(in) < 2) continue;
    
    al = (struct alarm*) malloc(sizeof(struct alarm));
    if( al == NULL)
     puts("err");
    
    if(sscanf(in, "%d %64[^\n]", &al->sec, al->message)<2) {
        fprintf(stderr, "what")    ;
        free(al);
    } else {
        status = pthread_create(&th,NULL,alarm_th, al );
        if( status != 0)
            puts("err");
    }
    }
    
    return 0;
}