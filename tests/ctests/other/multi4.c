#include "types.h"
#include "stat.h"
#include "user.h"

void
test_failed()
{
	printf(1, "TEST FAILED\n");
	exit();
}

void
test_passed()
{
 printf(1, "TEST PASSED\n");
 exit();
}

#define MAX 1000

void
child()
{
  if (getnumsyscallp() != 0) { //counter is not reset
      printf(1, "new process does not have a new counter\n");
      test_failed();
  }

  int i;
  for (i = 0; i < MAX; i++) {
    getpid();
    getnumsyscallp();
    uptime();
    getnumsyscallp();
    uptime();
    getnumsyscallp();
    getnumsyscallp();
    getnumsyscallp();
  }

  if (getnumsyscallp() != 3*MAX) {
      test_failed();
  }
}

int
main(int argc, char *argv[])
{
  int i;
  for (i = 0; i < MAX; i++) {
    getpid();
    getnumsyscallp();
    uptime();
    getnumsyscallp();
    uptime();
    getnumsyscallp();
    getnumsyscallp();
    getnumsyscallp();
  }

  int pid = fork();
  if (pid < 0) {
    test_failed();
  }
  else if (pid == 0) {
    child();
    exit();
    return 0;
  }
  else {
    wait();
  }

  //parent's counter should stay untouched
  if (getnumsyscallp() != 3*MAX+4) { //2 from beginning; 1 fork; 1 wait
      printf(1, "parent process's counter is incorrect\n");
      test_failed();
  }

  //parent's counter should be able to continue to change
  for (i = 0; i < MAX; i++) {
    getpid();
    getnumsyscallp();
    uptime();
    getnumsyscallp();
    uptime();
    getnumsyscallp();
    getnumsyscallp();
    getnumsyscallp();
  }

  if (getnumsyscallp() != 6*MAX+4) { //2 from beginning; 1 fork; 1 wait
      printf(1, "parent process's counter is incorrect\n");
      test_failed();
  }

  test_passed();
  return 0;
}
