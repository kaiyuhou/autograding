#include "types.h"
#include "stat.h"
#include "user.h"

#define USERTOP 0xA0000
#define PGSIZE 4096

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

void expectedVersusActualNumeric(char* name, int expected, int actual)
{
  printf(1, "      %s expected: %d, Actual: %d\n", name, expected, actual);
}

void expectedVersusActualAddress(char* name, uint expected, uint actual)
{
  printf(1, "      %s expected: %x, Actual: %x\n", name, expected, actual);
}

int
main(int argc, char *argv[])
{	
	void *ptr;
  
	while (1) {
		ptr = sbrk(1024);
		if (ptr == (char *) -1) {
			break;
		}
	}
	
	ptr = shmem_access(0);
	if (ptr == NULL) {
		// in case they did extra credit, make one page of room at the top
		ptr = sbrk(-PGSIZE);
		ptr = shmem_access(0);
		if (ptr == NULL) {
			// if they did extra credit, shmem_access should now have succeeded
			printf(1, "shmem_access returned NULL: %d\n", (uint)ptr);
			test_failed();
		}
	}

	test_passed();
	exit();
}
