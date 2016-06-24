#include "./users.h"

void fork_o(void) 
{
    printf("-fork_o");
    do_fork_o();
    
    puts("");
} 

void clone_o()
{
    printf("-clone_o");
    
    do_fork_o();
    puts("");
}

