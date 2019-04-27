/* Trying to find race conditions, but honestly I think this test does nothing.  It calls clone 30 times then calls sbrk(0) in the parent and the child thread, then calls join 30 times to wait for all the child threads. */
#include "types.h"
#include "user.h"

#undef NULL
#define NULL ((void*)0)

#undef NUM_THREADS
#define NUM_THREADS 30

#undef PGSIZE
#define PGSIZE (4096)

int ppid;
int global = 0;
unsigned int size = 0;
volatile int lock = 0;
int bytesToAdd = 600;


#define assert(x) if (x) {} else { \
   printf(1, "%s: %d ", __FILE__, __LINE__); \
   printf(1, "assert failed (%s)\n", # x); \
   printf(1, "TEST FAILED\n"); \
   kill(ppid); \
   exit(); \
}

void worker(void* arg_ptr);

int
main(int argc, char *argv[])
{
   ppid = getpid();
   int threadIds[NUM_THREADS];
   void* stacks[NUM_THREADS];

   int arg = 101;
   void* arg_ptr = &arg;
   lock = 1;

   int i;
   for(i = 0; i < NUM_THREADS; i++){
      void* stack = malloc(2*PGSIZE);
      if((uint)stack % PGSIZE) {
         stack = stack + (PGSIZE - (uint)stack % PGSIZE);
      }
      stacks[i] = stack;
   }
   for (i = 0; i < NUM_THREADS; i++) {
      void* stack = stacks[i];
      int thread_pid = clone(worker, arg_ptr, stack);
      assert(thread_pid > 0);
      threadIds[i] = thread_pid;
   }

   size = (unsigned int)sbrk(0);
   printf(1, "main thread size: %d\n", size);
   lock = 0;

   while (global < NUM_THREADS) {
      sleep(100);
   }

   // printf(1, "main thread increasing size.\n");
   // global = 0;
   // assert((unsigned int)sbrk(0) == size);


   for (i = 0; i < NUM_THREADS; i++) {
      int thread_pid = threadIds[i];
      int join_pid = join(thread_pid);
      assert(join_pid > 0);
      assert(join_pid == thread_pid)
   }

   printf(1, "TEST PASSED\n");
   exit();
}

void
worker(void* arg_ptr) {
   while(lock == 1){
      ; // wait for main thread to unlock
   }
   printf(1, "worker thread size: %d\n", sbrk(0));
   assert((unsigned int)sbrk(0) == size);
   global++;

   exit();
}

