## **Taller 0 - Estructuras de Datos** ⭐ ✨
### Luis Esteban Chaustre Garzon 🚀
### Profesor: Ing. Santiago 'Primo' Chaustre 📝

En este taller introductorio a la asignatura de Estructuras de Datos, se refrescan algunos conceptos vistos en la asignatura de Programación Avanzada en el lenguaje C++, los cuales se trataron de manejar de la mejor forma posible en base a lo que se recordaba, con una novedad que es: la compilación en terminal, en vez de en un IDE, como lo veníamos haciendo en semestres anteriores.

---

### *Comandos para compilar* 🧠 🛠️ 

En orden de compilar un programa en C++ a través de la terminal se deben poder ejecutar ciertos comandos que requieren de extensiones como g++.

En mi caso específico, trabajo desde un sistema operativo Windows. Sin embargo, se utilizo la terminal MSYS2 UCRT64, que me permitió descargar estos requisitos con mayor facilidad.

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

### *Plan de pruebas* ✅ ❌ ⚠️

- *init* ▶️
  
  Como primer paso para comprobar el funcionamiento adecuado del comando init, vamos a crear un nuevo archivo con nombre <bitacora.bd> con el comando:

  ```bash
  ./bitacora init bitacora.bd
  ```
  En este caso la salida esperada es:
  
  *El archivo bitacora.bd fue creado con exito (N=0)*

  Para la comprobación de que el comando init no crea un archivo que ya existe, ni lo modifica, usaremos nuevamente el comando anterior, en este caso se deberá mostrar:

  *El archivo bitacora.bd ya existe y no se modifico*

  En el caso hipotético en el que el archivo no se pueda crear por una ruta mala o cuestión de permisos, la salida esperada es:

  *ERROR: No se pudo crear el archivo*

- *add* 📂
  
  Para ingresar un nuevo registro al archivo que escojamos se utilizará el comando add. Un ejemplo de registro válido es:

  ```bash
  ./bitacora add bitacora.bd --nombre "Ana" --emocion Feliz --felicidad 85 --energia 70 --sueno 12 --aguacate S
  ```
  Para este caso la salida será:

  *bitacora.bd esta vacio*  
  *Registro guardado con exito. Total de registros en bitacora.bd: 1*

  La salida nos informa que el archivo estaba vacio, y después confirma la creación de un registro, actualizando el numero de ellos que se tienen

  En el caso que se ingrese una emoción distinta de las establecidas en el header bitacora.h, por ejemplo:

  ```bash
  ./bitacora add bitacora.bd --nombre "Ana" --emocion Deprimida --felicidad 85 --energia 70 --sueno 12 --aguacate S
  ```
  La salida esperada es:

  *La emocion ingresada no se reconoce*

  Informando del problema que se presenta con un valor de emoción no permitido.

  En el caso que se ingrese un valor de energía fuera del rango establecido:

  ```bash
  ./bitacora add bitacora.bd --nombre "Ana" --emocion Feliz --felicidad 85 --energia 180 --sueno 12 --aguacate S
  ```
  La salida esperada es: 

  *Energia fuera de rango*

  Se informa de una situación anormal en el ingreso de ese valor.

- *list* 📄
  
  El comando list se utiliza para mostrar en la terminal todos los registros que existen en un archivo.

  Para un archivo vacío, la salida esperada es:

  *<nombre_archivo> esta vacio*  
  *Bitacora Andoriana - 0 registros*

  Para un archivo con información previamente agregada de manera correcta, se espera que se impriman todos los registros, a modo de ejemplo se usa el comando:

  ```bash
  ./bitacora list bitacora.bd
  ```
  Como salida se espera: 

  *Bitacora Andoriana - 1 registros*  
  *[1] Ana | Feliz | F=85 E=70 | sueno=12 | aguacate= Si :)*

  En el caso hipotético de que el archivo esté corrompido de alguna manera (Ej: que el header no coincida con el numero de registros), la salida que se espera es:

  *BD corrupta o formato inválido*

