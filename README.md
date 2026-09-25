# Proyecto 2 - System Calls en xv6

## Información General

- **Curso:** Sistemas Operativos (2026-2)
- **Institución:** Universidad EAFIT
- **Docente:** José Luis Montoya Pareja
- **Integrantes:**
  - Miguel Ángel Alzate Chavarria
  - Samuel Quintero

---

## Descripción de la Solución

En este proyecto se extendió el núcleo del sistema operativo **xv6-riscv** mediante la implementación de dos nuevas llamadas al sistema (syscalls) orientadas a la observabilidad, monitoreo e introspección del kernel:

1. **`trace`**: Permite realizar un seguimiento en tiempo real de una llamada al sistema específica ejecutada por un proceso. Captura e imprime en consola el PID del proceso, la syscall interceptada, el valor de retorno y el estado de los registros clave del procesador RISC-V (`s0`, `s1`, `a0`, `a1`) al salir de la llamada.
2. **`sysinfo`**: Recopila métricas del estado interno del sistema en tiempo real y las transfiere desde espacio de kernel hacia espacio de usuario utilizando una estructura dedicada (`struct sysinfo`). Reporta la memoria libre disponible (MB), el total de páginas utilizadas, las páginas disponibles y la cantidad de procesos en estado `RUNNABLE`.

---

## Archivos Modificados y Creados

| Archivo | Tipo | Descripción de la Modificación |
| :--- | :--- | :--- |
| `Autoevaluaciones/AUTOEVALUACION1.MD` | Creado | Autoevaluación individual de Miguel Ángel Alzate Chavarria. |
| `Autoevaluaciones/AUTOEVALUACION2.MD` | Creado | Autoevaluación individual de Samuel Quintero. |
| `kernel/sysinfo.h` | Creado | Define la estructura `struct sysinfo` compartida entre kernel y usuario. |
| `user/sysinfo.c` | Creado | Programa de usuario para invocar y desplegar la información recibida de `sysinfo`. |
| `user/sysinfotest.c` | Creado | Programa de pruebas automatizadas para verificar el correcto funcionamiento de `sysinfo`. |
| `user/trace.c` | Creado | Programa de usuario que configura la syscall a monitorear y ejecuta el comando objetivo. |
| `kernel/proc.h` | Modificado | Inclusión del campo `trace_syscall` dentro de `struct proc` para almacenar el identificador a monitorear. |
| `kernel/proc.c` | Modificado | Limpieza de `trace_syscall` en `freeproc()`, propagación del parámetro en `fork()` para subprocesos e implementación de `countrunnable()`. |
| `kernel/kalloc.c` | Modificado | Implementación de `countfreepages()` para el conteo de memoria física libre disponible. |
| `kernel/syscall.c` | Modificado | Intercepción en `syscall()`, validación contra `p->trace_syscall` e impresión formateada de PID, retorno y registros RISC-V. |
| `kernel/sysproc.c` | Modificado | Implementación de los handlers `sys_trace()` y `sys_sysinfo()` con empaquetamiento y copia segura vía `copyout()`. |
| `kernel/syscall.h` | Modificado | Definición de las constantes numéricas `SYS_trace` y `SYS_sysinfo`. |
| `kernel/defs.h` | Modificado | Declaración de prototipos del kernel (`countrunnable`, `countfreepages`, `ireclaim`, `uvmclear`). |
| `user/user.h` | Modificado | Prototipos de funciones de usuario para las syscalls `trace()` y `sysinfo()`. |
| `user/usys.pl` | Modificado | Entrada de stubs en ensamblador para la generación automatizada de las llamadas en espacio de usuario. |
| `Makefile` | Modificado | Registro de los ejecutables `_trace`, `_sysinfo` y `_sysinfotest` en la regla `UPROGS`. |
| `.gitignore` | Modificado | Reglas de exclusión para evitar la subida de ejecutables generados y binarios de compilación. |
---

## Decisiones de Diseño Realizadas

- **Mecanismo de Rastreación en `trace`**:
  Se optó por almacenar de forma explícita el número entero de la syscall solicitada en el atributo `p->trace_syscall` de la estructura del proceso (`struct proc`), realizando la comparación directa (`==`) durante la interrupción por *trap* en `syscall()`. Esto garantiza sencillez, bajo overhead en tiempo de ejecución y exactitud en la intercepción.

- **Herencia entre Procesos (`fork`)**:
  Para prevenir la pérdida del rastreo cuando un programa monitoreado crea subprocesos, la variable `trace_syscall` se clona explícitamente desde el proceso padre hacia el proceso hijo durante la ejecución de `fork()` en `kernel/proc.c`.

- **Seguridad Kernel-Usuario en `sysinfo`**:
  Para la recolección de métricas del sistema, la lectura de páginas y tabla de procesos se efectúa protegiendo las estructuras internas mediante *spinlocks*. La transferencia de datos hacia espacio de usuario se efectúa estrictamente a través de `copyout()`, validando las direcciones de memoria virtual para evitar lecturas arbitrarias o pánicos del kernel.

---

## Compilación y Ejecución

### Requisitos Previos

- Cadena de herramientas *cross-compiler* para `riscv64-unknown-elf-gcc`.
- Emulador **QEMU** para arquitectura RISC-V.

### 1. Compilación Limpia

Para compilar el sistema operativo desde cero y limpiar ejecutables previos:

```bash
make clean
make qemu
```

### 2. Comandos de Prueba en xv6

**Prueba de `sysinfo`:**

```bash
$ sysinfo
```

Muestra la memoria disponible en MB, páginas usadas, páginas libres y procesos ejecutables.

**Prueba de `trace`:**

```bash
$ trace 16 echo hola
```

Rastrea la llamada al sistema de escritura (`SYS_write = 16`) durante la ejecución de `echo`.

---

## Enlace de Evidencia en Video

**Video Demostrativo del Proyecto:**  link: https://drive.google.com/file/d/1fYigRpb1rmIm8-H8nYJFa6PWg3d9W_f3/view?usp=sharing

(Incluye evidencia de compilación con `make clean && make qemu`, ejecución de `sysinfo` y captura de registros mediante `trace`).

---

## Declaración de Uso de IA Generativa

De acuerdo con la política institucional y la guía del proyecto, se declara la utilización de herramientas de Inteligencia Artificial Generativa (Gemini y Claude) durante el desarrollo:

- **Uso Realizado:** Apoyo en el diagnóstico de errores de enlazado y tipos en `defs.h`, depuración de firmas de funciones de gestión de memoria (`kalloc.c`/`vm.c`), corrección de paso de parámetros en el programa de usuario `sysinfo.c` y estructuración de la documentación técnica.
- **Declaración de Responsabilidad:** Todos los integrantes del equipo comprendemos en su totalidad la implementación entregada, su flujo dentro del kernel de xv6-riscv, la arquitectura de manejo de llamadas al sistema y asumimos la responsabilidad plena de su autoría y funcionamiento.
