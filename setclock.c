#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char **argv)
{
    if(argc<3) {
      perror("Not enough input arguments!: setclock delta_sec delta_ns");
      exit(1);
    }
    struct timespec c_real;
    sscanf(argv[1],"%ld",&c_real.tv_sec);
    sscanf(argv[2],"%ld",&c_real.tv_nsec);
    if (clock_settime(CLOCK_REALTIME, &c_real) == -1) {
      // printf("errno: %d\n", errno);
      return 1;
    }
    return 0;
}
