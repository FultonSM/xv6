#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf(1,"usage: cpu <string>\n");
        return 0;
    }

    while (1) {
        sleep(100);
        printf(1,"%s\n",argv[1]);
    }
    exit();
}
