#include "kernel/types.h"
#include "kernel/sysinfo.h"
#include "user/user.h"

int
main(void)
{
  struct sysinfo info;
  
  if(sysinfo(&info) < 0){
    printf("sysinfotest: error al ejecutar sysinfo\n");
    exit(1);
  }

  printf("sysinfotest: ok\n");
  exit(0);
}