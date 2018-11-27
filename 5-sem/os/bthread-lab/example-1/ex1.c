#include <stdio.h>
#include <setjmp.h>


static jmp_buf buf;

void dothings(){
    printf("Now I'm here\n");
    sleep(3);
    longjmp(buf, 42);
    printf("This is never printed\n");
}

int main(int argc, char** argv){
    if(!setjmp(buf)){
        dothings();
    } else {
        printf("Now I'm there!");
    }
    return 0;
}