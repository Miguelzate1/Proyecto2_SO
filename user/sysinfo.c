#include "kernel/types.h"
#include "kernel/sysinfo.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  struct sysinfo info;

  if(sysinfo(&info) < 0){
    fprintf(2, "sysinfo: la syscall falló\n");
    exit(1);
  }

  printf("Free Memory: %d MB\n", (int)(info.freemem / (1024 * 1024)));
  printf("Used Pages: %d\n", (int)info.usedpages);
  printf("Available Pages: %d\n", (int)info.availpages);
  printf("Runnable Processes: %d\n", info.nproc);

  exit(0);
}