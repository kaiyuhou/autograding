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
whenSharingAPageBetween2Processes_countReturns2(void)
{
  printf(1, "Test: whenSharingAPageBetween2Processes_countReturns2...\n");
  char* sharedPage = shmem_access(0);
  sharedPage = sharedPage + 0;  // silence unused variable error

  int pid = fork();

  if(pid == 0){
    // in child
    char* childsSharedPage = shmem_access(0);
    childsSharedPage = childsSharedPage + 0;  // silence unused variable error

    int count = shmem_count(0);
    if(count != 2){
      testFailed();
      expectedVersusActualNumeric("'count'", 2, count);
    }

    exit();
  } else{
    // in parent
    wait(); // wait for child to exit
    int parentsCount = shmem_count(0);
    if(parentsCount != 1){
      testFailed();
      expectedVersusActualNumeric("'parentsCount'", 1, parentsCount);
    }
  }

  testPassed();
}

int
main(void)
{
  int pid;

  // we fork then run each test in a child process to keep the main process
  // free of any shared memory
  pid = fork();
  if(pid == 0){
    whenSharingAPageBetween2Processes_countReturns2();
    exit();
  }
  wait();
  exit();
}