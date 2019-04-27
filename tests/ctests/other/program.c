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

char *args[] = { "syscallptest", "10",  0};

int
main(int argc, char *argv[])
{
  int pid = fork();
  if (pid < 0) {
    test_failed();
  }
  else if (pid == 0) {
    exec("syscallptest", args);
    printf(1, "exec failed!\n");
    test_failed();
		exit();
  }
  else {
    wait();
  }

  test_passed();
  return 0;
}
