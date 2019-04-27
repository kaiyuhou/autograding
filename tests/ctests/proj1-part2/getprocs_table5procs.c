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

void
checkNumeric(char* name, int expected, int actual)
{
  if(expected != actual){
    printf(1, "%s  expected: %d, actual: %d\n", name, expected, actual);
    test_failed();
  }
}

void
checkString(char* name, char* expected, char* actual)
{
  int i = 0;
  while(i < 16){
    if(expected[i] != actual[i]){
      printf(1, "%s  expected: %s, actual: %s\n", name, expected, actual);
      test_failed();
    }
    i++;
    if(expected[i] == '\0' && actual[i] == '\0'){
      break;
    }
  }
}

int
main(int argc, char *argv[])
{
  int pid;
  int i;
  int numForks = 2;
  for(i = 0; i < numForks; i++){
    pid = fork();
    if(pid != 0){
      break;
    } else {
      if(i == numForks - 1){
        struct ProcessInfo processInfoTable[64];
  printf(1, "table address: %p\n", processInfoTable);
        getprocs(processInfoTable);

        checkNumeric("processInfoTable[0].pid", 1, processInfoTable[0].pid);
        checkNumeric("processInfoTable[0].state", 2, processInfoTable[0].state);
        checkNumeric("processInfoTable[0].sz", 12288, processInfoTable[0].sz);
        checkString("processInfoTable[0].name", "init", processInfoTable[0].name);

        checkNumeric("processInfoTable[1].pid", 2, processInfoTable[1].pid);
        checkNumeric("processInfoTable[1].ppid", 1, processInfoTable[1].ppid);
        checkNumeric("processInfoTable[1].state", 2, processInfoTable[1].state);
        checkNumeric("processInfoTable[1].sz", 16384, processInfoTable[1].sz);
        checkString("processInfoTable[1].name", "sh", processInfoTable[1].name);

        checkNumeric("processInfoTable[2].pid", 3, processInfoTable[2].pid);
        checkNumeric("processInfoTable[2].ppid", 2, processInfoTable[2].ppid);
        checkNumeric("processInfoTable[2].state", 2, processInfoTable[2].state);
        checkNumeric("processInfoTable[2].sz", 16384, processInfoTable[2].sz);
        checkString("processInfoTable[2].name", "usertests", processInfoTable[2].name);

        checkNumeric("processInfoTable[3].pid", 4, processInfoTable[3].pid);
        checkNumeric("processInfoTable[3].ppid", 3, processInfoTable[3].ppid);
        checkNumeric("processInfoTable[3].state", 2, processInfoTable[3].state);
        checkNumeric("processInfoTable[3].sz", 16384, processInfoTable[3].sz);
        checkString("processInfoTable[3].name", "usertests", processInfoTable[3].name);

        checkNumeric("processInfoTable[4].pid", 5, processInfoTable[4].pid);
        checkNumeric("processInfoTable[4].ppid", 4, processInfoTable[4].ppid);
        checkNumeric("processInfoTable[4].state", 4, processInfoTable[4].state);
        checkNumeric("processInfoTable[4].sz", 16384, processInfoTable[4].sz);
        checkString("processInfoTable[4].name", "usertests", processInfoTable[4].name);

        test_passed();
      }
    }
  }
  wait();
  exit();
  return 0;
}
