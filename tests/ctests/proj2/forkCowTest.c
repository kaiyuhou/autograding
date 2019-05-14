#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int dummy = 1;
  printf(1, "fork_cow_test\n");

  int pid = fork();
  if(pid == 0) {
    dummy = 5;
    if (dummy != 5) {
      printf(1, "TEST FAILED\n");
      exit();
    }
//    assert(dummy == 5);
    printf(1, "I'm child process, dummy = %d\n", dummy);
    sleep(5);
    exit();
  }
  // parent
  if (dummy != 1) {
    printf(1, "TEST FAILED\n");
    exit();
  }
 // assert(dummy == 1);
  printf(1, "I'm parent process, dummy = %d\n", dummy);
  wait();
  if (dummy != 1) {
    printf(1, "TEST FAILED\n");
    exit();
  }
 // assert(dummy == 1);
  printf(1, "I'm parent process, dummy = %d\n", dummy);
  printf(1, "TEST PASSED\n");
  exit();
}
