#include "types.h"
#include "stat.h"
#include "user.h"

#define USERTOP 0xA0000
#define PGSIZE 4096

void
expectedVersusActualAddress(char* name, uint expected, uint actual)
{
  printf(1, "      %s expected: %x, Actual: %x\n", name, expected, actual);
}

void
expectedVersusActualNumeric(char* name, int expected, int actual)
{
  printf(1, "      %s expected: %d, Actual: %d\n", name, expected, actual);
}

int
main(int argc, char *argv[])
{
  
  int pid = fork();

  if (pid < 0) {
    printf(1, "fork() failed.");
    printf(1, "TEST FAILED\n");
    exit();
  } else if(pid == 0){
    // child
    int originalSize = (int)sbrk(0);

    uint bytesToAlloc = USERTOP - originalSize - 5*PGSIZE;
    int oldsize = (int)sbrk(bytesToAlloc);

    if(oldsize != originalSize){
      expectedVersusActualNumeric("sbrk return value", originalSize, oldsize);
      printf(1, "TEST FAILED\n");
    }

    uint bytesToAlloc2 = 6*PGSIZE;
    int result = (int)sbrk(bytesToAlloc2);

    if(result != -1){
      expectedVersusActualNumeric("sbrk return value", -1, result);
      printf(1, "TEST FAILED\n");
    }

    exit();

  } else {
    // parent
    wait();
    printf(1, "TEST PASSED\n");
    exit();
  }
}
