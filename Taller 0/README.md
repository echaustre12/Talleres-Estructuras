## Taller 0 - Estructuras de Datos
### Luis Esteban Chaustre Garzon
### Profesor: Ing. Santiago "Primo" Chaustre

En este taller introductorio a la asignatura de Estructuras de Datos, se refrescan algunos conceptos vistos en la asignatura de Programación Avanzada en el lenguaje C++, los cuales se trataron de manejar de la mejor forma posible en base a lo que se recordaba, con una novedad que es: la compilación en terminal, en vez de en un IDE, como lo veníamos haciendo en semestres anteriores.

---

### Comandos para compilar

En orden de compilar un programa en C++ a través de la terminal se deben poder ejecutar ciertos comandos que requieren de extensiones como g++.

En mi caso específico, trabajo desde un sistema operativo Windows. Sin embargo, utilizo la terminal MSYS2 UCRT64, que me permitió descargar estos requisitos con mayor facilidad.

Para compilar el programa es necesario estar en el directorio en el que se encuentran los archivos.

Se utiliza el comando:

```bash
g++ -std=c++11 -Wall -Wextra -pedantic -o bitacora main.cpp bitacora.cpp
```

Después de esto ya se pueden realizar las funciones del programa por medio del ejecutable:

```bash
./bitacora
```

---

### Plan de pruebas

- init  
  Como primer paso para comprobar el funcionamiento adecuado del comando init, vamos a crear un nuevo archivo con nombre <bitacora.bd> con el comando:

  ```bash
  ./bitacora init bitacora.bd
  ```

  *El archivo bitacora.bd fue creado con exito (N=0)*

  Para la comprobación de que el comando init no crea un archivo que ya existe, ni lo modifica, usaremos nuevamente el comando:

  ```bash
  ./bitacora init bitacora.bd
  ```

  *El archivo bitacora.bd ya existe y no se modifico*

  En el caso hipotético en el que el archivo no se pueda crear por una ruta mala o cuestión de permisos, la salida esperada es:

  *ERROR: No se pudo crear el archivo*

- add  
  Para ingresar un nuevo registro al archivo que escojamos se utilizará el comando add. Un ejemplo de registro válido es:

  ```bash
  ./bitacora add bitacora.bd --nombre "Ana" --emocion Feliz --felicidad 85 --energia 70 --sueno 12 --aguacate S
  ```

  *bitacora.bd esta vacio*  
  *Registro guardado con exito. Total de registros en bitacora.bd: 1*

  En el caso que se ingrese una emoción distinta de las establecidas en el header bitacora.h, por ejemplo:

  ```bash
  ./bitacora add bitacora.bd --nombre "Ana" --emocion Deprimida --felicidad 85 --energia 70 --sueno 12 --aguacate S
  ```

  *La emocion ingresada no se reconoce*

  En el caso que se ingrese un valor de energía fuera del rango establecido:

  ```bash
  ./bitacora add bitacora.bd --nombre "Ana" --emocion Feliz --felicidad 85 --energia 180 --sueno 12 --aguacate S
  ```

  *Energia fuera de rango*

- list  
  El comando list se utiliza para mostrar en la terminal todos los registros que existen en un archivo.

  Para un archivo vacío, la salida esperada es:

  *<nombre_archivo> esta vacio*  
  *Bitacora Andoriana - 0 registros*

  Para un archivo con información previamente agregada:

  ```bash
  ./bitacora list bitacora.bd
  ```

  *Bitacora Andoriana - 1 registros*  
  *[1] Ana | Feliz | F=85 E=70 | sueno=12 | aguacate= Si :)*

  En el caso hipotético de que el archivo esté corrompido:

  *BD corrupta o formato inválido*

- find  
  El comando find se encarga de buscar un registro por nombre.

  ```bash
  ./bitacora find bitacora.bd --nombre "Ana"
  ```

  *Encontrado:*  
  *Ana | Feliz | F=85 E=70 | sueno=12 | aguacate= Si :)*

  Si el registro no existe:

  ```bash
  ./bitacora find bitacora.bd --nombre "Esteban"
  ```

  *Registro no encontrado en bitacora.bd*

  En el caso de encontrar más de un registro con el mismo nombre:

  *Se encontro mas de un registro con el mismo nombre. Devolviendo el primero*  
  *Encontrado:*  
  *Ana | Feliz | F=85 E=70 | sueno=12 | aguacate= Si :)*

- stats (n=0 / n<k / n>=k / k inválido)  
  El comando stats realiza operaciones usando los valores contenidos en los registros.

  Archivo sin registros:

  *<nombre_archivo> esta vacio*  
  *No se puede realizar ninguna operación*

  Caso n < k:

  *Stats Andorianas*  
  *Registros disponibles: 2*  
  *K solicitado: 9 (se usaran 2)*  
  *Promedio nivel andoriano (ultimos 2): 52*

  Caso n >= k:

  *Stats Andorianas*  
  *Registros disponibles: 2*  
  *K solicitado: 2*  
  *Promedio nivel andoriano (ultimos 2): 52*

  Valor de k inválido:

  ```bash
  ./bitacora stats bitacora.bd --k -2
  ```

  *k solicitado invalido*

---

### Evidencia de depuración

