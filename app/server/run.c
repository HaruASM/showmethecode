#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <pthread.h>

typedef struct alarm_tag {
 int sec;
 char message[64];
}alarm_t;

void *func(void *arg)
{
  alarm_t *alm = (alarm_t*)arg;
  
  int status;
  status = pthread_detach (pthread_self());
  
  if(status != 0)
    puts("err2");
  sleep(alm->sec);
  printf("%d %s\n", alm->sec, alm->message);
  free(alm);

  return NULL;
}

int main(int c, char* argv)
{
  int status;
  char line[1024];
  alarm_t *alm;
  pthread_t th;
  
  while(1){
    if(fgets(line,sizeof(line),stdin)==NULL)  exit(0);
    if(strlen(line)<=1) continue;
    
    alm = (alarm_t*)malloc(sizeof(alarm_t));
    
    sscanf(line,"%d %64[\n]", &alm->sec, alm->message);
    
    status = pthread_create(
      &th, NULL, func, alm);
  }
    

  return 0;
}