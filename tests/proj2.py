import toolspath
from testing import Xv6Build, Xv6Test

# Part 1
class deref_null(Xv6Test):
  name = "deref_null"
  description = "Part 1: Fork to create a child process and have the child attempt to dereference NULL pointer.  " + \
                 "Child process should be killed."
  tester = "ctests/proj2/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 15
  timeout = 10

class deref_0x1000(Xv6Test):
  name = "deref_0x1000"
  description = "Part 1: Fork to create a child process and have the child attempt to dereference address 0x1000.  " + \
                 "Child process should survive and exit normally."
  tester = "ctests/proj2/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 2.5
  timeout = 10

class alloc_155_pages(Xv6Test):
  name = "alloc_155_pages"
  description = "Part 1: Attempt to allocate up to the top of userspace (below shared memory)."
  tester = "ctests/proj2/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 2.5
  timeout = 15

class whenTryingToAllocateAboveUsertop_sbrkShouldFail(Xv6Test):
  name = "whenTryingToAllocateAboveUsertop_sbrkShouldFail"
  description = "Part 1: Attempt to allocate up to the top of userspace (below shared memory).  " + \
                "Then try to allocate 6 more pages, which would blow through USERTOP.  sbrk should return -1."
  tester = "ctests/proj2/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 2.5
  timeout = 10

class whenTryingToReallocateAPageNearUsertop_sbrkShouldSucceed(Xv6Test):
  name = "whenTryingToReallocateAPageNearUsertop_sbrkShouldSucceed"
  description = "Part 1: Attempt to allocate up to the top of userspace (below shared memory).  " + \
                "Then deallocate one page and reallocate one page.  Make sure both calls to sbrk succeed."
  tester = "ctests/proj2/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 2.5
  timeout = 10

# Part 2
class shmem_access_invalid_input(Xv6Test):
  name = "shmem_access_invalid_input"
  description = "Part 2: When calling shmem_access with invalid parameters (e.g. -1, 100), it should return NULL."
  tester = "ctests/proj2/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 3.6
  timeout = 10

class shmem_count_invalid_input(Xv6Test):
  name = "shmem_count_invalid_input"
  description = "Part 2: When calling shmem_count with invalid parameters (e.g. -1, 100), it should return -1."
  tester = "ctests/proj2/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 3.6
  timeout = 10

class whenRequestingSharedMemory_ValidAddressIsReturned(Xv6Test):
  name = "whenRequestingSharedMemory_ValidAddressIsReturned"
  description = "Part 2: shmem_access must return a page-aligned address within the top 4 pages of user space."
  tester = "ctests/proj2/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 3.6
  timeout = 10

class afterRequestingSharedMemory_countReturns1(Xv6Test):
  name = "afterRequestingSharedMemory_countReturns1"
  description = "Part 2: After calling shmem_access once, shmem_count should return 1."
  tester = "ctests/proj2/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 3.6
  timeout = 10

class whenSharingAPage_ParentSeesChangesMadeByChild(Xv6Test):
  name = "whenSharingAPage_ParentSeesChangesMadeByChild"
  description = "Part 2: Parent gets shared page, sets a value to 42, then forks.  Child increments value to 43 then exits.  " + \
                "Parent reads value and should see that it is now 43."
  tester = "ctests/proj2/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 3.6
  timeout = 10

class whenProcessExits_SharedPageIsFreed(Xv6Test):
  name = "whenProcessExits_SharedPageIsFreed"
  description = "Part 2: Parent forks.  Child requests shared page, sets value to 42, then exits.  Parent then requests same " + \
                "shared page.  Parent should see garbage because the page was cleaned up when the child exited."
  tester = "ctests/proj2/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 3.6
  timeout = 10

class whenSharingAPageBetween2Processes_countReturns2(Xv6Test):
  name = "whenSharingAPageBetween2Processes_countReturns2"
  description = "Part 2: Parent gets shared page, then forks and child get shared page.  shmem_count on the shared page should " + \
                "return 2.  Then the child exits.  shmem_count on the shared page should then return 1."
  tester = "ctests/proj2/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 3.6
  timeout = 10

class whenProcessExists_countReturns0(Xv6Test):
  name = "whenProcessExists_countReturns0"
  description = "Part 2: Parent forks, child gets a shared page then exits.  Parent then calls shmem_count on the shared page, which " + \
                "should return 0."
  tester = "ctests/proj2/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 3.6
  timeout = 10

class beforeRequestingSharedMemory_countReturns0(Xv6Test):
  name = "beforeRequestingSharedMemory_countReturns0"
  description = "Part 2: No shared pages are requested.  shmem_count should return 0."
  tester = "ctests/proj2/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 3.6
  timeout = 10

