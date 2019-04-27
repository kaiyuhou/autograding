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

void
whenRequestingSharedMemory_ValidAddressIsReturned(void)
{
  printf(1, "Test: whenRequestingSharedMemory_ValidAddressIsReturned...\n");
  char* sharedPage = shmem_access(0);
  char* highestPage =       (char*)(USERTOP - PGSIZE);
  char* secondHighestPage = (char*)(USERTOP - 2*PGSIZE);
  char* thirdHighestPage =  (char*)(USERTOP - 3*PGSIZE);
  char* fourthHighestPage = (char*)(USERTOP - 4*PGSIZE);
  
  if(sharedPage == highestPage ||
     sharedPage == secondHighestPage ||
     sharedPage == thirdHighestPage ||
     sharedPage == fourthHighestPage) {
    testPassed();
  } else {
    testFailed(); 
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
    whenRequestingSharedMemory_ValidAddressIsReturned();
    exit();
  }
  wait();
  exit();
}