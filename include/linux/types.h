//## Linux/include/linux/types.h ##
#ifndef _LINUX_TYPES_H_O
#define _LINUX_TYPES_H_O



// Linux/include/uapi/asm-generic/posix_types.h 여기에서
typedef int             __kernel_pid_t;

typedef __kernel_pid_t          pid_t;

// http://lxr.free-electrons.com/source/include/linux/types.h#L185
// # list 관리 구조체 집합
struct list_head {
        struct list_head *next, *prev;
};

struct hlist_node {
    struct hlist_node *next, **pprev;
};








#endif /* _LINUX_TYPES_H_O */