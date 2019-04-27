/* test cv_wait and cv_signal, signal, don't broadcast */
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
cond_t cond;

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

   lock_init(&lock);

   int thread_pids[NUM_THREADS];

   int i;
   for(i = 0; i < NUM_THREADS; i++) {
     thread_pids[i] = thread_create(worker, 0);
     assert(thread_pids[i] > 0);
   }

   sleep(50);

   for(i = 0; i < NUM_THREADS; i++) {
     lock_acquire(&lock);
     assert(global == i);
     cv_signal(&cond);
     lock_release(&lock);

     int join_pid = thread_join(thread_pids[i]);
     assertEquals(thread_pids[i], join_pid);

     sleep(10);
     lock_acquire(&lock);
     assert(global == i+1);
     lock_release(&lock);
   }

   printf(1, "TEST PASSED\n");
   exit();
}

void
worker(void *arg_ptr) {
  lock_acquire(&lock);
  cv_wait(&cond, &lock);
  global++;
  lock_release(&lock);
  exit();
}
