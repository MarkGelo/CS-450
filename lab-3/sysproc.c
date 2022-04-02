#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

// lab 2
int sys_exitStatus(void)
{
  int status;

  if (argint(0, &status) < 0){ // pass in an integer, passing arguments into a kernel function - https://stackoverflow.com/questions/27068394/how-to-pass-a-value-into-a-system-call-function-in-xv6
    return -1;
  }

  exitStatus(status);

  return 0; // not reached
}

//sysfile.c has code that uses argptr

int sys_waitStatus(void){
  int *status;
  
  if (argptr(0, (void *) &status, sizeof(*status)) < 0){
    return -1;
  }

  return waitStatus(status);
}

int sys_waitpid(void){
  int pid;
  int options;
  int *status;

  // pid is 0, status 1, options 2. cuz waitpid(pid, status, options)
  if (argint(0, &pid) < 0){
    return -1;
  }
  if (argptr(1, (void *) &status, sizeof(*status)) < 0){
    return -1;
  }
  if (argint(2, &options) < 0){
    return -1;
  }

  return waitpid(pid, status, options);
}

// lab 3
int sys_setprio(void){
  int priority;
  if(argint(0, &priority) < 0){
    return -1;
  }

  setprio(priority);

  return 0;
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
