import toolspath
from testing import Xv6Build, Xv6Test

# Part A
class Basic(Xv6Test):
   name = "getprocs_easiest"
   description = "2A: getprocs simply returns without error"
   tester = "ctests/proj1-part2/" + name + ".c"
   make_qemu_args = "CPUS=1"
   point_value = 5
   timeout = 20

class NoExtraProcs(Xv6Test):
   name = "getprocs_3procs"
   description = "2A: when calling getprocs first, returns correct number of processes: 3"
   tester = "ctests/proj1-part2/" + name + ".c"
   make_qemu_args = "CPUS=1"
   point_value = 6
   timeout = 20

class OneExtraProc(Xv6Test):
   name = "getprocs_4procs"
   description = "2A: when calling getprocs with one additional process running, " + \
                 "returns correct number of processes: 4"
   tester = "ctests/proj1-part2/" + name + ".c"
   make_qemu_args = "CPUS=1"
   point_value = 5
   timeout = 20

class TwoExtraProc(Xv6Test):
   name = "getprocs_5procs"
   description = "2A: when calling getprocs with two additional processes running, " + \
                 "returns correct number of processes: 5"
   tester = "ctests/proj1-part2/" + name + ".c"
   make_qemu_args = "CPUS=1"
   point_value = 5
   timeout = 20

class ThreeExtraProc(Xv6Test):
   name = "getprocs_6procs"
   description = "2A: when calling getprocs with three additional processes running, " + \
                 "returns correct number of processes: 6"
   tester = "ctests/proj1-part2/" + name + ".c"
   make_qemu_args = "CPUS=1"
   point_value = 6
   timeout = 20

class SixtyOneExtraProc(Xv6Test):
   name = "getprocs_64procs"
   description = "2A: when calling getprocs with 61 additional processes running, " + \
                 "returns correct number of processes: 64"
   tester = "ctests/proj1-part2/" + name + ".c"
   make_qemu_args = "CPUS=1"
   point_value = 6
   timeout = 20


# Part B
class PsPrints4Procs(Xv6Test):
   name = "ps_4procs"
   description = "2B: when executing ps from first shell, " + \
                 "it prints correct info for init, sh, tester and itself."
   tester = "ctests/proj1-part2/" + name + ".c"
   make_qemu_args = "CPUS=1"
   point_value = 5
   timeout = 20

class PsPrints5Procs(Xv6Test):
   name = "ps_5procs"
   description = "2B: when executing ps from one child process, " + \
                 "it prints correct info for init, sh, two testers and itself."
   tester = "ctests/proj1-part2/" + name + ".c"
   make_qemu_args = "CPUS=1"
   point_value = 6
   timeout = 20

class PsPrints63Procs(Xv6Test):
   name = "ps_63procs"
   description = "2B: when executing ps as 63rd process, " + \
                 "it prints correct info."
   tester = "ctests/proj1-part2/" + name + ".c"
   make_qemu_args = "CPUS=1"
   point_value = 5
   timeout = 20

class getProcsCheckTable3Procs(Xv6Test):
   name = "getprocs_table3procs"
   description = "2B: when calling getprocs from first shell, processInfoTable contains " + \
                 "correct info."
   tester = "ctests/proj1-part2/" + name + ".c"
   make_qemu_args = "CPUS=1"
   point_value = 5
   timeout = 20

class getProcsCheckTable4Procs(Xv6Test):
   name = "getprocs_table4procs"
   description = "2B: when calling getprocs from one child, processInfoTable contains " + \
                 "correct info."
   tester = "ctests/proj1-part2/" + name + ".c"
   make_qemu_args = "CPUS=1"
   point_value = 5
   timeout = 20

class getProcsCheckTable5Procs(Xv6Test):
   name = "getprocs_table5procs"
   description = "2B: when calling getprocs with two additional processes running, processInfoTable contains " + \
                 "correct info."
   tester = "ctests/proj1-part2/" + name + ".c"
   make_qemu_args = "CPUS=1"
   point_value = 5
   timeout = 20

class getProcsCheckTable63Procs(Xv6Test):
   name = "getprocs_table63procs"
   description = "2B: when calling getprocs with 63 total processes, processInfoTable contains " + \
                 "correct info."
   tester = "ctests/proj1-part2/" + name + ".c"
   make_qemu_args = "CPUS=1"
   point_value = 6
   timeout = 20


import toolspath
from testing.runtests import main
#main(Xv6Build, [Program])
main(Xv6Build, [Basic, NoExtraProcs, OneExtraProc, TwoExtraProc, ThreeExtraProc, SixtyOneExtraProc, 
                PsPrints4Procs, PsPrints5Procs, getProcsCheckTable3Procs, 
               getProcsCheckTable4Procs, getProcsCheckTable5Procs, getProcsCheckTable63Procs])
#main(Xv6Build, [NoExtraProcs, OneExtraProc, TwoExtraProc])
