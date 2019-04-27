/* Call clone to create a couple threads then exit the main thread.  Repeat this over and over.  We shouldn't run out of space in the ptable and we shouldn't run out of memory. */
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
   int childPid;

   int i;
   for(i = 0; i < 100; i++){
      if(i % 20 == 0){
         printf(1, "%d calling fork %d\n", ppid, i);
      }
      childPid = fork();
      assert(childPid >= 0);

      if(childPid == 0){
         // in child
         //int j;
         void* stack1;
         int clone_pid;

         stack1 = malloc(PGSIZE*2);
         assert(stack1 != NULL);
         if((uint)stack1 % PGSIZE) {
           stack1 = stack1 + (PGSIZE - (uint)stack1 % PGSIZE);
         }

         //printf(1, "calling clone1 %d\n", i);
         clone_pid = clone(worker, (void*)&arg, stack1);
         assert(clone_pid > 0);

         void* stack2 = malloc(PGSIZE*2);
         assert(stack2 != NULL);
         if((uint)stack2 % PGSIZE) {
           stack2 = stack2 + (PGSIZE - (uint)stack2 % PGSIZE);
         }

         //printf(1, "calling clone2 %d\n", i);
         clone_pid = clone(worker, (void*)&arg, stack2);
         assert(clone_pid > 0);

         //printf(1, "calling exit %d\n", i);
         exit();
      } else {
         // in parent
         wait();
      }
   }

   
   
   printf(1, "TEST PASSED\n");
   exit();
}

void
worker(void *arg_ptr) {
   while(1){
      ; // never hestitate, never surrender
   }
}
