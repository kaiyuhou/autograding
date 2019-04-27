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
whenAManyProcessesSharingAPageExit_referenceCountsAreDecrementedCorrectly(void)
{
  printf(1, "Test: whenAManyProcessesSharingAPageExit_referenceCountsAreDecrementedCorrectly...\n");

  int i;
  int pid;
  int numForks = 50;

  char* sharedPage0 = shmem_access(0);
  char* sharedPage3 = shmem_access(3);

  sharedPage0[0] = 34;
  sharedPage3[0] = 43;

  for(i = 0; i < numForks; i++){
    pid = fork();

    if(pid < 0){
      printf(1, "fork() failed on iteration %d.\n", i);
      testFailed();
    } else if(pid > 0){
      // parent waits
      wait();
      break;
    } else {
      // child
      int count0 = shmem_count(0);
      if(count0 != i + 2){
        expectedVersusActualNumeric("shmem_count(0) return value", i+2, count0);
        testFailed();
      }

      int count3 = shmem_count(3);
      if(count3 != i + 2){
        expectedVersusActualNumeric("shmem_count(3) return value", i+2, count3);
        testFailed();
      }

      // loop
    }
  }
  
  int count0 = shmem_count(0);
  if(count0 != i + 1){
    expectedVersusActualNumeric("parent shmem_count(0) return value", i+1, count0);
    testFailed();
  }

  int count3 = shmem_count(3);
  if(count3 != i + 1){
    expectedVersusActualNumeric("parent shmem_count(3) return value", i+1, count3);
    testFailed();
  }
  if(i == 0){
    // original parent
    testPassed();
  }

  exit();

}

int
main(void)
{
  int pid;

  // we fork then run each test in a child process to keep the main process
  // free of any shared memory
  pid = fork();
  if(pid == 0){
    whenAManyProcessesSharingAPageExit_referenceCountsAreDecrementedCorrectly();
    exit();
  }
  wait();
  exit();
}