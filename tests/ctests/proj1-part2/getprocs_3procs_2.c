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
  if (getprocs((struct ProcessInfo*)processInfoTable) != 3) {
  	if (getprocs((struct ProcessInfo[])processInfoTable) != 3) {
      test_failed();
  	}
  }
  test_passed();
  return 0;
}
