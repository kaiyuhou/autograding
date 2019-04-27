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
  int i;
  int pid;
  for(i = 0; i < 61; i++){
    pid = fork();
    if(pid != 0){
      // parent
      break;
    }
    if(i == 60){
      int numProcs = getprocs(processInfoTable);
      if(numProcs != 64){
        test_failed();
      }
      exit();
    }
    wait();
    exit();
  }
  
  wait();
  if(i == 0){
    test_passed();
  }
  
  return 0;
}
