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
  int pid;
  int i;
  for(i = 0; i < 60; i++){
    pid = fork();
    if(pid != 0){
      // parent
      break;
    }
    if(i == 59){
      // in child, exec ps
      close(1);
      open("out63.txt", O_RDWR | O_CREATE);
      close(2);
      open("err.txt", O_RDWR | O_CREATE);
      exec("ps", args);
      printf(1, "exec failed!\n");
      test_failed();
      exit();
    }
  }
  
  if(i == 0){
    wait();
    int fd = open("out63.txt", O_RDONLY);
    printf(1, "fd: %d\n", fd);
    char expected[] = {"1  -1  SLEEPING  12288  init\n2  1  SLEEPING  12288  sh\n3  2  SLEEPING  12288  tester\n"
                       "4  3  SLEEPING  12288  tester\n5  4  SLEEPING  12288  tester\n6  5  SLEEPING  12288  tester\n"
                       "7  6  SLEEPING  12288  tester\n8  7  SLEEPING  12288  tester\n9  8  SLEEPING  12288  tester\n"
                       "10  9  SLEEPING  12288  tester\n11  10  SLEEPING  12288  tester\n12  11  SLEEPING  12288  tester\n"
                       "13  12  SLEEPING  12288  tester\n14  13  SLEEPING  12288  tester\n15  14  SLEEPING  12288  tester\n"
                       "16  15  SLEEPING  12288  tester\n17  16  SLEEPING  12288  tester\n18  17  SLEEPING  12288  tester\n"
                       "19  18  SLEEPING  12288  tester\n20  19  SLEEPING  12288  tester\n21  20  SLEEPING  12288  tester\n"
                       "22  21  SLEEPING  12288  tester\n23  22  SLEEPING  12288  tester\n24  23  SLEEPING  12288  tester\n"
                       "25  24  SLEEPING  12288  tester\n26  25  SLEEPING  12288  tester\n27  26  SLEEPING  12288  tester\n"
                       "28  27  SLEEPING  12288  tester\n29  28  SLEEPING  12288  tester\n30  29  SLEEPING  12288  tester\n"
                       "31  30  SLEEPING  12288  tester\n32  31  SLEEPING  12288  tester\n33  32  SLEEPING  12288  tester\n"
                       "34  33  SLEEPING  12288  tester\n35  34  SLEEPING  12288  tester\n36  35  SLEEPING  12288  tester\n"
                       "37  36  SLEEPING  12288  tester\n38  37  SLEEPING  12288  tester\n39  38  SLEEPING  12288  tester\n"
                       "40  39  SLEEPING  12288  tester\n41  40  SLEEPING  12288  tester\n42  41  SLEEPING  12288  tester\n"
                       "43  42  SLEEPING  12288  tester\n44  43  SLEEPING  12288  tester\n45  44  SLEEPING  12288  tester\n"
                       "46  45  SLEEPING  12288  tester\n47  46  SLEEPING  12288  tester\n48  47  SLEEPING  12288  tester\n"
                       "49  48  SLEEPING  12288  tester\n50  49  SLEEPING  12288  tester\n51  50  SLEEPING  12288  tester\n"
                       "52  51  SLEEPING  12288  tester\n53  52  SLEEPING  12288  tester\n54  53  SLEEPING  12288  tester\n"
                       "55  54  SLEEPING  12288  tester\n56  55  SLEEPING  12288  tester\n57  56  SLEEPING  12288  tester\n"
                       "58  57  SLEEPING  12288  tester\n59  58  SLEEPING  12288  tester\n60  59  SLEEPING  12288  tester\n"
                       "61  60  SLEEPING  12288  tester\n62  61  SLEEPING  12288  tester\n"
                       "63  62  RUNNING  8192  ps\n"};
    char output[2000];
    int numCharsRead = read(fd, output, 2000);
    printf(1, "numCharsRead: %d\n", numCharsRead);
    printf(1, "ps actual output:\n%s\n", output);
    printf(1, "ps expected output:\n%s\n", expected);

    int expectedNumCharsRead = 28 + 26 + 30*7 + 31 + 32*52 + 26;
    if(numCharsRead < expectedNumCharsRead - 10 || numCharsRead > expectedNumCharsRead + 10){
      test_failed();
    }
    int i = 0;
    while(i < numCharsRead - 12 && i < sizeof(expected) - 12){
      if(expected[i] != output[i]){
        printf(1, "%d, %c, %c\n", i, expected[i], output[i]);
        test_failed();
      }
      i++;
    }
  } else {
    wait();
    exit();
  }
  test_passed();
  return 0;
}
