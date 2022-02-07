#include "types.h"
#include "stat.h"
#include "user.h"

int main(){
    printf(1,"This be the syscall function matey\n");
    sleep(10);
    sleep(10);
    int pid = getpid();
    int gud = calls(pid);
    if(gud == -1){
        printf(2,"Error: calls error");
    }
    else{
        printf(1,"%d\n");
    }
    exit();
}