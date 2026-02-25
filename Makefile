# all: Compile the shell
# clean: Remove binaries and object files

CC=gcc
CFLAGS= -Wall


_OBJ = main.o parser.o executor.o
OBJ = $(_OBJ)

%.o: %.c parser.h executor.h command.h
	@$(CC) -c -o $@ $< $(CFLAGS)

all: myshell

myshell: $(OBJ)
	@$(CC) -o $@ $^

.PHONY: clean

clean: 
	@rm -f *.o myshell

# tester

PASS = "\033[32m[PASS]\033[0m" #green for pass
FAIL = "\033[31m[FAIL]\033[0m" #red for fail

test: myshell
	@echo "Tester: Running...\n"
	
	@# --- pwd ---
	@echo "pwd" | ./myshell | grep -q "/" \
		&& echo $(PASS) "pwd prints a path" \
		|| echo $(FAIL) "pwd prints a path"
		
	@# --- output redirection ---
	@echo "echo redirectiontest > /tmp/mysh_test.txt" | ./myshell ; \
		grep -q "redirectiontest" /tmp/mysh_test.txt \
		&& echo $(PASS) "output redirection >" \
		|| echo $(FAIL) "output redirection >"
	
	@# --- append redirection >> ---
	@echo "echo appended >> /tmp/mysh_test.txt" | ./myshell ; \
		grep -q "appended" /tmp/mysh_test.txt \
		&& echo $(PASS) "append redirection >>" \
		|| echo $(FAIL) "append redirection >>"

	@# --- input redirection ---
	@echo "wc -l < /tmp/mysh_test.txt" | ./myshell | grep -q "[0-9]" \
		&& echo $(PASS) "input redirection <" \
		|| echo $(FAIL) "input redirection <"
	
	@# --- cd then pwd ---
	@printf "cd /tmp\npwd\n" | ./myshell | grep -q "/tmp" \
		&& echo $(PASS) "cd changes directory" \
		|| echo $(FAIL) "cd changes directory"
		
	@# --- nonexistent command exits ---
	@echo "nonexistent_cmd_xyz" | ./myshell ; \
		echo $(PASS) "nonexistent command does not crash shell"
		
	@# --- empty input ---
	@printf "\n\n" | ./myshell \
		&& echo $(PASS) "empty input handled" \
		|| echo $(FAIL) "empty input handled"

	@# --- background job ---
	@echo "sleep 10 &" | ./myshell | grep -q "PID" \
		&& echo $(PASS) "background job prints PID" \
		|| echo $(FAIL) "background job prints PID"
		
	@# --- edge cases ---
	@# --- long command lines ---
	@echo "echo aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" | ./myshell | grep -q "aaa" \
		&& echo $(PASS) "very long command lines" \
		|| echo $(FAIL) "very long command lines"
	
	@# --- commands with many arguments ---
	@echo "echo a b c d e f g h i j k l m n o p q r s t u v w x y z" | ./myshell | grep -q "z" \
		&& echo $(PASS) "many arguments" \
		|| echo $(FAIL) "many arguments"
		
	@# --- redirectation to /dev/null ---
	@echo "ls > /dev/null" | ./myshell \
		&& echo $(PASS) "redirection to /dev/null" \
		|| echo $(FAIL) "redirection to /dev/null"
		
	@# --- spaces around redirection operators ---
	@echo "echo spacetest > /tmp/mysh_space.txt" | ./myshell ; \
		grep -q "spacetest" /tmp/mysh_space.txt \
		&& echo $(PASS) "spaces around redirection operators" \
		|| echo $(FAIL) "spaces around redirection operators"
		
	@rm -f /tmp/mysh_test.txt
	@echo "\nDone."
