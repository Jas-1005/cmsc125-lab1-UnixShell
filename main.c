/**
Build a Unix shell ( mysh ) that supports:
• Interactive command execution with prompt
• Built-in commands: exit, cd, pwd
• External command execution via fork() and exec()
• 1/O redirection: > (truncate), » (append), < (input)
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

References: Advanced Programming in the UNIX Environment by W. Richard Stevens
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h> 
#include <fcntl.h> //handles file control operations  
#include <signal.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 100
static void sig_int(int);

int main(){

    char input[MAX_COMMAND_LENGTH];
    pid_t process_id;
    int status;

    while (1){
        printf("mysh> ");
        fflush(stdout);
        //READ
        if (fgets(input, sizeof(input), stdin) == NULL){
            break; //EOF

        input[strcspn(input, "\n")] = 0;

        //PARSE
        //The shell parses this null-terminated C string and breaks it up into separate command-line arguments for the command.

        int i = 0; //i is the index of the last argument
        int background = 0;
        char *args[MAX_ARGS], *ptr = strtok(input, " ");
        while (ptr != NULL){
            args[i++] = ptr;
            ptr = strtok(NULL, " ");
        }
        args[i] = NULL; //null terminate the args array

        if (args[0] == NULL) {
            continue; //just skip if no command is entered
        }
        //if the last character contains & -> background execution
        if (i > 0 && strcmp(args[i-1], "&") == 0){
            background = 1;
            args[i-1] = NULL; //remove & from args
        }

        if (signal(SIGINT, sig_int) == SIG_ERR){
            perror("signal error.");
        }
        // handle EOF (Ctrl+D)

        // read command line input
        if ((process_id = fork()) < 0){  //OS cannot create new process if it reached max process limit
            status = -1;
            perror("fork error.");
        } else if (process_id == 0){
            //child process
            char *argv[] = {"/bin/sh", "-c", input, NULL}; //passes the information to argument
            execv("/bin/sh", argv); //execv replaces the current process image with a new process image
            perror("exec error.");
            exit(127); //exec error: command cannot be executed
        } else {
            while (waitpid(process_id, &status, 0) < 0) {
                if (errno != EINTR) {
                    perror("waitpid error.");
                    status = -1;
                    break;
                }
            }
            printf("mysh> ");
        }
        }
    }
    return(status);
}

void sig_int(int signo) {
    printf("\nmysh> ");
}
/**
 * while (fgets(input, sizeof(input), stdin) != NULL) {
 *      if (input[strlen(input) - 1] == "\n")
 *          input[strlen(input) - 1] == 0; //replace newline with null
 *      
 *  
 * }
 *
 */
