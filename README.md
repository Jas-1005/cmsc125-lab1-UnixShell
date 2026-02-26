# mysh - A Custom UNIX Shell

An interactive UNIX shell developed for lab1 requirement of the course, CMSC 125 - Operating Systems. 

# Group Members
  * Eleah Joy Melchor
  * Jasmine Magadan

## PR1
* **Problem Analysis:** 
  * implement an interactive command-line interface 
  * handle background processes

* **Solution Architecture:**
  * command.h
  * executor.h
  * parser.h
  * executor.c
  * parser.c
  * main.c
  * Makefile

* **Timeline:**
  * Week 1 (Jan 30 - Feb 5): 
      * problem analysis
      * design modular structure
      * populate readme file
      * initial implementation code

  * Week 2 (Feb 6 - Feb 12): 
      * functional prototype with core features

  * Week 3 (Feb 13 - Feb 19):
      * test results
      * documentation of issues

  * Week 4 (Feb 26): 
      * program defense
      * finalize readme file
      * submit lab1 deliverables  


## Features 

* **Interactive Command Execution:** mysh features a persistent prompt that supports standard UNIX commands.
* **Built-in Commands Support:** Native support for exit, cd, and pwd executed within the shell process.
* **External Commands:** Allows execution of system binaries using fork() and execv(). 
* **I/O Redirection:**
  * `>`: Truncate
  * `>>`: Append
  * `<`: Redirect input
* **Background Execution:** Support for the & operator to execute processes asynchronously.
* **Memory Cleanup and Management:** Cleanup for leakage memory prevention 
## Getting Started

### Prerequisites

To compile and run this shell, you need: 

* A UNIX-like environment (e.g., Linux, MacOS, or WSL).
* The gcc compiler.
* make utility

### Step 1: Clone and Compile

1. Clone this repository or download the source code.
2. Open your terminal in the project folder.
3. Compile and build the executable by using the provided make file.

```bash
make 
```

### Step 2: Running the Shell

Start the shell by executing the compiled binary:

```bash
./myshell
```
### Step 3: Usage Examples

* **Simple command:** ```ls -lo```
* **Redirection:** ```ls > [filename].txt```
* **Background:** ```sleep 10 &```
* **Built-in:** ```cd /tmp```

### Step 3: Other Commands
Run automated tests of the shell by executing the command:

```bash
make test
```

Clean build and test files by executing the command:

```bash
make clean
```

## Known Bugs & Limitations
* **Requires spacing around redirection operators (parser currently uses strtok)**
* **Does not support multiple piped commands**

## Development
Development Period : Jan 28 - Feb 25, 2026
Tested on: Linux Kernel 6.6.87.2-microsoft-standard-WSL2
Compiler: gcc (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0

This lab is written in C and interfaces directly with UNIX syscalls.



