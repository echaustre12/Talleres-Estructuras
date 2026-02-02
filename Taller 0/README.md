## **Taller 0 - Estructuras de Datos**
### **Luis Esteban Chaustre Garzon**
### **Profesor: Ing. Santiago "Primo" Chaustre**

En este taller introductorio a la asignatura de **Estructuras de Datos**, se refrescan algunos conceptos vistos en la asignatura de **Programación Avanzada** en el lenguaje **C++**, los cuales se trataron de manejar de la mejor forma posible con base en lo que se recordaba.

Como novedad principal, se trabajó la **compilación desde la terminal**, en lugar de un IDE, como se venía realizando en semestres anteriores.

---

### *Comandos para compilar*

Para compilar un programa en C++ a través de la terminal es necesario contar con un compilador como `g++`.

En este caso específico, el desarrollo se realizó en un sistema operativo **Windows**, utilizando la terminal **MSYS2 UCRT64**, lo que facilitó la instalación de las dependencias necesarias.

Antes de compilar, es indispensable ubicarse en el directorio donde se encuentran los archivos fuente.

- Comando de compilación:
  ```bash
  g++ -std=c++11 -Wall -Wextra -pedantic -o bitacora main.cpp bitacora.cpp
  ```
