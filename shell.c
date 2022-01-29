#include "types.h"
#include "stat.h"
#include "user.h"
#include "parse.h"

int main(){
    //using shell to copy echo using read
    char* cptr = "mem A";
    command cmd;
    int gud = parse(cptr,&cmd);
    if(gud == -1){
        printf(2,"Parse Error\n");
    }

    //* print out cmd code
    printf(1,"bg: %d\nargc: %d\n",cmd.bg,cmd.argc);
    for(int i=0; i<cmd.argc;++i){
        printf(1,"argv[%d]: %s\n",i,cmd.argv[i]);
    }
    printf(1,"input: %s\noutput: %s\n",cmd.input,cmd.output);
    //*/
    
    gud = exec(cmd.argv[0],cmd.argv);
    if(gud == -1){
        printf(2,"exec Error\n");
    }
    exit();
}