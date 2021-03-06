/* Allocate all memory to top of userspace (USERTOP), then deallocate 2 pages, then call shmem_access on 2 non-consecutive pages, then fork and have parent and child read and write. */
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
    int originalSize = (int)sbrk(0);
    assert(originalSize != -1);

    // allocate all memory to top of userspace
    uint bytesToAlloc = USERTOP - originalSize - PGSIZE;
    int oldsize = (int)sbrk(bytesToAlloc);
    assert(oldsize != -1);

    if(oldsize != originalSize){
      expectedVersusActualNumeric("sbrk return value", originalSize, oldsize);
      printf(1, "TEST FAILED\n");
    }

    // check new size
    int newSize = (int)sbrk(0);
    assert(newSize != -1);

    if(newSize != 159 * PGSIZE){
      expectedVersusActualNumeric("sbrk return value", 159*PGSIZE, newSize);
      printf(1, "TEST FAILED\n");
    }

    // make room for 2 shared page
    newSize = (int)sbrk(-2*PGSIZE);
    assert(newSize != -1);

    if(newSize != 159 * PGSIZE){
      expectedVersusActualNumeric("sbrk return value", 159*PGSIZE, newSize);
      printf(1, "TEST FAILED\n");
    }

    newSize = (int)sbrk(0);
    assert(newSize != -1);

    if(newSize != 157 * PGSIZE){
      expectedVersusActualNumeric("sbrk return value", 157*PGSIZE, newSize);
      printf(1, "TEST FAILED\n");
    }

    char* ptr;
    char* ptr2;
    int i;
    char arr[8] = "EECS343";
    
    ptr = shmem_access(0);
    if (ptr == NULL) {
      printf(1, "shmem_access(0) returned NULL.");
      printf(1, "TEST FAILED\n");
    }

    // put some garbage in there to start
    *(ptr+6) = 1;
    *(ptr+7) = 1;

    ptr2 = shmem_access(3);
    if (ptr == NULL) {
      printf(1, "shmem_access(3) returned NULL.");
      printf(1, "TEST FAILED\n");
    }

    int pid2 = fork();
    if (pid2 < 0) {
      printf(1, "fork() failed.");
      printf(1, "TEST FAILED\n");
    }
    else if (pid2 == 0) {
      // in child
      while(*(ptr+7) != arr[7]){
        ; // wait for parent to finish writing
      }
      
      // child reads from shared page
      for (i = 0; i < 8; i++) {
        if (*(ptr2+i) != arr[i]) {
          expectedVersusActualString("", arr, ptr2);
          printf(1, "TEST FAILED\n");
        }
      }

      for (i = 0; i < 8; i++) {
        if (*(ptr+i) != arr[i]) {
          expectedVersusActualString("", arr, ptr);
          printf(1, "TEST FAILED\n");
        }
      }

      // child writes it backwards
      for(i = 7; i >= 0; i--) {
        *(ptr+i) = arr[7-i];
      }

      exit(); // child exits
    }
    else {
      // in parent
      // parent writes to shared pages
      for (i = 0; i < 8; i++) {
        *(ptr2+i) = arr[i];
      }

      for (i = 0; i < 8; i++) {
        *(ptr+i) = arr[i];
      }
      
      wait(); // wait for child to exit

      // parent reads
      for(i = 7; i >= 0; i--) {
        if(*(ptr+i) != arr[7-i]) {
          expectedVersusActualString("", arr, ptr);
          printf(1, "TEST FAILED\n");
        }
      }

    }

    exit();

  } else {
    // parent
    wait();
    printf(1, "TEST PASSED\n");
    exit();
  }
}
