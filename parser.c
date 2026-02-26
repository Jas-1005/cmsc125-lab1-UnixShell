#include <stdio.h> 
#include <string.h> 
#include <stdbool.h>
#include <stdlib.h>
#include "parser.h"


char *exclude_quotations(char *ptr){
    int i, j;
    for (i = 0 ,j = 0 ; ptr[i] != '\0'; i++){
        if (ptr[i] != '"') ptr[j++] = ptr[i]; 
    }
    ptr[j] = '\0';
    return ptr;
}

void free_memory(Command *cmd){
    if(cmd->command) {
        free(cmd->command);
        cmd->command = NULL;
    }
    if(cmd->input_file) {
        free(cmd->input_file);
        cmd->input_file = NULL;
    }
    if(cmd->output_file) {
        free(cmd->output_file);
        cmd->output_file = NULL;

    }
    int i = 0;
    while(cmd->args[i] != NULL){
        free(cmd->args[i]);
        cmd->args[i] = NULL;
        i++;
    }
}

void parse_user_input(char *input, Command *cmd){// make this return Command    
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
            if (ptr != NULL) cmd->input_file = strdup(ptr);
            else {
                fprintf(stderr, "mysh: syntax error, missing input file\n");
            } 

        } else if(strcmp(ptr, ">>") == 0){
            ptr = strtok(NULL, " ");
            if (ptr != NULL){
                cmd->output_file = strdup(ptr);
                cmd->append = true;
            } else {
                fprintf(stderr, "mysh: syntax error, missing output file\n");
            } 
    
            
        } else if(strcmp(ptr, ">") == 0){
            ptr = strtok(NULL, " ");
            if (ptr != NULL){
                cmd->output_file = strdup(ptr);
                cmd->append = false;
            } else {
                fprintf(stderr, "mysh: syntax error, missing output file\n");
            } 
    
        } else if(strcmp(ptr, "&") == 0){
            cmd->background = true;
            
        } else {
            if (strchr(ptr, '"') != NULL) exclude_quotations(ptr);
            cmd->args[arg_index++] = strdup(ptr);

            if(cmd->command == NULL) cmd->command = strdup(ptr);

        }
        ptr = strtok(NULL, " ");
    }

    cmd->args[arg_index] = NULL;
    // char *input_file;     // For < redirection (NULL if none)
    // char *output_file;    // For > or >> redirection (NULL if none)
    // bool append;          // true for >>, false for >
    // bool background;      // true if & present

}