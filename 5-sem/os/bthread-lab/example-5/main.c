#include <setjmp.h>

typedef unsigned long int bthread_t;

typedef enum { __BTHREAD_READY = 0, __BTHREAD_BLOCKED, __BTHREAD_SLEEPING,
               __BTHREAD_ZOMBIE} bthread_state;

typedef struct {

} bthread_attr_t ;

typedef void* (*bthread_routine) (void*);

typedef struct {
    bthread_t tid;
    bthread_routine body;
    void* arg;
    bthread_state state;
    bthread_attr_t attr;
    char* stack;
    jmp_buf context;
    void* retval;
} __bthread_private ;