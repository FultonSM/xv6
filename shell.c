#include "types.h"
#include "stat.h"
#include "user.h"
#include "parse.h"
#include "fcntl.h"

int main(){
    char* cptr = malloc(1024);
    int gud = 0;
    int pid = 0;
    int bkgd[100];
    int bgps = -1;

    while(1){    
        //shell feed line print
        printf(1,"shell>");

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
            //if there is a background process
            if(bgps != -1){
                //kill off all bg processes
                for(; bgps>=0; --bgps){
                    gud = kill(bkgd[bgps]);
                    //kill error check
                    if(gud == -1){
                        printf(2,"Error: kill error\n");
                        exit();
                    }
                }
                
            }
            break;
        }
        
        //check if command is bg
        if(strcmp(cmd.argv[0],"bg") == 0){
            for(int i=0; i<=bgps;++i){
                printf(1,"%d ",bkgd[i]);
            }
            printf(1,"\n");
        }

        //check if command is wait
        if(strcmp(cmd.argv[0],"wait") == 0){
            gud = wait();
            //wait error check
            if(gud == -1){
                printf(2,"Error: wait error\n");
                exit();
            }
        }
        //we now know that we have a file to run
        
        //* print parse "function"
        printf(1,"bg: %d\nargc: %d\n",cmd.bg,cmd.argc);
        for(int i=0; i<cmd.argc;++i){
            printf(1,"argv[%d]: %s\n",i,cmd.argv[i]);
        }
        printf(1,"input: %s\noutput: %s\n\n",cmd.input,cmd.output);
        //*/



        //calling fork
        pid = fork();

        //fork error check
        if(pid == -1){
            printf(2,"Error: fork error\n");
            exit();
        }
        
        //* fork exec "function"
        //fork child check
        if(pid > 0){
            //checking if background process
            if(cmd.bg == 0){
                gud = wait();
                //wait error check
                if(gud == -1){
                    printf(2,"Error: wait error\n");
                    exit();
                }
            }
            else{
                //save background process
                ++bgps;
                bkgd[bgps] = pid;
                //printf(1,"bkgrd=%d\n",bkgd);
            }
        }
        else{
            //if child, execute process
            //checking for input
            if(cmd.input != 0){
                //close standard in
                gud = close(0);

                //close error check
                if(gud == -1){
                    printf(2,"Error: close error\n");
                    exit();
                }

                //open file
                gud = open(cmd.input,O_CREATE | O_RDONLY);
                //open error check
                if(gud == -1){
                    printf(2,"Error: open error\n");
                    exit();
                }
            }

            //checking for output
            if(cmd.output != 0){
                //close standard out
                gud = close(1);
                //close error check
                if(gud == -1){
                    printf(2,"Error: close error\n");
                    exit();
                }

                //open file
                gud = open(cmd.output,O_CREATE | O_WRONLY);
                //open error check
                if(gud == -1){
                    printf(2,"Error: open error\n");
                    exit();
                }
            }

            //execute the file
            gud = exec(cmd.argv[0],cmd.argv);
            exit();
        }
        //*/
    }

    exit();
}