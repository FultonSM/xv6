#include "types.h"
#include "stat.h"
#include "user.h"
//#include "parse.h"

int main(){
    //using shell to copy echo using read
    char* cptr = malloc(sizeof(char)*10);
    int gud = read(0,cptr,10);
    if(gud < 0){
        printf(2,"error, idk\n");
        exit();
    }
    printf(1,cptr);
    printf(1,"\n\n");
    exit();
}