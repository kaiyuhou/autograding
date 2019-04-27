/* open a file a new file.  Call clone and verify that the child thread can write to the file (because it got a copy of the open file descriptor). Then have the child thread open a new file and verify that the parent can't write to it. */

#include "types.h"
#include "user.h"
#include "fcntl.h"
#include "x86.h"

#undef NULL
#define NULL ((void*)0)

#undef PGSIZE
#define PGSIZE (4096)

int ppid;
volatile uint newfd = 0;

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

   int fd = open("tmp", O_WRONLY|O_CREATE);
   assert(fd == 3);
   int clone_pid = clone(worker, 0, stack);
   assert(clone_pid > 0);
   while(!newfd);
   assert(write(newfd, "goodbye\n", 8) == -1);
   printf(1, "TEST PASSED\n");
   exit();
}

void
worker(void *arg_ptr) {
   assert(write(3, "hello\n", 6) == 6);
   xchg(&newfd, open("tmp2", O_WRONLY|O_CREATE));
   exit();
}
