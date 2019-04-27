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

void
expectedVersusActualNumeric(char* name, int expected, int actual)
{
  printf(1, "      %s expected: %d, Actual: %d\n", name, expected, actual);
}

void
expectedVersusActualAddress(char* name, uint expected, uint actual)
{
  printf(1, "      %s expected: %x, Actual: %x\n", name, expected, actual);
}

void
expectedVersusActualString(char* name, char* expected, char* actual)
{
  printf(1, "      %s expected: %s, Actual: %s\n", name, expected, actual);
}

int
main(int argc, char *argv[])
{
  char *ptr;
  int i;
  char arr[8] = "EECS343";
  
  ptr = shmem_access(2);
  if (ptr == NULL) {
    printf(1, "shmem_access(2) returned NULL.");
    test_failed();
  }

  int pid = fork();
  if (pid < 0) {
    printf(1, "fork() failed.");
    test_failed();
  }
  else if (pid == 0) {
    // in child
    sleep(20);
    
    // child reads
    for (i = 0; i < 8; i++) {
      if (*(ptr+i) != arr[i]) {
        expectedVersusActualString("", arr, ptr);
        test_failed();
      }
    }

    // child writes it backwards
    for(i = 7; i >= 0; i--) {
      *(ptr+i) = arr[7-i];
    }
  }
  else {
    // in parent
    // parent writes
    for (i = 0; i < 8; i++) {
      *(ptr+i) = arr[i];
    }
    
    wait();

    // parent reads
    for(i = 7; i >= 0; i--) {
      if(*(ptr+i) != arr[7-i]) {
        expectedVersusActualString("", arr, ptr);
        test_failed();
      }
    }
    test_passed();
  }


  exit();
}
