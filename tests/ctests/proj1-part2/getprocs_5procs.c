#include "types.h"
#include "stat.h"
#include "user.h"
//#include "ProcessInfo.h"
//#include "processinfo.h"
//#include "processInfo.h"

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

int
main(int argc, char *argv[])
{
  struct ProcessInfo processInfoTable[64];
  int pid = fork();
  if(pid == 0){
    // in child
    pid = fork();
    if(pid == 0){
      // in grandchild
      int numProcesses = getprocs(processInfoTable);
      if (numProcesses != 5) {
          printf(1, "expected numProcesses: %d actual numProccesses: %d\n", 5, numProcesses);
          test_failed();
      }
      exit();
    } else {
      wait();
      exit();
    }
  } else {
    wait();
    test_passed();
  }
  
  return 0;
}
