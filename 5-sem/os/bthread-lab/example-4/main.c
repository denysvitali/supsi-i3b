#include <stdio.h>
#include <setjmp.h>

#define CUSHION_SIZE 1000
#define save_context(CONTEXT) setjmp(CONTEXT)
#define restore_context(CONTEXT) longjmp(CONTEXT, 1)

typedef enum { __BTHREAD_UNINITIALIZED, __BTHREAD_READY } bthread_state;
typedef void * (*bthread_routine) (void*);

void create_cushion_and_call(bthread_routine fn, bthread_state* state);

void* bthread1(void* arg);
void* bthread2(void* arg);
void* bthread3(void* arg);

jmp_buf bthread_1_buf, bthread_2_buf, bthread_3_buf;
bthread_state bthread1_state = __BTHREAD_UNINITIALIZED;
bthread_state bthread2_state = __BTHREAD_UNINITIALIZED;
bthread_state bthread3_state = __BTHREAD_UNINITIALIZED;

void create_cushion_and_call(bthread_routine fn, bthread_state* state){
    char cushion[CUSHION_SIZE];
    cushion[CUSHION_SIZE-1] = cushion[0];
    *state = __BTHREAD_READY;
    fn(NULL);
}

void* bthread1(void* arg){
    volatile int i;
    for(i=0; i< 10000; i++){
        printf("BThread1, i=%d\n", i);
        /* Yield to next bthread */
        if(!save_context(bthread_1_buf)) {
            if(bthread2_state == __BTHREAD_UNINITIALIZED){
                create_cushion_and_call(bthread2, &bthread2_state);
            } else {
                restore_context(bthread_2_buf);
            }
        }
    }
}

void* bthread2(void* arg){
    volatile int i;
    for(i=0; i< 10000; i++){
        printf("BThread2, i=%d\n", i);
        /* Yield to next bthread */
        if(!save_context(bthread_2_buf)) {
            if(bthread3_state == __BTHREAD_UNINITIALIZED){
                create_cushion_and_call(bthread3, &bthread3_state);
            } else {
                restore_context(bthread_3_buf);
            }
        }
    }
}

void* bthread3(void* arg){
    volatile int i;
    for(i=0; i< 10000; i++){
        printf("BThread3, i=%d\n", i);
        /* Yield to next bthread */
        if(!save_context(bthread_3_buf)) {
            restore_context(bthread_1_buf);
        }
    }
}

void main(){
    create_cushion_and_call(bthread1, &bthread1_state);
}