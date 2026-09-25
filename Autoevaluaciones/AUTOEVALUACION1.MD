# Autoevaluación Individual - Proyecto 2: System Calls en xv6

**Estudiante:** Miguel Ángel Alzate Chavarria
**Curso:** Sistemas Operativos (2026-2)
**Docente:** José Luis Montoya Pareja

## 1. Contribuciones Individuales

- **Desarrollo e implementación completa de la syscall `trace`:** Diseñé e implementé la syscall `trace` desde su interfaz inicial hasta la lógica interna del kernel (Fases 1, 2 y 3), incluyendo el programa de usuario `user/trace.c` y la propagación de herencia en `proc.c` (`fork`).
- **Depuración de la condición de intercepción en `trace`:** Identifiqué y corregí el error en `kernel/syscall.c` donde la condición comparaba `p->trace_syscall` como máscara de bits (`&`) cuando se almacenaba el número directamente; se corrigió usando comparación de igualdad (`==`), lo que permitió la impresión correcta de registros y retornos.
- **Resolución de compilación y enlazado global de `sysinfo`:** Depuré y solucioné los errores de prototipos y declaraciones cruzadas en `kernel/defs.h` y archivos del kernel, permitiendo que la syscall `sysinfo` enlazara y compilara correctamente con todo el sistema.
- **Integración, Git y Entregables:** Lideré el repositorio base, gestioné la integración mediante el merge de la rama `rama/sysinfo`, redacté la documentación completa en `README.md` y coordiné la entrega final con el enlace del video demostrativo.

## 2. Comprensión de la Implementación

Entiendo el flujo completo de ambas syscalls: cómo `trace` intercepta la ejecución en `syscall()` comparando el número de syscall activa contra el valor guardado en el proceso e imprimiendo el estado de los registros RISC-V, y cómo `sysinfo` recolecta métricas del kernel (memoria libre, páginas y procesos `RUNNABLE`) para transferirlas de forma segura al espacio de usuario mediante `copyout()`, respetando los límites de memoria virtual.

## 3. Principales Aprendizajes

- Diseño de mecanismos de interceptación en el kernel y la diferencia práctica entre el uso de máscaras de bits versus comparación directa (`==`).
- Mantenimiento de coherencia en las firmas declaradas en `kernel/defs.h` para evitar fallos de enlazado en C.
- Transferencia segura de datos entre kernel y usuario mediante `copyout()`.
- Flujo de trabajo en Git utilizando ramas modulares (`rama/sysinfo`), resolución de merges y trazabilidad de commits.