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
whenManyProcessesRequestSharedMemoryThenExit_NoMemoryLeaks(void)
{
  printf(1, "Test: whenManyProcessesRequestSharedMemoryThenExit_NoMemoryLeaks...\n");

  int i;
  int pid;
  int numForks = 8000;

  for(i = 0; i < numForks; i++){
    pid = fork();

    if(pid < 0){
      printf(1, "fork() failed on iteration %d.\n", i);
      testFailed();
    } else if(pid > 0){
      // parent loops
      wait();
      continue;
    } else {
      // child loops
      // child calls shmem_access on various page numbers then exits
      shmem_access(0);
      shmem_access(1);
      shmem_access(2);
      shmem_access(3);
      exit();
    }
  }

  if(i >= numForks){
    testPassed();
    exit();
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
    whenManyProcessesRequestSharedMemoryThenExit_NoMemoryLeaks();
    exit();
  }
  wait();
  exit();
}