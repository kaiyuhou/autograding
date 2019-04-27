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
whenProcessExits_SharedPageIsFreed(void)
{
  printf(1, "Test: whenProcessExits_SharedPageIsFreed...\n");
  int pid = fork();

  if(pid == 0){
    // in child
    char* sharedPage = shmem_access(0);
    sharedPage[0] = 42;
    exit();
  } else {
    // in parent
    wait();
    char* parentsSharedPage = shmem_access(0);
    if(parentsSharedPage[0] != 42){
      testPassed();
    } else {
      // should be garbage value after being freed, but it's still 42
      testFailed();
      expectedVersusActualNumeric("'parentsSharedPage[0]'", 1, parentsSharedPage[0]);
    }
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
    whenProcessExits_SharedPageIsFreed();
    exit();
  }
  wait();
  exit();
}