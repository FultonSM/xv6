#include "types.h"
#include "stat.h"
#include "user.h"
#include "spinlock.h"

int main(int argc, char *argv[]){
    //printf(1,"This be the syscall function matey\n");
    if(argc > 2){
        printf(1,"usage: syscalls <pid>\n");
        return 0;
    }
    else if(argc == 2){
        int pid = atoi(argv[1]);
        int syscalls = calls(pid);
        if(syscalls == -1){
            printf(2,"Error: process does not exist\n");
            exit();
        }
        printf(1,"%d\n",syscalls);
    }
    else{
        for(int i=1;i<=1000;++i){
            int syscalls = calls(i);
            if(syscalls != -1){
                printf(1,"%d: %d\n",i,syscalls);
            }
        }
    }
    exit();
}