
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>


#define BUF_MAX 1024 
#define LISTENQ 5
#define THREAD_NUM 10
#define CLIENT_MAX 10
#define PORT 3000

void *func(void *arg);
void broadcasting(char* message, int len);


int res = 0;
int cliCnt = 0; 


pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int main()
{
    
    struct sockaddr_in serv_addr, cli_addr;
    int listen_sock, cli_sock[CLIENT_MAX];
    int addrlen = sizeof(serv_addr);
    int i, status; 
    pthread_t tid[THREAD_NUM];
    pid_t pid;
    
    if(pthread_mutex_init(&lock, NULL))
        perror("err 0");

    if( (listen_sock = socket(PF_INET, SOCK_STREAM, 0)) < 0 ){
        perror("err 1");
        exit(0);
    }
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(PORT);
    
    if( bind(listen_sock, (struct sockaddr *)&serv_addr, 
      sizeof(serv_addr)) <0 ) {
        perror("err 2");
        exit(0);
    }
    
    puts("server open");
    
    listen(listen_sock, LISTENQ );
    
    while(1) {
        
        pthread_mutex_lock(&lock);
        cli_sock[cliCnt] = accept(listen_sock, (struct sockaddr *)&cli_addr,
            &addrlen);
        if(cli_sock[cliCnt] < 0){
            perror("err 3");
            exit(0);
        }
        
        if(  (status = pthread_create( &tid[cliCnt], NULL, &func,
            (void *)&cli_sock[cliCnt])) != 0 ) {
                printf("%d thread err 4: %s\n", cliCnt, strerror(status));
                exit(0);
            }
        
        pthread_join(tid[cliCnt], NULL);
        cliCnt++;
        // 
    }

    puts("yep");
    
    return 0;
}

char aa[20] = "hello";
char bb[20] = "humi";

void *func(void *arg)
{
    int sock = (int) *((int*)arg);
    int i , buf = 0 ;
    

    read(sock, &buf, 4);
    printf("-cli : %c\n", buf);
    pthread_mutex_lock(&lock);
    res += buf;
    
    // for( i=0, i < cliCnt ; ++i ){
    //     ;
    // }
    
    printf("=res : %d\n", res);
    pthread_mutex_unlock(&lock);
    
    write(sock, aa, 20);

    close(sock);
}


void broadcasting(char* message, int len);