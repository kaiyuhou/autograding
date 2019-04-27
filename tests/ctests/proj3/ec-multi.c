/* In a loop, call thread_create many times.  In each worker, calculate several fibonacci numbers by calling a helper function. */
#include "types.h"
#include "user.h"
//#include "uthreadlib.c"

#undef NULL
#define NULL ((void*)0)

#undef PGSIZE
#define PGSIZE (4096)

#undef NUM_THREADS
#define NUM_THREADS 30

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

unsigned int fib(unsigned int n) {
   if (n == 0) {
      return 0;
   } else if (n == 1) {
      return 1;
   } else {
      return fib(n - 1) + fib(n - 2);
   }
}


int
main(int argc, char *argv[])
{
   ppid = getpid();

   assert(fib(28) == 317811);

   int thread_pids[NUM_THREADS];

   int arg = 101;
   void *arg_ptr = &arg;

   int i;
   for (i = 0; i < NUM_THREADS; i++) {
      thread_pids[i] = thread_create(worker, arg_ptr);
      assert(thread_pids[i] > 0);
   }

   for (i = 0; i < NUM_THREADS; i++) {
      int join_pid = thread_join(thread_pids[i]);
      assertEquals(thread_pids[i], join_pid);
   }

   printf(1, "TEST PASSED\n");
   exit();
}

void
worker(void *arg_ptr) {
   int arg = *(int*)arg_ptr;
   assert(arg == 101);
   assert(global == 1);
   assert(fib(2) == 1);
   assert(fib(3) == 2);
   assert(fib(9) == 34);
   assert(fib(15) == 610);
   exit();
}

