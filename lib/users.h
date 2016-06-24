// ## 위치 불명 선언부들들 임시 위치
// ## user.c에 구현
#ifndef _LIB_USERS_H
#define _LIB_USERS_H

#include <stdio.h>
#include "../include/linux/sched.h"

void fork_o();
void clone_o();
pid_t do_fork_o(); // fork.c 구현

#endif /* _LIB_USERS_H */