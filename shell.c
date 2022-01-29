#include "types.h"
#include "stat.h"
#include "user.h"
#include "parse.h"

int main(){
    //using shell to copy echo using read
    char* cptr = "";
    int gud = read(0,cptr,10);
    if(gud < 0){
        printf(2,"read Error\n");
        exit();
    }
    //printf(1,"%s\n",cptr);
    command cmd;
    gud = parse(cptr,&cmd);
    if(gud == -1){
        printf(2,"Parse Error\n");
        exit();
    }

    /* print out cmd code
    printf(1,"bg: %d\nargc: %d\n",cmd.bg,cmd.argc);
    for(int i=0; i<cmd.argc;++i){
        printf(1,"argv[%d]: %s\n",i,cmd.argv[i]);
    }
    printf(1,"input: %s\noutput: %s\n",cmd.input,cmd.output);
    //*/

    //fork code
    int pd = fork();
    if(pd < 0){
        printf(2,"Fork Error\n");
    }
    else if(pd == 0){
        gud = exec(cmd.argv[0],cmd.argv);
    }
    else{
        wait();
    }
    
    if(gud == -1){
        printf(2,"exec Error\n");
    }
    exit();
}