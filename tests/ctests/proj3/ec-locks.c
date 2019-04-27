/* In a loop, call thread_create many times.  In the worker, in a loop, get the lock, read a global and store as a temp, waste a little time, then set global = temp + 1, then release the lock. After all workers have been joined, global should have the correct value. */
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
int global = 0;
lock_t lock;
int loops = 1000;


#define assert(x) if (x) {} else { \
   printf(1, "%s: %d ", __FILE__, __LINE__); \
   printf(1, "assert failed (%s)\n", # x); \
   printf(1, "TEST FAILED\n"); \
   kill(ppid); \
   exit(); \
}

void worker(void *arg_ptr);

int
main(int argc, char *argv[])
{
   ppid = getpid();

   lock_init(&lock);

   int thread_pids[NUM_THREADS];

   int i;
   for (i = 0; i < NUM_THREADS; i++) {
      thread_pids[i] = thread_create(worker, 0);
      assert(thread_pids[i] > 0);
   }

   for (i = 0; i < NUM_THREADS; i++) {
      int join_pid = thread_join(thread_pids[i]);
      assert(join_pid > thread_pids[i]);
   }

   assert(global == NUM_THREADS * loops);

   printf(1, "TEST PASSED\n");
   exit();
}

void
worker(void *arg_ptr) {
   int i, j, tmp;
   for (i = 0; i < loops; i++) {
      lock_acquire(&lock);
      tmp = global;
      for(j = 0; j < 50; j++); // take some time
      global = tmp + 1;
      lock_release(&lock);
   }
   exit();
}

