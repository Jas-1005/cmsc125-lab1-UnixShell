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
#include "executor.h"
#include "command.h"
#define MAX_PATH_LENGTH 4096

bool is_bultin_command(Command cmd){
    if((strcmp(cmd.args[0], "exit") == 0) || (strcmp(cmd.args[0], "cd") == 0) || (strcmp(cmd.args[0], "pwd") == 0)) return true;
    return false;
}

void execute_user_command(Command cmd, int status){ 
    if (is_bultin_command(cmd)){
        if(strcmp(cmd.args[0], "exit") == 0){
            exit(0);
            /* 
                if command == "cd":
                    if no argument:
                        path = HOME environment variable
                    else:
                        path = args[1]
                    if chdir(path) fails:
                        print error
                continue shell loop
            */
        } else if (strcmp(cmd.args[0], "cd") == 0){
            char *path = cmd.args[1];
            if(path == NULL){
                path = getenv("HOME");
                fprintf(stderr, "cd: HOME not set\n");
            } else if(chdir(path) != 0){
                perror("mysh: cd error");
            }
            return;
        } else if (strcmp(cmd.args[0], "pwd") == 0) {
            char cwd[MAX_PATH_LENGTH];
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                printf("%s\n", cwd);
            } else {
                perror("getcwd error.");
            }
            return;
        }
    } else {
        if(cmd.background) cmd.args[sizeof(cmd.args)-1] = NULL; // remove & from args here
        pid_t process_id = fork();
        if (process_id < 0){  //OS cannot create new process if it reached max process limit
            perror("fork error.");
        } else if (process_id == 0){
            //child process
            for (int j = 0; cmd.args[j] != NULL; j++) {
                if (cmd.output_file != NULL && cmd.append) {
                    int fd = open(cmd.args[j+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    if (fd < 0) { perror("open"); exit(1); }
                    dup2(fd, STDOUT_FILENO);
                    close(fd);
                    cmd.args[j] = NULL; 
                } else if (cmd.output_file != NULL && !cmd.append ) { // Check args[j], not j+1
                    int fd = open(cmd.args[j+1], O_WRONLY | O_CREAT | O_APPEND, 0644);
                    if (fd < 0) { perror("open"); exit(1); }
                    dup2(fd, STDOUT_FILENO);
                    close(fd);
                    cmd.args[j] = NULL;
                } else if (cmd.input_file != NULL) { // Check args[j], not j+1
                    int fd = open(cmd.args[j+1], O_RDONLY);
                    if (fd >= 0) {
                        dup2(fd, STDIN_FILENO);
                        close(fd);
                    } 
                    cmd.args[j] = NULL;
                }
            }
            execvp(cmd.args[0], cmd.args); 
            perror("exec error");
            exit(127);
        } else {
            //parent process
            if (cmd.background) printf("[Process running in background, PID: %d]\n", process_id);
            else waitpid(process_id, &status, 0);
        }
    }
};