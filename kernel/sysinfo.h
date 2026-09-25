#ifndef _SYSINFO_H_
#define _SYSINFO_H_

struct sysinfo {
  uint64 freemem;    // memoria libre en bytes
  uint64 usedpages;  // páginas físicas usadas
  uint64 availpages; // páginas físicas disponibles
  int nproc;         // procesos en estado RUNNABLE
};

#endif