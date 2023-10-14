SimpleScheduler

SimpleScheduler is a rudimentary simulation of an OS scheduler that utilizes a round-robin scheduling approach, coupled with support for priority-based scheduling. Built in C, it allows the user to submit processes with or without a given priority.
Features:

    Basic Round-Robin Scheduling: Processes are added to the end of a queue and are run in a cyclic order.
    Priority-Based Scheduling: Processes can be given a priority, affecting their scheduling.
    Real-time Statistics: On termination, the shell provides statistics such as name, PID, execution time, and wait time for all jobs.
    Dynamic Code Integration: Users can incorporate their executables into the SimpleShell with minimal modifications, thanks to the provided dummy_main.h.

Getting Started:
Prerequisites:

    GCC Compiler
    A Unix-like environment or Windows Subsystem for Linux (WSL) if on Windows

Installation:

    Clone the Repository:

    bash

git clone https://github.com/nugget-cloud/scheduler.git

Navigate to the Project Directory:

bash

cd scheduler

Compile the Source Code:

bash

    gcc scheduler.c -o simpleshell

Usage:

    Start SimpleShell:

    bash

./simpleshell

Provide the Time Slice (in milliseconds):

less

Enter time slice (in milliseconds): [your_value]

Submit a Job:
For a program without priority:

css

SimpleShell$ submit ./[your_program]

For a program with a priority:

css

SimpleShell$ submit ./[your_program] [priority_value]

Note: Priority values can range from 1-4.

Terminate the Shell:

shell

    SimpleShell$ exit

    View the Process Statistics: Upon termination, the shell will display statistics for the submitted jobs.

Integrating Your Executable:

To run your program under SimpleShell:

    Ensure your program doesn't have any blocking calls, such as scanf, sleep, etc.

    Add the following code snippet at the top, immediately after any includes for stdio.h:

    c

#include "dummy_main.h"

Compile your program:

bash

gcc your_program.c -o your_program

Use the submit command within SimpleShell to run your executable.
