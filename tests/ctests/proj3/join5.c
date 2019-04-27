/* Call clone to create a new thread (thread1), which calls clone to create another new thread (thread2).  thread1 calls join on thread2.  main thread calls join on thread1. */
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

void worker1(void *arg_ptr);
void worker2(void *arg_ptr);

int
main(int argc, char *argv[])
{
   ppid = getpid();

   void *stack1 = malloc(PGSIZE*2);
   assert(stack1 != NULL);
   if((uint)stack1 % PGSIZE){
     stack1 = stack1 + (PGSIZE - (uint)stack1 % PGSIZE);
   }

   int arg = 42;
   int clone_pid = clone(worker1, &arg, stack1);
   assert(clone_pid > 0);

   int join_pid = join(clone_pid);
   assert(join_pid == clone_pid);
   assert(global == 3);

   printf(1, "TEST PASSED\n");
   exit();
}

void
worker1(void *arg_ptr) {
  int* arg = (int*)arg_ptr;
  assert(*arg == 42);
  assert(global == 1);
  global++;

  void* stack2 = malloc(PGSIZE*2);
  assert(stack2 != NULL);
  if((uint)stack2 % PGSIZE){
    stack2 = stack2 + (PGSIZE - (uint)stack2 % PGSIZE);
  }

  int clone_pid2 = clone(worker2, arg, stack2);
  assert(clone_pid2 > 0);

  int join_pid2 = join(clone_pid2);
  assert(join_pid2 == clone_pid2);
  assert(global == 3);
  assert(*arg == 43);

  exit();
}

void
worker2(void *arg_ptr) {
   int* arg2 = (int*)arg_ptr;
   assert(*arg2 == 42);
   assert(global == 2);
   global++;
   (*arg2)++;
   assert(global == 3);
   assert(*(int*)arg_ptr == 43);

   printf(1, "worker2 calling exit\n");
   exit();
}