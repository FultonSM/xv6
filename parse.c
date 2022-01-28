#include "parse.h"

int isspace(char c)
{
    return c==' ' || c=='\t' || c=='\n' || c=='\r';
}

char *strtok(char **s)
{
    if (!s) return 0;
    while (isspace(**s))
        (*s)++;
    if (**s == 0)
        return 0;
    char * r = *s;
    while (!isspace(**s) && **s)
        (*s)++;
    if (!**s)
        s = 0;
    else {
        **s=0;
        (*s)++;
    }
    return r;
}

int parse(char *line,command *cmd) 
{
    cmd->input = 0;
    cmd->output = 0;
    cmd->argc = 0;
    cmd->bg = 0;

    if (line[0] == '&') {
        cmd->bg = 1;
        line++;
    }

    char *s = line;
    char *p;
    while ((p=strtok(&s))) {
        if (*p == '#')
            break;
        else if (*p == '<') {
            if (p[1]) 
                cmd->input = p+1;
            else if (!(cmd->input = strtok(&s)))
                return -1;
        }        
        else if (*p == '>') {
            if (p[1])
                cmd->output = p+1;
            else if (!(cmd->output = strtok(&s)))
                return -1;
        }
        else if (cmd->argc >= NUMARGS)
            return -1;
        else
            cmd->argv[cmd->argc++] = p;
    }
    return 0;
}
