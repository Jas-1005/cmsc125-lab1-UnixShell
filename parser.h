#ifndef PARSER_H
#define PARSER_H
#include "command.h"

void parse_user_input(char *input, Command *cmd); //return command, remove pointer

char *exclude_quotations(char *ptr);

#endif