#include "types.h"
#include "stat.h"
#include "user.h"
#include "parse.h"
#include "fcntl.h"

int main(){
    char* cptr = malloc(1024);
    int gud = 0;

    while(1){    
        gud = read(0,cptr,1024);    //read line

        //read error check
        if(gud < 0){
            printf(2,"Error: read error\n");
            exit();
        }
        
        //parsing the line
        command cmd;
        gud = parse(cptr,&cmd);

        //parse error check
        if(gud == -1){
            printf(2,"error: parse error\n");
            exit();
        }

        //check if command is exit
        if(strcmp(cmd.argv[0],"exit") == 0){
            break;
        }
        /*
        printf(1,"bg: %d\nargc: %d\n",cmd.bg,cmd.argc);
        for(int i=0; i<cmd.argc;++i){
            printf(1,"argv[%d]: %s\n",i,cmd.argv[i]);
        }
        printf(1,"input: %s\noutput: %s\n\n",cmd.input,cmd.output);
        //*/

        //calling fork
        gud = fork();

        //fork error check
        if(gud == -1){
            printf(2,"Error: fork error\n");
            exit();
        }
        
        //fork child check
        if(gud > 0){
            gud = wait();
            //wait error check
            if(gud == -1){
                printf(2,"Error: wait error\n");
                exit();
            }
        }
        else{
            //if child, execute process
            gud = exec(cmd.argv[0],cmd.argv);
            exit();
        }
    }

    exit();
}