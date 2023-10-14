#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>

#define MAX_JOBS 100

typedef struct {
    int pid;
    char name[255];
    int priority;
    int running;
    time_t start_time;
    time_t end_time;
} Job;

Job jobs[MAX_JOBS];
int num_jobs = 0;
int TSLICE = 1000;

void sigchld_handler(int signo) {
    (void) signo;
    int status;
    pid_t pid;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        for (int i = 0; i < num_jobs; i++) {
            if (jobs[i].pid == pid) {
                jobs[i].end_time = time(NULL);
            }
        }
    }
}

int submit_job(char* job_name, int priority) {
    if (num_jobs >= MAX_JOBS) {
        printf("Job limit reached.\n");
        return -1;
    }

    int pid = fork();
    if (pid == 0) {  // Child process
        pause();  // Wait for signal to start
        execlp(job_name, job_name, NULL);
        exit(0);  // In case exec fails
    } else if (pid > 0) {  // Parent process
        jobs[num_jobs].pid = pid;
        strncpy(jobs[num_jobs].name, job_name, sizeof(jobs[num_jobs].name));
        jobs[num_jobs].priority = priority;
        jobs[num_jobs].running = 0;
        jobs[num_jobs].start_time = 0;
        jobs[num_jobs].end_time = 0;
        num_jobs++;
    } else {
        perror("Failed to fork");
        return -1;
    }

    return pid;
}

void scheduler() {
    while (1) {
        usleep(TSLICE * 1000);  // Sleep for TSLICE milliseconds
        for (int i = 0; i < num_jobs; i++) {
            if (jobs[i].running == 0 && jobs[i].end_time == 0) {
                kill(jobs[i].pid, SIGCONT);  // Signal child to start
                if (jobs[i].start_time == 0) {
                    jobs[i].start_time = time(NULL);
                }
                jobs[i].running = 1;
            } else if (jobs[i].end_time == 0) {
                kill(jobs[i].pid, SIGSTOP);  // Signal child to stop
                jobs[i].running = 0;
            }
        }
    }
}

void display_stats() {
    printf("\nJob Statistics:\n");
    printf("Name\tPID\tExec Time\tWait Time\n");
    for (int i = 0; i < num_jobs; i++) {
        double exec_time = difftime(jobs[i].end_time, jobs[i].start_time);
        double wait_time = exec_time - (double) TSLICE/1000;  // naive calculation
        printf("%s\t%d\t%.2lf\t\t%.2lf\n", jobs[i].name, jobs[i].pid, exec_time, wait_time);
    }
}

int main(int argc, char **argv) {
    signal(SIGCHLD, sigchld_handler);

    printf("Enter time slice (in milliseconds): ");
    scanf("%d", &TSLICE);

    printf("SimpleShell started. Submit your jobs!\n");

    char command[255];
    char job_name[255];
    int priority = 1;  // default priority

    // Start the scheduler in a separate process
    if (fork() == 0) {
        scheduler();
        exit(0);
    }

    while (1) {
        printf("SimpleShell$ ");
        scanf("%s", command);

        if (strcmp(command, "submit") == 0) {
            scanf("%s", job_name);
            if (scanf("%d", &priority) <= 0) {
                priority = 1; // Reset if not provided
            }
            submit_job(job_name, priority);
        } else if (strcmp(command, "exit") == 0) {
            display_stats();
            exit(0);
        } else {
            printf("Unknown command.\n");
        }
    }

    return 0;
}
