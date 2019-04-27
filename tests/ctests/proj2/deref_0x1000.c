#include "types.h"
#include "stat.h"
#include "user.h"

#define O_RDONLY  0x000
#define O_WRONLY  0x001
#define O_RDWR    0x002
#define O_CREATE  0x200

int
main(int argc, char *argv[])
{ 
	int pid = fork();

	if (pid < 0) {
    printf(1, "fork() failed.");
		printf(1, "TEST FAILED\n");
		exit();
	}  
	else if (pid == 0) {
    close(1);
    open("out.txt", O_RDWR | O_CREATE);

    uint * pageOnePointer = (uint*)0x1000;
    printf(1, "0x1000 dereference: ");
    printf(1, "%x %x\n", pageOnePointer, *pageOnePointer);
    // this process should be killed
    printf(1, "Process survived.");
    exit();
  }
	else {
    wait();
    int fd = open("out.txt", O_RDONLY);
    char expected[] = {"0x1000 dereference: 1000 ..."};
    char output[200];
    int numCharsRead = read(fd, output, 200);

    printf(1, "actual output:\n%s\n", output);
    printf(1, "expected output:\n%s\n", expected);

    if(numCharsRead < 26){
      printf(1, "TEST FAILED\n");
    }

    uint i = 0;
    for(i = 0; i < 24; i++) {
      if(output[i] != expected[i]) {
        printf(1, "TEST FAILED\n");
      }
    }

    printf(1, "TEST PASSED\n");
    
    exit();
  }
}
