#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[1]){
    printf(1, "hello world\n");
    
    // list of childs, so i can reference their pids
    int pids[3] = {0, 0, 0};
    int exitStatuses[3] = {5, 22, 13};
    int pid;

    for(int i = 0; i < 3; i++){
        pid = fork();
        pids[i] = pid;
        if (pid == 0){
            printf(1, "(Child, PID = %d) exiting with status %d", pid, exitStatuses[i])
            exitStatus(exitStatuses[i]);
        }
    }
    
    exit();
}