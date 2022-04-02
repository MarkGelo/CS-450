#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#include "memlayout.h"

int main(int argc, char *argv[]){
    if(argc >= 1){
        int prio = atoi(argv[1]);
        setprio(prio);
        int limit = 14300;
        int i, j;
        for(i = 0; i < limit; i++){
            asm("nop");
            for(j = 0; j < limit; j++){
                asm("nop");
            }
        }
    }
    exit();
}
