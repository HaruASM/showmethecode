#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int add(int a, int b)
{
    return a + b;
}

int sub(int a, int b)
{
    return a - b;
}

struct Calc {
   int (*fp[2])(int, int);
};

int executer(int (*fp)(int, int) , int a, int b)
{
    return fp(a, b);
}

int (*getFunc(struct Calc *c, int index))(int, int)
{
    return c->fp[index];
}

int main()
{
    struct Calc c = { { add, sub } };

    printf("%d\n", executer(getFunc(&c, 0), 10, 20));
    printf("%d\n", executer(getFunc(&c, 1), 10, 20));

    return 0;
}