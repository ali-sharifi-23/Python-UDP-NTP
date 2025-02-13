#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void add_timespec(struct timespec *result, struct timespec *ts1, struct timespec *ts2) {
  result->tv_sec = ts1->tv_sec + ts2->tv_sec;
  
  result->tv_nsec = ts1->tv_nsec + ts2->tv_nsec;
  
  if (result->tv_nsec >= 1000000000) {
      result->tv_nsec -= 1000000000;
      result->tv_sec += 1;
  }
}

int main(int argc, char **argv)
{
    if(argc<3) {
      perror("Not enough input arguments!: setclock delta_sec delta_ns");
      exit(1);
    }
    struct timespec c_delta, c_real, c_ref = {1000000, 0};
    sscanf(argv[1],"%ld",&c_delta.tv_sec);
    sscanf(argv[2],"%ld",&c_delta.tv_nsec);
    add_timespec(&c_real, &c_delta, &c_ref);
    printf("Ref_Sec: %lu\n", c_ref.tv_sec);
    printf("Ref_nSec: %lu\n", c_ref.tv_nsec);
    printf("Real_Sec: %lu\n", c_real.tv_sec);
    printf("Real_nSec: %lu\n", c_real.tv_nsec);
    if (clock_settime(CLOCK_REALTIME, &c_real) == -1) {
      perror("clock_settime failed");
      printf("errno: %d\n", errno);
      return 1;
    }
    printf("Clock set successfully.\n");
    return 0;
}
