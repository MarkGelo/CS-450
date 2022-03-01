#include "types.h"
#include "stat.h"
#include "user.h"
#include <stdlib.h>

int main(int argc, char *argv[1]){
    //printf("hello world\n");
    
    // list of childs, so i can reference their pids
    int pids[3] = {0, 0, 0};
    for(int i = 0; i < 3; i++){
        pid = fork();
        pids[i] = pid;
        if (pid == 0){
            int rng = rand() % 20 + 1; // random from 1 to 20
            printf("(Child, PID = %d) exiting with status %d", pid, rng)
            exitStatus(rng);
        }
    }
    
    exit();
}