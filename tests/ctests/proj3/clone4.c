/* If a thread spawns another thread, address space is shared amongst thread group */
#include "types.h"
#include "user.h"

#undef NULL
#define NULL ((void*)0)

int ppid, threadId2;

#undef PGSIZE
#define PGSIZE (4096)

volatile int global = 1;

#define assert(x) if (x) {} else { \
   printf(1, "%s:%d ", __FILE__, __LINE__); \
   printf(1, "assert failed (%s)\n", # x); \
   printf(1, "TEST FAILED\n"); \
   kill(ppid); \
   exit(); \
}

void worker1(void *arg_ptr);
void worker2(void *arg_ptr);

int
main(int argc, char *argv[])
{
   ppid = getpid();
   void *stack = malloc(PGSIZE*2);
   assert(stack != NULL);
   if((uint)stack % PGSIZE) {
     stack = stack + (PGSIZE - (uint)stack % PGSIZE);
   }

   int clone_pid = clone(worker1, 0, stack);
   assert(clone_pid > 0);
   while(global != 2){
      ; // wait for thread 2 to change global
   }
   while(global != 5){
      ; // wait for thread 1 to change global
   }

   stack = malloc(PGSIZE*2);
   assert(stack != NULL);
   if((uint)stack % PGSIZE) {
     stack = stack + (PGSIZE - (uint)stack % PGSIZE);
   }
   clone_pid = clone(worker2, 0, stack);
   assert(clone_pid > 0);
   while(global != 6){
      ; //wait for worker 2 to change global
   }


   printf(1, "TEST PASSED\n");
   exit();
}

void
worker1(void *arg_ptr)
{
   assert(global == 1);

   int threadId = getpid();

   void *stack = malloc(PGSIZE*2);
   assert(stack != NULL);
   if((uint)stack % PGSIZE) {
     stack = stack + (PGSIZE - (uint)stack % PGSIZE);
   }

   threadId2 = clone(worker2, 0, stack);
   assert(threadId2 > 0);
   assert(threadId2 != threadId);
   assert(threadId2 != ppid);

   while(global != 2){
      ; // wait for thread 2
   }

   global = 5;
   exit();
}

void
worker2(void *arg_ptr)
{
   printf(1, "global: %d\n", global);
   assert(global == 1 || global == 5);
   global = global + 1;
   exit();
}
