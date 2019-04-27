/* Calling join on a forked child process pid should return -1 (join is only valid on threads, not processes). */
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

int
main(int argc, char *argv[])
{
   ppid = getpid();

   int fork_pid = fork();
   if(fork_pid == 0) {
     // parent exits
     exit();
   }
   // in child
   assert(fork_pid > 0);

   int join_pid = join(fork_pid);
   assert(join_pid == -1);

   printf(1, "TEST PASSED\n");
   exit();
}
