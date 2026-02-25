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

bool is_builtin_command(Command cmd){
    if((strcmp(cmd.args[0], "exit") == 0) || (strcmp(cmd.args[0], "cd") == 0) || (strcmp(cmd.args[0], "pwd") == 0)) return true;
    return false;
}

void file_redirection(int fd, char file_type[]){
    if(strcmp(file_type, "output") == 0){
        if (fd < 0) { perror("open"); exit(1); }
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }

    if (strcmp(file_type, "input") == 0){
        if (fd < 0) { perror("open"); exit(1); }
        dup2(fd, STDIN_FILENO);
        close(fd);
    }
}

void execute_user_command(Command cmd, int status){ 
    if (is_builtin_command(cmd)){
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
                if (path == NULL) {
                    fprintf(stderr, "cd: HOME not set\n");
                    return;
                }
            }
            if(chdir(path) != 0) perror("mysh: cd error");
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
        pid_t process_id = fork();
        if (process_id < 0){  //OS cannot create new process if it reached max process limit
            perror("fork error.");
        } else if (process_id == 0){
        //child process
            if (cmd.output_file != NULL && !cmd.append) {
                int fd = open(cmd.output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                file_redirection(fd, "output");
            } else if (cmd.output_file != NULL && cmd.append ) { // Check args[j], not j+1
                int fd = open(cmd.output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
                file_redirection(fd, "output");
            }
            if (cmd.input_file != NULL) { // Check args[j], not j+1
                int fd = open(cmd.input_file, O_RDONLY);
                file_redirection(fd, "input");
            }
            execvp(cmd.args[0], cmd.args); 
            exit(127);
        } else {
            //parent process
            if (cmd.background) printf("[Process running in background, PID: %d]\n", process_id);
            else waitpid(process_id, &status, 0);
        }
    }
}