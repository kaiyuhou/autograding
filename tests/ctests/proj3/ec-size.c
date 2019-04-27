/* check that address space size is updated in threads */
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
unsigned int size = 0;
lock_t lock, lock2;


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

   int arg = 101;
   void *arg_ptr = &arg;

   lock_init(&lock);
   lock_init(&lock2);
   lock_acquire(&lock);
   lock_acquire(&lock2);

   int thread_pids[NUM_THREADS];

   int i;
   for (i = 0; i < NUM_THREADS; i++) {
      thread_pids[i] = thread_create(worker, arg_ptr);
      assert(thread_pids[i] > 0);
   }

   size = (unsigned int)sbrk(0);

   while (global < NUM_THREADS) {
      lock_release(&lock);
      sleep(50);
      lock_acquire(&lock);
   }

   global = 0;
   sbrk(10000);
   size = (unsigned int)sbrk(0);
   lock_release(&lock);

   while (global < NUM_THREADS) {
      lock_release(&lock2);
      sleep(50);
      lock_acquire(&lock2);
   }
   lock_release(&lock2);

   for (i = 0; i < NUM_THREADS; i++) {
      int join_pid = thread_join(thread_pids[i]);
      assertEquals(thread_pids[i], join_pid);
   }

   printf(1, "TEST PASSED\n");
   exit();
}

void
worker(void *arg_ptr) {
   lock_acquire(&lock);
   assert((unsigned int)sbrk(0) == size);
   global++;
   lock_release(&lock);

   lock_acquire(&lock2);
   assert((unsigned int)sbrk(0) == size);
   global++;
   lock_release(&lock2);

   exit();
}

