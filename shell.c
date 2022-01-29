#include "types.h"
#include "stat.h"
#include "user.h"
#include "parse.h"

int main(){
    char *cprt = "";
    char estr[] = "exit";
    int gud = 0;
    command cmd;
    while(1){
        gud = read(0,cprt,8);
        if(gud == -1){
            printf(2,"Error: read error\n");
            exit();
        }
        gud = parse(cprt,&cmd);
        if(gud == -1){
            printf(2,"Error: parse error\n");
            exit();
        }
        if(strcmp(estr,cmd.argv[0]) == 0){
            exit();
        }

        

        int forkch = fork();
        if(forkch == 0){
            gud = exec(cmd.argv[0],cmd.argv);
            if(gud == -1){
                printf(2,"Error: exec error\n");
            }
        }
        else if(forkch == -1){
            printf(2,"Error: fork error\n");
            exit();
        }
        else{
            gud = wait();
            if(gud == -1){
                printf(2,"Error: wait error\n");
            }
        }

        sleep(50);
    }
}