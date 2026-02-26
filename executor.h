#ifndef EXECUTOR_H
#define EXECUTOR_H
#include "command.h"

void execute_user_command(Command cmd, int *status, int *job_id);
bool is_builtin_command(Command cmd);
void file_redirection(int fd, char file_type[]);

#endif