- *find* 🔍
  
  El comando find se encarga de buscar un registro por nombre. A modo de prueba seguiremos trabajado en el archivo bitacora.bd, para un caso donde solo existe un registro, usando el comando:

  ```bash
  ./bitacora find bitacora.bd --nombre "Ana"
  ```
  La salida que recibiremos es:

  *Encontrado:*  
  *Ana | Feliz | F=85 E=70 | sueno=12 | aguacate= Si :)*

  Si el registro no existe, en este caso de ejemplo:

  ```bash
  ./bitacora find bitacora.bd --nombre "Esteban"
  ```
  La salida que recibiremos es:

  *Registro no encontrado en bitacora.bd*

  En el caso de encontrar más de un registro con el mismo nombre, el programa nos avisara y recibiremos una salida como:

  *Se encontro mas de un registro con el mismo nombre. Devolviendo el primero*  
  *Encontrado:*  
  *Ana | Feliz | F=85 E=70 | sueno=12 | aguacate= Si :)*

- *stats* 📊
  
  El comando stats realiza operaciones usando los valores contenidos en los registros de acuerdo con las especificaciones del taller.

  Para un archivo sin registros la salida será:

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

  Valor de k inválido, como por ejemplo un numero negativo:

  ```bash
  ./bitacora stats bitacora.bd --k -2
  ```

  *k solicitado invalido*

---

### *Evidencia de depuración* 🧪🐛

Con el fin de realizar la depuración del código a lo largo de su realización se utilizó GDB, el cual permite ejecutar distintos comandos que muestran la ejecución de las tareas del programa en un bajo nivel.

Para utilizar el depurador es necesario compilar el código.

```bash
g++ -g -O0 main.cpp bitacora.cpp -o bitacora
```

Posteriormente se ejecuta: 

```bash
gdb ./bitacora
  ```

GDB ofrece la opcion de correr el programa con instrucciones especificas, con *run*:

```bash
run stats archivo.bd --k 3
  ```

En este caso, similar a la ejecucion con g++, también nos muestra el resultado de la operacion, aunque con otros datos de memoria: 

```bash
[New Thread 14912.0x90c]
[New Thread 14912.0xe84]
[New Thread 14912.0x226c]
Stats Andorianas
Registros disponibles: 5
K solicitado: 3
Promedio nivel andoriano (ultimos 3): 50.6667[Thread 14912.0x226c exited with code 0]
[Thread 14912.0x90c exited with code 0]
[Thread 14912.0xe84 exited with code 0]
[Inferior 1 (process 14912) exited normally]
```

GDB también permite hacer pausas en funciones específicas con el comando *break*, el cual fue utilizado para debuggear el programa. Se hace un *break* en una función especifica: 

```bash
(gdb) break agregarRegistro
```

Luego, se corre el programa con instrucciones que involucren esa función, en este caso:

```bash
(gdb) run add bitacora.bd --nombre Esteban --emocion Feliz --felicidad 78 --energia 40 --sueno 8 --aguacate N
```

Se notifica que la ejecución se detuvo debido al *break* definido:

```bash
[New Thread 4728.0x2464]
[New Thread 4728.0x440c]
[New Thread 4728.0x3444]
Thread 1 hit Breakpoint 1, 0x00007ff7af112bf9 in agregarRegistro(Registro*&, int&, Registro const&) ()
```

En este momento, podemos realizar la inspeccion del código de distintas maneras. La primera revisando que hat guardado en stack con el comando *backtrace*, recibiendo como salida en este caso:

```bash
#0  0x00007ff7af112bf9 in agregarRegistro(Registro*&, int&, Registro const&) ()
#1  0x00007ff7af1117b6 in main ()
```

El backtrace muestra la secuencia de funciones activas en el momento en que el programa se detuvo. Indica que la ejecución está actualmente en agregarRegistro, la cual fue llamada previamente desde main. 

Adicionalmente, se puede continuar la ejecución de manera manual utilizando el comando *step*, o imprimir el valor de una variable utilizando *print*, como se muestra en los ejemplos a continuación:

```bash
(gdb) print n
$1 = (int &) @0x5ffd64: 2
```

```bash
(gdb) print nuevo
$2 = (const Registro &) @0x5ffcf0: {nombre = "Esteban", emocion = Feliz, felicidad = 78,
  energia = 40, horas_sueno = 8, comio_aguacate = 0}
```

GDB es una herramienta fundamental para la depuración de código, ya que permite analizar la ejecución del programa paso a paso, inspeccionar el flujo de llamadas entre funciones y verificar el estado de las variables. Esto facilita la corrección de errores, brindando mayor control y comprensión sobre el comportamiento interno del programa durante su ejecución.

