## **Taller 0 - Estructuras de Datos**
### **Luis Esteban Chaustre Garzon**
### **Profesor: Ing. Santiago 'Primo' Chaustre**

En este taller introductorio a la asignatura de Estructuras de Datos, se refrescan algunos conceptos vistos en la asignatura de Programación Avanzada en el lenguaje c++, los cuales se trataron de manejar de la mejor forma posible en base a lo que se recordaba, con una novedad que es: la compilación en terminal, en vez de en un IDE, como lo veníamos haciendo en semestres anteriores.

### *Comandos para compilar*
En orden de compilar un programa en c++ a traves de la terminal se deben de poder ejecutar ciertos comandos que requieren de extensiones como g++.
En mi caso especifico, trabajo desde un sistema operativo windows. Sin embargo utilizo la terminal MSYS2 UCRT64, que me permitió descargar estos requisitos con mayor facilidad.
Para compilar el programa es necesario estar en el directorio en el que se encuentran los archivos.
Se utiliza el comando:
g++ -std=c++11 -Wall -Wextra -pedantic -o bitacora main.cpp bitacora.cpp
Después de esto ya se pueden realizar las funciones del programa por medio del ejecutable ./bitacora

### *Plan de pruebas*
- init
Como primer paso para comprobar el funcionamiento adecuado del comando init, vamos a crear un nuevo archivo con nombre <bitacora.bd> con el comando:
*./bitacora init bitacora.bd*
En este caso la salida esperada es: 
*El archivo bitacora.bd fue creado con exito (N=0)*

Para la comprobación de que el comando init no crea un archivo que ya existe, ni lo modifica, usaremos nuevamente el comando:
*./bitacora init bitacora.bd*
En este caso la salida esperada es:
*El archivo bitacora.bd ya existe y no se modifico*

En el caso hipotetico en el que el archivo no se pueda crear por una ruta mala o cuestión de permisos la salida esperada es:
*ERROR: No se pudo crear el archivo*

- add
Para ingresar un nuevo registro al archivo que escojamos se utilizara el comando add, en este caso, un ejemplo de registro valido es:
./bitacora add bitacora.bd --nombre "Ana" --emocion Feliz --felicidad 85 --energia 70 --sueno 12 --aguacate S
En este caso la salida sera:
bitacora.bd esta vacio
Registro guardado con exito. Total de registros en bitacora.bd: 1
La salida nos informa que el archivo estaba vacio, y después confirma la creación de un registro, actualizando el numero de ellos que se tienen.

En el caso que se ingrese una emoción distinta de las establecidas en el header bitacora.h, como por ejemplo.
./bitacora add bitacora.bd --nombre "Ana" --emocion Deprimida --felicidad 85 --energia 70 --sueno 12 --aguacate S
La salida esperada es:
La emocion ingresada no se reconoce
Informando del problema que se presenta con una emoción distinta al enum.

En el caso que se ingrese un valor de energía fuera del rango establecido, como por ejemplo: 
$ ./bitacora add bitacora.bd --nombre "Ana" --emocion Feliz --felicidad 85 --energia 180 --sueno 12 --aguacate S
La salida esperada es: 
Energia fuera de rango
La salida en este caso informa de una situación anormal en el ingreso de ese valor.

list
El comando list se utiliza para mostrar en la terminal todos los registros que existen en un archivo. Para un archivo vacio la salida del comando sera:
<nombre_archivo> esta vacio
Bitacora Andoriana - 0 registros

Por otro lado, en un archivo con información previamente agregada de manera correcta, se espera que se impriman todos los registros, a modo de ejemplo usaremos el archivo que se viene trabajando, con el comando: 
./bitacora list bitacora.bd
Como salida se espera: 
Bitacora Andoriana - 1 registros
[1] Ana | Feliz | F=85 E=70 | sueno=12 | aguacate= Si :)

En el caso hipotetico de que el archivo este corrompido de alguna manera (Ej: que el header no coincida con el numero de registros), la salida que se espera es: 
BD corrupta o formato inválido

find
El comando find se encarga de buscar un registro por el nombre. A modo de prueba seguiremos trabajado en el archivo bitacora.bd, para un caso donde solo existe un registro, usando el comando: 
./bitacora find bitacora.bd --nombre "Ana"
La salida que recibiremos es:
Encontrado:
Ana | Feliz | F=85 E=70 | sueno=12 | aguacate= Si :)

Por el contrario, si buscamos un registro cuyo nombre no esta incluido en el archivo, por ejemplo: 
./bitacora find bitacora.bd --nombre "Esteban"
La salida que recibiremos es:
Registro no encontrado en bitacora.bd

Por ultimo en el caso en el que se encuentren dos registros con el mismo nombre, el programa nos avisara y recibiremos una salida como:
Se encontro mas de un registro con el mismo nombre. Devolviendo el primero
Encontrado:
Ana | Feliz | F=85 E=70 | sueno=12 | aguacate= Si :)

stats: n=0 / n<k / n>=k / k inválido
El comando stats realiza una serie de operaciones usando los valores contenidos en los registros de acuerdo con las especificaciones del taller.
En el primer caso, si se accede a un archivo que no tiene registros, la salida sera:
<nombre_archivo> esta vacio
No se puede realizar ninguna operación

Como segundo caso se tiene cuando se ingresa un numero mayor al total de registros que existen, la salida sera, a modo de ejemplo:
Stats Andorianas
Registros disponibles: 2
K solicitado: 9 (se usaran 2)
Promedio nivel andoriano (ultimos 2): 52

En el tercer caso, cuando el numero que se ingresa es igual o menor que el numero de registros con los que se cuentan en determinado archivo, la salida sera, a modo de ejemplo con el mismo archivo anterior:
Stats Andorianas
Registros disponibles: 2
K solicitado: 2
Promedio nivel andoriano (ultimos 2): 52

Por ultimo, cuando se ingresa un k invalido, como por ejemplo un numero negativo: 
./bitacora stats bitacora.bd --k -2
La salida esperada es: 
k solicitado invalido

Evidencia de depuración
