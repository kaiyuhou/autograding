import shutil, os, subprocess
from testing import Test, BuildTest, pexpect
import fileinput

class Xv6Test(BuildTest, Test):
   name = None
   description = None
   timeout = 30
   tester = "usertests.c"
   make_qemu_args = ""
   point_value=0


   def _copy_test_file_with_key(self, tester_path):
      dest_path = os.path.join(self.project_path,"usertests.c")
      dest_file = open(dest_path, 'w')
      src_file = open(tester_path, 'r')
      print("Copying "+tester_path+" to "+dest_path)

      for line in src_file:
            dest_line = line.replace('TEST PASSED\\n"', 'TEST PASSED %d\\n", ' + str(self.key))
            dest_file.write(dest_line)

      src_file.close()
      dest_file.close()


   def run(self):
      tester_path = self.test_path + "/" + self.tester
      self.log("Running xv6 user progam " + str(tester_path))
      self._copy_test_file_with_key(tester_path)

      is_success = self.make(["xv6.img", "fs.img"])
      if not is_success:
         return # stop test on if make fails

      target = "qemu-nox " + self.make_qemu_args
      if self.use_gdb:
         target = "qemu-nox-gdb " + self.make_qemu_args
      self.log("make " + target)
      child = pexpect.spawn("make " + target,
            cwd=self.project_path,
            logfile=self.logfd,
            timeout=None)
      self.children.append(child)

      if self.use_gdb:
         gdb_child = subprocess.Popen(
               ["xterm", "-title", "\"gdb\"", "-e", "gdb"],
               cwd=self.project_path)
         self.children.append(gdb_child)

      child.expect_exact("init: starting sh")
      child.expect_exact("$ ")
      child.sendline("usertests")

      # check if test passed
      patterns = ["TEST FAILED", "cpu\d: panic: .*\n", "TEST PASSED " + str(int(self.key))]#, "[$][ ]"]
      index = child.expect(patterns)
      if index == 0:
         self.fail("usertests failed")
      elif index == 1:
         self.fail("xv6 kernel panic")
      elif index == 3:
         self.fail("usertests failed")

      if self.use_gdb:
         child.wait()
      else:
         child.close()
      self.done()

class Xv6Build(BuildTest):
   name = "build"
   description = "build xv6 using make"
   timeout = 60
   targets = ["xv6.img", "fs.img"]
   point_value = 15


