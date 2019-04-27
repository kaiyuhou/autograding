import sys, os, inspect

import toolspath
from testing import Xv6Test, Xv6Build

ctestsDir = os.path.basename(__file__)[:-3]

curdir = os.path.realpath(os.path.dirname(inspect.getfile(inspect.currentframe())))
def get_description(name):
  cfile = os.path.join(curdir, 'ctests', ctestsDir, name + '.c')
  with open(cfile, 'r') as f:
    desc = f.readline()
  desc = desc.strip()
  desc = desc[2:]
  desc = "Description:" + desc
  if desc[-2:] == '*/':
    desc = desc[:-2]
  return desc.strip()

test_values = [
  {'name': 'shared_page_easy0', 'point_value': 1.74, 'timeout': 10},
  {'name': 'shared_page_easy1', 'point_value': 1.66, 'timeout': 10},
  {'name': 'shared_page_easy2', 'point_value': 1.66, 'timeout': 10},
  {'name': 'shared_page_easy3', 'point_value': 1.66, 'timeout': 10},
  {'name': 'shared_page0', 'point_value': 1.66, 'timeout': 10},
  {'name': 'shared_page1', 'point_value': 1.66, 'timeout': 10},
  {'name': 'shared_page2', 'point_value': 1.66, 'timeout': 10},
  {'name': 'shared_page3', 'point_value': 1.66, 'timeout': 10},
  {'name': '2_shared_pages', 'point_value': 1.66, 'timeout': 10},
  {'name': '2_sep_shared_pages', 'point_value': 1.66, 'timeout': 10},
  {'name': '3_sep_shared_pages', 'point_value': 1.66, 'timeout': 10},
  {'name': 'shmem_access_then_alloc', 'point_value': 1.66, 'timeout': 10},
]

all_tests = []

build_test = Xv6Build
build_test.point_value = 0;

for test in test_values:
  testname = test['name']

  if 'point_value' in test.keys():
    point_value = test['point_value']
  else:
    point_value = 0

  if 'timeout' in test.keys():
    timeout = test['timeout']
  else:
    timeout = 10

  members = {
      'name': testname,
      'tester': 'ctests/' + ctestsDir + '/' + testname + '.c',
      'description': get_description(testname),
      'timeout': timeout,
      'point_value': point_value
      }
  newclass = type(testname, (Xv6Test,), members)
  all_tests.append(newclass)
  setattr(sys.modules[__name__], testname, newclass)

class usertests(Xv6Test):
  name = 'usertests_2_2'
  tester = 'ctests/' + ctestsDir + '/usertests.c'
  description = get_description(name)
  timeout = 240

# To include full regression test by running usertests, uncomment the line below.
#all_tests.append(usertests)

from testing.runtests import main
main(build_test, all_tests)
