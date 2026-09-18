#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(argc < 3){
    fprintf(2, "Uso: %s <numero_syscall> <comando> [args...]\n", argv[0]);
    exit(1);
  }

  // Convertimos el id/mascara y llamamos a nuestra syscall
  if(trace(atoi(argv[1])) < 0){
    fprintf(2, "%s: fallo la llamada a trace\n", argv[0]);
    exit(1);
  }

  // Ejecutamos el comando pasado como argumento
  exec(argv[2], &argv[2]);

  // Si exec falla:
  fprintf(2, "exec %s fallo\n", argv[2]);
  exit(1);
}