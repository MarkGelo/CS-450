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
    
    printf(1, "Testing exitStatus(int status) and waitStatus(int *status)")
    // list of childs, so i can reference their pids
    int pids[3] = {0, 0, 0};
    int exitStatuses[3] = {5, 22, 13};
    int pid;
    int exitStatus;

    for(int i = 0; i < 3; i++){
        pid = fork();
        if (pid < 0){ // negative pid means fork failed
            printf(1, "fork failed. Retry test\n");
            exit();
        }
        pids[i] = pid;
        if (pid == 0){ // child has their pid = 0
            printf(1, "(Child, PID = %d) exiting with status %d \n", pid, exitStatuses[i]);
            exitStatus(exitStatuses[i]);
        }
    }

    for(int i = 0; i < 3; i++){
        pid = waitStatus(&exitStatus);
        printf(1, "(Parent) Child with PID = %d exited with status %d \n", pid, exitStatus);
    }
    
    exit();
}