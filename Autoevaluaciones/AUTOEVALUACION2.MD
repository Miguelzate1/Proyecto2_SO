# Autoevaluación Individual - Proyecto 2: System Calls en xv6

**Estudiante:** Samuel Quintero Escobar 
**Curso:** Sistemas Operativos (2026-2) 
**Docente:** José Luis Montoya Pareja

## 1. Contribuciones Individuales

* **Diseño e implementación completa de la syscall `sysinfo`:** Definí la estructura `struct sysinfo` en `kernel/sysinfo.h` para transferir memoria libre, páginas usadas/disponibles y procesos activos desde el kernel hacia el espacio de usuario.
* **Conteo de memoria física (`kernel/kalloc.c`):** Implementé `countfreepages()`, que recorre la lista enlazada `kmem.freelist` protegida con `kmem.lock` para contar cuántas páginas físicas están libres en el sistema.
* **Conteo de procesos activos (`kernel/proc.c`):** Implementé `countrunnable()`, que recorre el arreglo `proc[NPROC]` y cuenta cuántos procesos están en estado `RUNNABLE`, adquiriendo `p->lock` de cada proceso para evitar condiciones de carrera con el scheduler.
* **Depuración de un error de compilación crítico en `proc.c`:** Detecté que `countrunnable()` había quedado anidada dentro de `procdump()`, lo que producía un error de compilación (`-Werror=unused-function`) porque nunca era invocada desde ahí. Corregí el problema extrayéndola como función independiente al nivel superior del archivo.
* **Depuración de `sys_sysinfo` (`kernel/sysproc.c`):** Al compilar con el toolchain real de RISC-V, identifiqué dos incompatibilidades con la versión de xv6 usada en el curso: `argaddr()` retorna `void` (no puede compararse con `< 0`), y `copyout()` en esta versión recibe un parámetro adicional (`p->sz`) para verificar límites de memoria. Corregí ambas llamadas y verifiqué que el kernel compilara sin errores.
* **Programa de usuario (`user/sysinfo.c`):** Implementé el programa que invoca la syscall `sysinfo()` e imprime en pantalla la memoria libre, páginas usadas, páginas disponibles y procesos runnable en el formato solicitado.
* **Verificación funcional real:** Compilé el kernel completo con `riscv64-linux-gnu-gcc` y lo ejecuté en QEMU, confirmando que `sysinfo` imprime valores correctos y coherentes (memoria libre, páginas y procesos).
* **Resolución de un problema de Git:** Detecté que el archivo `.gitignore` del repositorio contenía únicamente un `*`, lo que ignoraba absolutamente todos los archivos del proyecto (incluido mi código fuente). Lo corregí para que solo ignorara binarios y artefactos de compilación (`*.o`, `kernel/kernel`, `fs.img`, etc.), permitiendo subir correctamente mis archivos a la rama `rama/sysinfo`.

## 2. Comprensión de la Implementación

Entiendo el flujo completo de mi syscall: `sysinfo` recolecta métricas del estado interno del kernel —memoria física libre (recorriendo `kmem.freelist`) y procesos en estado `RUNNABLE` (recorriendo la tabla de procesos)— las empaqueta en una estructura, y usa `copyout()` para transferir esos datos de forma segura desde el espacio de direcciones del kernel hacia el espacio de direcciones virtuales del proceso de usuario, respetando que cada proceso tiene su propia tabla de páginas (`pagetable`). También comprendo por qué se necesitan spinlocks (`kmem.lock`, `p->lock`): xv6 corre en varios cores (`hart`) simultáneamente, y sin sincronización un core podría modificar la lista de páginas libres o el estado de un proceso justo mientras otro core lo está leyendo, produciendo un conteo incorrecto o un fallo del kernel.

## 3. Principales Aprendizajes

* La diferencia práctica entre `argint`/`argaddr` (que reciben el argumento por referencia) y funciones que retornan un código de error explícito — no todas siguen la misma convención, y hay que revisar la firma real en `defs.h` en vez de asumirla.
* La importancia de compilar y probar en un entorno real (toolchain de RISC-V + QEMU) antes de dar por buena una implementación: dos de mis errores solo se detectaron al compilar de verdad, no leyendo el código.
* Por qué las estructuras compartidas del kernel (listas de memoria libre, tabla de procesos) necesitan spinlocks incluso para operaciones de "solo lectura" en un sistema multiprocesador.
* Cómo funciona la transferencia segura de datos entre espacios de memoria distintos (kernel/usuario) mediante `copyout()`.
* Manejo de un flujo de trabajo colaborativo en Git con ramas modulares (`rama/sysinfo`), incluyendo la depuración de un `.gitignore` mal configurado que bloqueaba silenciosamente mis commits.