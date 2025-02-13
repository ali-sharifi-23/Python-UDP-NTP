#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

unsigned long usec, sec;

int main(int argc, char **argv)
{
    if(argc<3) {
      perror("Not enough input arguments!: setclock delta_sec delta_us");
      exit(1);
    }
    sscanf(argv[1],"%lu",&sec);
    sscanf(argv[2],"%lu",&usec);
    struct timeval delta;
    delta.tv_sec = sec;
    delta.tv_usec = usec;
    printf("Seconds: %ld\n", delta.tv_sec);
    printf("Microseconds: %ld\n", delta.tv_usec);
    int status = settimeofday(&delta,NULL);
    if (status == -1) {
      fprintf(stderr, "Error setting system time: %s\n", strerror(errno));
      exit(1);
    } else {
      printf("System time updated successfully\n");
    }
    return 0;
}
