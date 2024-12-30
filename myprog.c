#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char **argv) {
  if (argc != 2) {
    printf(1, "Usage: myprog <file_path>\n");
    exit();
  }
  printf(1, "Size of a given inode: %d\n", getinodesize(argv[1]));
  exit();
}