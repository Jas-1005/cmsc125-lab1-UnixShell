# mysh - A Custom UNIX Shell

An interactive UNIX shell developed for lab1 requirement of the course, CMSC 125 - Operating Systems. 

## Features 

* **Interactive Command Execution:** mysh features a persistent prompt that supports standard UNIX commands.
* **Built-in Commands Support:** Native support for exit, cd, and pwd executed within the shell process.
* **External Commands:** Allows execution of system binaries using fork() and execv(). 
* **I/O Redirection:**
  * `>`: Truncate
  * `>>`: Append
  * `<`: Redirect input
* **Background Execution:** Support for the & operator to execute processes asynchronously.

## Getting Started

### Prerequisites

To compile and run this shell, you need: 

* A UNIX-like environment (e.g., Linux, MacOS, or WSL).
* The gcc compiler.
* make

### Step 1: Clone and Compile

1. Clone this repository or download the source code.
2. Open your terminal in the project folder.
3. Compile the source code using gcc:

```bash
gcc -Wall -o mysh mysh.c
```

### Step 2: Running the Shell

Start the shell by executing the compiled binary:

```bash
./mysh
```

### Step 3: Usage Examples

* **Simple command:** ```ls -lo```
* **Redirection:** ```ls > [filename].txt```
* **Background:** ```sleep 10&```
* **Built-in:** ```cd /tmp```

## Roadmap by Features

---

## Compatibility

**Tested on:** 
**Environment:**

## Development

This lab is written in C and interfaces directly with UNIX syscalls.

### Core System Calls Used

--


