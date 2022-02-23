#ifdef XV6
    #include "types.h"
    #include "user.h"
    #define puts(x) printf(1,"%s\n",x)
#else
    #include <stdio.h>
#endif

int shift;
unsigned password_hash;

static unsigned hash(char *str)
{
    unsigned hash = 5381;
    int c;
    while ((c = (unsigned char)*str++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}

int check(char *password)
{
    return hash(password) == password_hash;
}

void decrypt(char *password,char *message)
{
    unsigned code = hash(password);
    while (*message) {
        *message ^= code;
        code = (code << shift) | (code >> (32-shift));
        message++;
    }
}

void setup(int,unsigned);

int main(int argc,char **argv)
{
    static char message[] = {0xd9,0x24,0xad,0xe7,0xa2,0x61,0xa0,0xf9,0xeb,0x2f,0xe6,0xff,0xae,0x38,0xae,0xfe,0xae,0x32,0xac,0xea,0xfc,0x35,0xe0};
    setup(8,0x41c18b8e);
    
    if (argc < 2)
        puts("usage: decrypt password");
    else if (!check(argv[1]))
        puts("wrong password");
    else {
        decrypt(argv[1],message);
        puts(message);
    }

    #ifdef XV6
        exit();
    #endif
}
