#include "types.h"
#include "stat.h"
#include "user.h"

int g = 42;
extern char _end;

int main(int argc, char *argv[])
{
    (void)argv;
    char *p = malloc(1);
    printf(1,"main=%p\n",&main);
    printf(1,"global=%p\n",&g);
    printf(1,"_end=%p\n",&_end);
    printf(1,"heap=%p\n",p);
    printf(1,"stack=%p\n",&argc);

    exit();
}
