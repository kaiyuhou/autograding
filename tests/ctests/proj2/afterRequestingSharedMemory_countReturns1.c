#include "types.h"
#include "stat.h"
#include "user.h"

#define USERTOP 0xA0000
#define PGSIZE 4096

void
testPassed(void)
{
  printf(1, "TEST PASSED\n");
  exit();
}

void
testFailed(void)
{
  printf(1, "TEST FAILED\n");
  exit();
}

void expectedVersusActualNumeric(char* name, int expected, int actual)
{
  printf(1, "      %s expected: %d, Actual: %d\n", name, expected, actual);
}

void
afterRequestingSharedMemory_countReturns1(void)
{
  printf(1, "Test: afterRequestingSharedMemory_countReturns1...\n");
  char* sharedPage = shmem_access(0);
  int count = shmem_count(0);

  if(count == 1) {
    testPassed();
  } else {
    testFailed();
    expectedVersusActualNumeric("'count'", 1, count);
  }

  // silence the error about unused variable
  sharedPage = sharedPage + 0;
}

int
main(void)
{
  int pid;

  // we fork then run each test in a child process to keep the main process
  // free of any shared memory
  pid = fork();
  if(pid == 0){
    afterRequestingSharedMemory_countReturns1();
    exit();
  }
  wait();
  exit();
}