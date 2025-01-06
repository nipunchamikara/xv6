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

int
sys_getps(void)
{
  int size;
  char *s;

  if (argint(0, &size) < 0) {
    return -1;
  }

  if (argptr(1, &s, size) < 0) {
    return -1;
  }

  const struct proc *ptable = getparr();
  const struct proc *p = ptable;

  int procCount = 0;
  while (p < &ptable[NPROC]){
    if (p->state == UNUSED) {
      p++; continue;
    }
    *(int *)s = p->pid;
    s += 4;
    *(uint *)s = p->sz;
    s += 4;
    *(int *)s = p->killed;
    s += 4;
    safestrcpy(s, p->name, 16);
    s += 16;
    procCount++;
    p++;
  }
  return procCount;
}
