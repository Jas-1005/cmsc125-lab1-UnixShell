#include <stdio.h> 
#include <string.h> 
#include <stdbool.h>
#include "parser.h"

void parse_user_input(char *input, Command *cmd){
    cmd->command = NULL;
    cmd->input_file = NULL;
    cmd->output_file = NULL;
    cmd->append = false;
    cmd->background = false;
    int i = 0;
    while(i < MAX_ARGS){
        cmd->args[i++] = NULL;
    }

    int arg_index = 0;
    char *ptr = strtok(input, " ");
    while(ptr != NULL && arg_index < MAX_ARGS - 1){
        if(strcmp(ptr, "<") == 0){
            ptr = strtok(NULL, " ");
            cmd->input_file = ptr;
        } else if(strcmp(ptr, ">>") == 0){
            ptr = strtok(NULL, " ");
            cmd->output_file = ptr;
            cmd->append = true;
        } else if(strcmp(ptr, ">") == 0){
            ptr = strtok(NULL, " ");
            cmd->output_file = ptr;
            cmd->append = false;
        } else if(strcmp(ptr, "&") == 0){
            cmd->background = true;
        } else {
            cmd->args[arg_index++] = ptr;

            if(cmd->command == NULL) cmd->command = ptr;

        }
        ptr = strtok(NULL, " ");
    }

    cmd->args[arg_index] = NULL;
    // char *input_file;     // For < redirection (NULL if none)
    // char *output_file;    // For > or >> redirection (NULL if none)
    // bool append;          // true for >>, false for >
    // bool background;      // true if & present

}