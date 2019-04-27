#include "types.h"
#include "stat.h"
#include "user.h"

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

#define MAX 1000

int
main(int argc, char *argv[])
{
  int i;
  for (i = 0; i < MAX; i++) {
    getpid();
  }

  if (getnumsyscallp() != MAX+2) {
      test_failed();
  }
  test_passed();
  return 0;
}
