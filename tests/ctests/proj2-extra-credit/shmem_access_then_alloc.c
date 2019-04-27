/* Allocate a shared page then fork, then allocate all user memory except 2 pages, then allocate another shared page.  Should be able to read and write to both shared pages throughout the process. */
#include "types.h"
#include "stat.h"
#include "user.h"

#define USERTOP 0xA0000
#define PGSIZE 4096

int ppid;

void
expectedVersusActualAddress(char* name, uint expected, uint actual)
{
  printf(1, "      %s expected: %x, Actual: %x\n", name, expected, actual);
}

void
expectedVersusActualNumeric(char* name, int expected, int actual)
{
  printf(1, "      %s expected: %d, Actual: %d\n", name, expected, actual);
}

void
expectedVersusActualString(char* name, char* expected, char* actual)
{
  printf(1, "      %s expected: %s, Actual: %s\n", name, expected, actual);
}

#define assert(x) if (x) {} else { \
   printf(1, "%s: %d ", __FILE__, __LINE__); \
   printf(1, "assert failed (%s)\n", # x); \
   printf(1, "TEST FAILED\n"); \
   kill(ppid); \
   exit(); \
}

#define assertEquals(expected, actual) if (expected == actual) {} else { \
   printf(1, "%s: %d ", __FILE__, __LINE__); \
   printf(1, "assert failed (%s == %s)\n", # expected, # actual); \
   printf(1, "assert failed (expected: %d)\n", expected); \
   printf(1, "assert failed (actual: %d)\n", actual); \
   printf(1, "TEST FAILED\n"); \
   kill(ppid); \
   exit(); \
}

int
main(int argc, char *argv[])
{
  ppid = getpid();
  
  int pid = fork();

  if (pid < 0) {
    printf(1, "fork() failed.");
    printf(1, "TEST FAILED\n");
    exit();
  } else if(pid == 0){
    // child
    char* ptr;
    int pid2;

    ptr = shmem_access(2);
    assert(ptr != (char*)-1);

    pid2 = fork();
    assert(pid2 != -1);

    if(pid2 == 0){
      // in child

      // write to shared page
      *ptr = 100;

      // read from shared page
      while(*(ptr+1) != 101){
        ; // wait for parent to write
      }

      // allocate all memory to top of userspace
      int originalSize = (int)sbrk(0);
      assert(originalSize != -1);
      uint bytesToAlloc = USERTOP - originalSize - 3*PGSIZE;
      int oldsize = (int)sbrk(bytesToAlloc);
      assert(oldsize != -1);

      char* ptr2 = shmem_access(0);
      assert(ptr2 != (char*)-1);

      // read from shared page
      while(*(ptr2+4095) != 34){
        ; // wait for parent to write
      }

      // write to shared page
      *(ptr2 + 4094) = 33;

      exit();

    } else {
      // in parent

      // read from shared page;
      while(*ptr != 100){
        ; // wait for child to write
      }

      // write to shared page
      *(ptr + 1) = 101;

      // allocate all memory to top of userspace
      int originalSize = (int)sbrk(0);
      assert(originalSize != -1);
      uint bytesToAlloc = USERTOP - originalSize - 3*PGSIZE;
      int oldsize = (int)sbrk(bytesToAlloc);
      assert(oldsize != -1);

      char* ptr2 = shmem_access(0);
      assert(ptr2 != (char*)-1);

      // write to shared page
      *(ptr2+4095) = 34;

      // read from shared page
      while(*(ptr2 + 4094) != 33){
        ; // wait for child to write
      }

      exit();
    }


    exit();

  } else {
    // parent
    wait();
    printf(1, "TEST PASSED\n");
    exit();
  }

  exit();
}
