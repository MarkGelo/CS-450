#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[1]){
    //printf("hello world\n");
    
    // list of childs, so i can reference their pids
    int pids[3] = {0, 0, 0};
    int exitStatuses[3] = {5, 22, 13};
    
    for(int i = 0; i < 3; i++){
        pid = fork();
        pids[i] = pid;
        if (pid == 0){
            printf("(Child, PID = %d) exiting with status %d", pid, exitStatuses[i])
            exitStatus(exitStatuses[i]);
        }
    }
    
    exit();
}