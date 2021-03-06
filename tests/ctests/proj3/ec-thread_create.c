/* Call thread_create. Have the worker check the argument passed in, modify a global variable, then exit. Call thread_join on the worker. */
#include "types.h"
#include "user.h"
//#include "uthreadlib.c"

#undef NULL
#define NULL ((void*)0)

#undef PGSIZE
#define PGSIZE (4096)

int ppid;
int global = 1;

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

   int arg = 35;
   int thread_pid = thread_create(worker, &arg);
   assert(thread_pid > 0);

   int join_pid = thread_join(thread_pid);
   assertEquals(thread_pid, join_pid);
   assertEquals(2, global);

   printf(1, "TEST PASSED\n");
   exit();
}

void
worker(void *arg_ptr) {
   int arg = *(int*)arg_ptr;
   assertEquals(35, arg);
   assertEquals(1, global);
   global++;
   exit();
}

