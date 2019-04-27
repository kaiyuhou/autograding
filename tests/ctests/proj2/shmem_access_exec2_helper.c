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

int
main(int argc, char *argv[])
{
  printf(1, "Exec-ed helper2.\n");
 	char *ptr;
	int i;
  
  for (i = 3; i >= 0; i--) {
    ptr = shmem_access(i);
    if (ptr == NULL) {
      test_failed();
    }
    
    *ptr = 'c';
  }
	
	test_passed();
	exit();
}
