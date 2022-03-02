#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#include "memlayout.h"

int main(int argc, char *argv[1]){
    //printf(1, "hello world\n");
    
    printf(1, "Testing exitStatus(int status) and waitStatus(int *status)\n");
    // list of childs, so i can reference their pids
    //int pids[3] = {0, 0, 0};
    int exitStatuses[3] = {5, 22, 13};
    int pid;
    int exitStatus_;

    for(int i = 0; i < 3; i++){
        pid = fork();
        if (pid < 0){ // negative pid means fork failed
            printf(1, "fork failed. Retry test\n");
            exit();
        }
        //pids[i] = pid;
        if (pid == 0){ // child has their pid = 0
            printf(1, "(Child) exiting with status %d \n", exitStatuses[i]);
            exitStatus(exitStatuses[i]);
        }
    }

    sleep(2); // give time so most childs finish
    for(int i = 0; i < 3; i++){
        pid = waitStatus(&exitStatus_);
        printf(1, "(Parent) Child with PID = %d exited with status %d \n", pid, exitStatus_);
    }

    printf(1, "\n");
    printf(1, "Testing waitpid\n");
    // list of childs, so i can reference their pids
    int pids[3] = {0, 0, 0};
    int options[3] = {7, 6, 5};

    for(int i = 0; i < 3; i++){
        pid = fork();
        if (pid < 0){ // negative pid means fork failed
            printf(1, "fork failed. Retry test\n");
            exit();
        }
        if (pid == 0){ // child has their pid = 0
            printf(1, "(Child) exiting with status %d \n", exitStatuses[i]);
            exitStatus(exitStatuses[i]);
        }
        pids[i] = pid;
    }

    sleep(2); // give time so most childs finish
    for(int i = 0; i < 3; i++){
        printf(1, "(Parent) Waiting for child with PID = %d to exit", pids[2 - i]);
        pid = waitpid(pids[2 - i], &exitStatus_, options[i]);
        printf(1, "(Parent) Child with PID = %d exited with status %d \n", pid, exitStatus_);
    }

    
    exit();
}