class shmem_access_communication(Xv6Test):
  name = "shmem_access_communication"
  description = "Part 2: Request shared page then fork.  Put child to sleep for 20, parent writes string to " + \
               "shared page.  Child should be able to read the string written by parent."
  tester = "ctests/proj2/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 3.6
  timeout = 40

class shmem_access_double_call(Xv6Test):
  name = "shmem_access_double_call"
  description = "Part 2: When a process calls shmem_access twice for the same page, it should receive the same " + \
               "address as the return value both times."
  tester = "ctests/proj2/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 3.6
  timeout = 20

class shmem_access_many_call(Xv6Test):
  name = "shmem_access_many_call"
  description = "Part 2: When a process calls shmem_access 2,000,000 times for the same page, it should receive the same " + \
               "address as the return value every time and physical memory should not run out because only 1 page needs to be " + \
               "allocated."
  tester = "ctests/proj2/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 3.6
  timeout = 20

class whenManyProcessesRequestSharedMemoryThenExit_NoMemoryLeaks(Xv6Test):
  name = "whenManyProcessesRequestSharedMemoryThenExit_NoMemoryLeaks"
  description = "Part 2: When a process forks 8,000 times, calling shmem_access each time, then exiting, " + \
               "kernel should not run out of physical memory as memory is freed after process exits."
  tester = "ctests/proj2/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 3.6
  timeout = 30

class shmem_access_full_address_space(Xv6Test):
  name = "shmem_access_full_address_space"
  description = "Part 2: Call sbrk repeatedly until it returns -1, then request a shared page and make sure it doesn't return " + \
                "NULL.  If it does return NULL, deallocate 1 page of normal memory and try requesting a shared page again.  " + \
                "This time it should definitely not return NULL."
  tester = "ctests/proj2/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 3.6
  timeout = 10

class shmem_access_full_address_space2(Xv6Test):
  name = "shmem_access_full_address_space2"
  description = "Part 2: Request a shared page, then call sbrk repeatedly until it returns -1.  Make sure it never returns an address " + \
                "higher than that of the shared page."
  tester = "ctests/proj2/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 3.6
  timeout = 10

class whenAProcessWithSharedPageRepeatedlyForks_ChildrenHaveAccessToSharedPage(Xv6Test):
  name = "whenAProcessWithSharedPageRepeatedlyForks_ChildrenHaveAccessToSharedPage"
  description = "Part 2: Request a shared page, then call fork() repeatedly.  Each child should be able to read from the shared " +\
                " page and the shmem_count should increment each time."
  tester = "ctests/proj2/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 3.6
  timeout = 10

class whenAManyProcessesSharingAPageExit_referenceCountsAreDecrementedCorrectly(Xv6Test):
  name = "whenAManyProcessesSharingAPageExit_referenceCountsAreDecrementedCorrectly"
  description = "Part 2: Request a shared page, then call fork() repeatedly.  Each child should see the shmem_count increment " + \
                "each time.  Parents wait for child to exit and should see shmem_count decremented each time."
  tester = "ctests/proj2/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 2.4
  timeout = 10

class shmem_access_exec(Xv6Test):
  name = "shmem_access_exec"
  description = "Part 2: Experimental Test."
  tester = "ctests/proj2/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 0
  timeout = 10

class shmem_access_exec2(Xv6Test):
  name = "shmem_access_exec2"
  description = "Part 2: Experimental Test."
  tester = "ctests/proj2/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 0
  timeout = 10


import toolspath
from testing.runtests import main
main(Xv6Build, [deref_null, deref_0x1000, alloc_155_pages, whenTryingToAllocateAboveUsertop_sbrkShouldFail,
               whenTryingToReallocateAPageNearUsertop_sbrkShouldSucceed,

               shmem_access_invalid_input, shmem_count_invalid_input,
               whenRequestingSharedMemory_ValidAddressIsReturned, afterRequestingSharedMemory_countReturns1,
               whenSharingAPage_ParentSeesChangesMadeByChild, whenProcessExits_SharedPageIsFreed, 
               whenSharingAPageBetween2Processes_countReturns2, whenProcessExists_countReturns0,
               beforeRequestingSharedMemory_countReturns0,
               shmem_access_communication, shmem_access_double_call, shmem_access_many_call, whenManyProcessesRequestSharedMemoryThenExit_NoMemoryLeaks,
               shmem_access_full_address_space,
               shmem_access_full_address_space2, whenAProcessWithSharedPageRepeatedlyForks_ChildrenHaveAccessToSharedPage,
               whenAManyProcessesSharingAPageExit_referenceCountsAreDecrementedCorrectly, 
               shmem_access_exec, shmem_access_exec2])
#main(Xv6Build, [shmem_access_communication])
