#include <stdio.h>
#include "./kernel/fork.c"

// 컴파일용 Entry point
int main()
{
    do_fork();
    return 0;
}