#include "types.h"
#include "stat.h"
#include "user.h"
#include "parse.h"

int main(){
    //using shell to copy echo using read
    char* cptr = malloc(sizeof(char)*12);
    int gud = read(0,cptr,12);
    if(gud < 0){
        printf(2,"error: read error\n");
        exit();
    }
    command cmd;
    printf(1,"got it, :%s\n",cptr);
    gud = parse(cptr,&cmd);
    if(gud == -1){
        printf(2,"error: parse error\n");
        exit();
    }
    printf(1,"bg = %d\nargc = %d\n");
    exit();
}