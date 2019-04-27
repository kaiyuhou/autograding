/* In a loop, repeatedly call thread_create then thread_join.  There should be no memory leaks so the process size returned by sbrk should not approach USERTOP */
#include "types.h"
#include "user.h"
//#include "uthreadlib.c"

#undef NULL
#define NULL ((void*)0)

#undef PGSIZE
#define PGSIZE (4096)

int ppid;
volatile int global;

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

void worker(void *arg_ptr);

int
main(int argc, char *argv[])
{
   ppid = getpid();

   int i, thread_pid, join_pid;
   for(i = 0; i < 2000; i++) {
      global = 1;
      thread_pid = thread_create(worker, 0);
      assert(thread_pid > 0);

      join_pid = thread_join(thread_pid);
      assertEquals(thread_pid, join_pid);
      assertEquals(5, global);
      assert((uint)sbrk(0) < (150 * PGSIZE) && "shouldn't even come close");
   }

   printf(1, "TEST PASSED\n");
   exit();
}

void
worker(void *arg_ptr) {
   assert(global == 1);
   global+=4;
   exit();
}

