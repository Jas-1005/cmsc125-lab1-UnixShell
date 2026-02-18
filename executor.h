#ifndef EXECUTOR_H
#define EXECUTOR_H
#include "command.h"

void execute_user_command(Command cmd, int status);
bool is_bultin_command(Command cmd);

#endif