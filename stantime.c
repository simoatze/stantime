#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>

int main (int argc, char *argv[])
{
  char command[500];
  char path[500];
  struct timeval tstart, tend;
  struct rusage proc;
  struct rusage start;
  struct rusage end;
  
  if(argc < 3) {
    printf("Usage: %s program_name output_file\n", (char *) argv[0]);
    return(0);
  }

  sprintf(command, "%s", argv[1]);

  getrusage(RUSAGE_CHILDREN, &start);
  gettimeofday(&tstart, NULL);

  system(command);

  gettimeofday(&tend, NULL);
  getrusage(RUSAGE_CHILDREN, &end);
  getrusage(RUSAGE_SELF, &proc);

  sprintf(path, "%s/tmp_%s", getenv("PWD"), argv[2]);
  FILE *f = fopen(path, "w");
  if (f == NULL)
    {
      printf("Error opening file!\n");
      exit(1);
    }

  fprintf(f, "Real[msecs]: %ld\n", (tend.tv_usec - tstart.tv_usec + ((tend.tv_sec - tstart.tv_sec) * 1000000)) / 1000);
  fprintf(f, "User[msecs]: %ld\n", (end.ru_utime.tv_usec - start.ru_utime.tv_usec) / 1000);
  fprintf(f, "System[msecs]: %ld\n", (end.ru_stime.tv_usec - start.ru_stime.tv_usec) / 1000);
  fprintf(f, "RSS[KBytes]: %ld\n", end.ru_maxrss - proc.ru_maxrss);
  fprintf(f, "RSS[MBytes]: %lg\n", ((end.ru_maxrss - proc.ru_maxrss) / 1024.));
  fprintf(f, "RSS[GBytes]: %lg\n", (((end.ru_maxrss - proc.ru_maxrss) / 1024.) / 1024.));
  fclose(f);

  printf("Real[msecs]: %ld\n", (tend.tv_usec - tstart.tv_usec + ((tend.tv_sec - tstart.tv_sec) * 1000000)) / 1000);
  printf("User[msecs]: %ld\n", (end.ru_utime.tv_usec - start.ru_utime.tv_usec) / 1000);
  printf("System[msecs]: %ld\n", (end.ru_stime.tv_usec - start.ru_stime.tv_usec) / 1000);
  printf("RSS[KBytes]: %ld\n", end.ru_maxrss - proc.ru_maxrss);
  printf("RSS[MBytes]: %lg\n", ((end.ru_maxrss - proc.ru_maxrss) / 1024.));
  printf("RSS[GBytes]: %lg\n", (((end.ru_maxrss - proc.ru_maxrss) / 1024.) / 1024.));
  
  return(0);
}
