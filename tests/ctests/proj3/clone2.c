/* clone and make an assignment to the argument passed in.  In the parent, verify that the value of the arg has changed. */
#include "types.h"
#include "user.h"

#undef NULL
#define NULL ((void*)0)

#undef PGSIZE
#define PGSIZE (4096)

int ppid;
volatile int arg = 55;
volatile int global = 1;

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
   void *stack = malloc(PGSIZE*2);
   assert(stack != NULL);
   if((uint)stack % PGSIZE)
     stack = stack + (PGSIZE - (uint)stack % PGSIZE);

   int clone_pid = clone(worker, (void*)&arg, stack);
   assert(clone_pid > 0);
   while(global != 55);
   assert(arg == 1);
   printf(1, "TEST PASSED\n");
   exit();
}

void
worker(void *arg_ptr) {
   int tmp = *(int*)arg_ptr;  // tmp now equals 55
   *(int*)arg_ptr = 1;   // arg now equals 1
   assert(global == 1);
   global = tmp;   // global now equals 55
   exit();
}
