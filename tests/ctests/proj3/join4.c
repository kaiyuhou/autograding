/* Calling wait on a process with child threads but no child processes should return -1. */
#include "types.h"
#include "user.h"

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

void worker(void *arg_ptr);

int
main(int argc, char *argv[])
{
   ppid = getpid();

   void *stack = malloc(PGSIZE*2);
   assert(stack != NULL);
   if((uint)stack % PGSIZE)
     stack = stack + (4096 - (uint)stack % PGSIZE);

   int arg = 42;
   int clone_pid = clone(worker, &arg, stack);
   assert(clone_pid > 0);

   sleep(250);
   assert(wait() == -1);

   int join_pid = join(clone_pid);
   assert(join_pid == clone_pid);
   assert(global == 2);

   printf(1, "TEST PASSED\n");
   exit();
}

void
worker(void *arg_ptr) {
   int arg = *(int*)arg_ptr;
   assert(arg == 42);
   assert(global == 1);
   global++;
   exit();
}
