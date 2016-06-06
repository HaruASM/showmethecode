// ## monster의 개체 관리
// parallel 연습 

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define MON_IDLE                0
#define MON_DEAD                1
#define MON_ATTACKED            2

#define MONTYPE_COW             1
#define MONTYPE_WOLF            2
#define MONTYPE_TIGER           3
#define MONTYPE_DRAGON          4

#define MONSTER_MAX             3
#define MONSTER_TYPE_MAX        4
#define MONSTER_STATE_MAX       3

char* stateTable[MONSTER_STATE_MAX] = {
    "배회중", //MON_IDLE
    "(DIE)", // MON_DEAD
    "[싸움]" // MON_ATTACKED
};

char* names[MONSTER_TYPE_MAX] = {
    "Cow",
    "Wolf",
    "Tiger!",
    "Dragon!!"
};

struct monster_t {
  int hp;
  int ap;
  int gold;
  int state;
  char *name;
};

struct monster_t* monsters[MONSTER_MAX];

struct monster_t* createMonster(int type)
{
    struct monster_t *tmp; 
    tmp = (struct monster_t*)malloc(sizeof(struct monster_t));
    
    tmp->state = MON_IDLE;
    tmp->name = names[type-1];
    
    switch(type){
        
        case MONTYPE_COW :
        tmp->hp = 1;
        tmp->ap = 1;
        tmp->gold = 1;
        break;
        case MONTYPE_WOLF :
        tmp->hp = 10;
        tmp->ap = 10;
        tmp->gold = 10;
        break;
        case MONTYPE_TIGER :
        tmp->hp = 20;
        tmp->ap = 20;
        tmp->gold = 20;
        break;
        case MONTYPE_DRAGON :
        tmp->hp = 100;
        tmp->ap = 100;
        tmp->gold = 100;
        break;
        default :
        puts("error1");
    }
    
    return tmp;
}

void spawnMonster() 
{
    int i = 0, type;
    for(; i<MONSTER_MAX ; ++i){
         if( monsters[i] )
            continue;
         type = rand() % MONSTER_TYPE_MAX + 1; // 1~4
         monsters[i] = createMonster(type);
    }
}

void* keepSpawnMonster()
{
    while(1) {
        sleep(1);
        puts("keeping");
        spawnMonster();
    }
    
    
}


void* init()
{
    spawnMonster();
}

void draw()
{
    int i = 0;
    for(; i<MONSTER_MAX ; ++i){
        if( monsters[i] )
        printf("%d %s / %d / %s\n", i+1, 
          monsters[i]->name, 
          monsters[i] ->hp, 
          stateTable[monsters[i]->state] );
        else 
         printf("%d (nop)\n", i+1);
    }
    
}

void shutdown()
{
    int i = 0;
    for(; i<MONSTER_MAX ; ++i){
        free( monsters[i] );
        monsters[i] = 0;
    }
}

void run()
{
    int cnt = 5;
    pthread_t th1, th2; // 스레드 ID 
    void *th_res;
    int status;
    draw(); 
    if( (status = pthread_create(&th1, NULL, init, NULL )) != 0 ) // 1회성 작업
        puts("err1");
    
    if( (status = pthread_join(th1, &th_res)) != 0) // join
        puts("err2");

    if(th_res != NULL)
        puts("err3");

    if( pthread_create(&th2, NULL, keepSpawnMonster , NULL  ) != 0 ) // 유지 관리
        puts("err4");

    // loop procedure
    while(cnt--){
        sleep(1);
        draw();
    }
    
    if( pthread_join(th2, &th_res ) !=0 ) 
        puts("err5");
        
    shutdown();
    
}

void attack()
{
    ;
}

int main(){
    run();
    return 0;
}

