SimpleScheduler

SimpleScheduler is a rudimentary simulation of an OS scheduler that employs a round-robin scheduling approach with an option for priority-based scheduling. Written in C, this shell-like interface allows users to submit processes with or without specified priorities.
Features

Round-Robin Scheduling: Processes are enqueued and run in a cyclic order.
Priority-Based Scheduling: Support for submitting processes with distinct priorities.
Real-time Statistics: Upon termination, view vital stats like name, PID, execution time, and wait time for all tasks.
Dynamic Code Integration: Seamlessly run your executables in SimpleShell by using the provided dummy_main.h.

Prerequisites

Ensure you have the following installed:

    GCC Compiler
    A Unix-like environment (For Windows users, WSL is recommended)

Setup and Usage

    Clone the Repository:
    git clone https://github.com/nugget-cloud/scheduler.git

Navigate to the Project Directory:
     
    cd scheduler

Compile the Source Code:

    gcc scheduler.c -o simpleshell

Start SimpleShell:

    ./simpleshell

Input the Desired Time Slice (in milliseconds):

    Enter time slice (in milliseconds): [Enter your chosen value here]
    Submit a Job:

For programs without priority:

      SimpleShell$ submit ./[name_of_your_program]

For programs with priority (from 1-4):

    SimpleShell$ submit ./[name_of_your_program] [priority_value]

Terminate the Shell:

shell

    SimpleShell$ exit

After termination, the shell will automatically display the statistics for all the submitted jobs.

Integrate Your Executable

If you wish to run your program under SimpleShell:
Make sure it doesn't contain blocking calls like scanf, sleep, etc.
Include this snippet at the beginning of your program, right after any stdio.h inclusions:

    c
    #include "dummy_main.h"

Compile your program:

      gcc [name_of_your_program].c -o [name_of_your_program]

Now, you can use the submit command in SimpleShell to execute your program.
