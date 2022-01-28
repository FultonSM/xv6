// shell command parser

// similar (but not identical) to POSIX function of the same name
// accepts a char pointer by reference
// advances the pointer (so it can be called repeatedly)
// skips over whitespace
// returns a pointer to non-whitespace characters
// nul-terminates non-whitespace characters
char *strtok(char **s);

#define NUMARGS 10
typedef struct command {
    int bg;                 // is this a "background" command?
    int argc;               // number of arguments (not including I/O)
    char *argv[NUMARGS];    // the arguments (each nul-terminated)
    char *input;            // input filename, or NULL
    char *output;           // output filename, or NULL
} command;

// accepts a pointer to (nul-terminated) input string to be parsed
// requires a reference to a command structure which is filled out
// returns 0 on success, -1 on parse error
int parse(char *line,command *cmd);