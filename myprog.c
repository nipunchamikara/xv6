#include "types.h"
#include "stat.h"
#include "user.h"

int main(void) {
  printf(1, "Size of my address space is %d bytes.\n", getmysize());
  printf(1, "Kernel start address is 0x%x.\n", getkernelstartaddr());
  printf(1, "Kernel end address is 0x%x.\n", getkernelendaddr());
  printf(1, "Kernel variable address is 0x%x.\n", getkernelvariaddr());
  printf(1, "System call address is 0x%x.\n", getsystemcalladdr());
  exit();
}