/**
 * A shell is a command-line interpreter that reads user input and
executes commands.

Build a Unix shell ( mysh ) that supports:
• Interactive command execution with prompt
• Built-in commands: exit, cd, pwd
• External command execution via fork() and exec()
• I/O redirection: > (truncate), » (append), < (input)
• Background execution: &

Shell follows REPL pattern (Read, Parse, Execute, Loop)

PSEUDOCODE
while (true):
    print prompt
    if fgets == NULL → break
    strip newline
    parse input
    if builtin → handle
    else:
        fork
        child → execvp
        parent → wait or not

References: 
Advanced Programming in the UNIX Environment by W. Richard Stevens
stackoverflow
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h> 
#include <fcntl.h> //handles file control operations  
#include <signal.h>
#include "parser.h"
#include "executor.h"

#define MAX_COMMAND_LENGTH 1024
// #define MAX_ARGS 100
#define MAX_PATH_LENGTH 4096

static void sig_int(int signo) {
    printf("\n");
}

int main(){
    Command cmd;
    char input[MAX_COMMAND_LENGTH];
    int status = 0;
    int job_id = 1;

    signal(SIGINT, sig_int); //register signal handler for SIGINT
    while (1){
        
        while(waitpid(-1, NULL, WNOHANG) > 0);
        //PROMPT
        printf("\nmysh> ");
        fflush(stdout);

        //READ
        if (fgets(input, sizeof(input), stdin) == NULL){
            printf("\n");
            break; //handle EOF (Ctrl+D)
        }

        input[strcspn(input, "\n")] = 0; //strip newline character from input string

        parse_user_input(input, &cmd);

        if (cmd.command == NULL) {
            free_memory(&cmd);
            continue; //just skip if no command is entered
        }

        execute_user_command(cmd, &status, &job_id);
        free_memory(&cmd);

        // if (signal(SIGINT, sig_int) == SIG_ERR){
        //     perror("signal error.");
        // }
        }
    return(status);
}
