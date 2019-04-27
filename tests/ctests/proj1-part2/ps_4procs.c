#include "types.h"
#include "stat.h"
#include "user.h"

#define O_RDONLY  0x000
#define O_WRONLY  0x001
#define O_RDWR    0x002
#define O_CREATE  0x200

void
test_failed()
{
  printf(1, "TEST FAILED\n");
  exit();
}

void
test_passed()
{
 printf(1, "TEST PASSED\n");
 exit();
}

char* args[] = {"ps", 0};

int
main(int argc, char *argv[])
{
  int pid = fork();
  if(pid == 0){
    close(1);
    open("out.txt", O_RDWR | O_CREATE);
    close(2);
    open("err.txt", O_RDWR | O_CREATE);
    exec("ps", args);
    printf(1, "exec failed!\n");
    test_failed();
    exit();
  } else {
    wait();
    int fd = open("out.txt", O_RDONLY);
    //char expected[] = {"1  -1  SLEEPING  8192  init\n2  1  SLEEPING  12288  sh\n3  2  RUNNING  8192  ps\n"};
    char expected[] = {"1  -1  SLEEPING  12288  init\n2  1  SLEEPING  16384  sh\n3  2  SLEEPING  12288  usertests\n"
                       "4  3  RUNNING  12288  ps\n"};
    char output[200];
    int numCharsRead = read(fd, output, 200);
    printf(1, "numCharsRead: %d\n", numCharsRead);
    printf(1, "ps actual output:\n%s\n", output);
    printf(1, "ps expected output:\n%s\n", expected);

    int expectedNumCharsRead = 107;
    if(numCharsRead < expectedNumCharsRead - 10 || numCharsRead > expectedNumCharsRead + 10){
      test_failed();
    }
    int i = 0;
    while(i < numCharsRead - 12 && i < sizeof(expected) - 12){
      //printf(1, "%d, %c, %c\n", i, expected[i], output[i]);
      if(expected[i] != output[i]){
        test_failed();
      }
      i++;
    }
  }
  test_passed();
  return 0;
}
