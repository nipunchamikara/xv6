#include "types.h"
#include "stat.h"
#include "user.h"

#define NUM_STRUCTS 64

struct process {
  int pid;
  uint size;
  int killed;
  char name[16];
};

int main(void) {

  const struct process processArray[NUM_STRUCTS];

  int procCount = getps(NUM_STRUCTS * sizeof(struct process), &processArray);

  const struct process *p = processArray;
  while(p != &processArray[procCount]){
    printf(1, "Process %d: %s\t | size: %d\t | killed: %d\n", p->pid, p->name, p->size, p->killed);
    p++;
  }

  exit();
}
