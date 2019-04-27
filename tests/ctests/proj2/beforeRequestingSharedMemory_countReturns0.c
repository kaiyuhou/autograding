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
beforeRequestingSharedMemory_countReturns0(void)
{
  printf(1, "Test: beforeRequestingSharedMemory_countReturns0...\n");
  int count = shmem_count(0);

  if(count != 0){
    testFailed();
    expectedVersusActualNumeric("'count'", 0, count);
  } else {
    testPassed();
  }
}

int
main(void)
{
  int pid;

  // we fork then run each test in a child process to keep the main process
  // free of any shared memory
  pid = fork();
  if(pid == 0){
    beforeRequestingSharedMemory_countReturns0();
    exit();
  }
  wait();
  exit();
}