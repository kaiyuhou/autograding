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
  printf(1, "table address: %p\n", processInfoTable);
  int pid = fork();
  if(pid == 0){
    // in child
    int numProcesses = getprocs(processInfoTable);
    if (numProcesses != 4) {
      printf(1, "expected: %d, actual: %d\n", 4, numProcesses);
      test_failed();
    }
    exit();
  } else {
    // in parent
    wait();
    test_passed();
  }
  
  return 0;
}
