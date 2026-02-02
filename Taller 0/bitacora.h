#ifndef bitacora_h
#define bitacora_h

#include <string>
using namespace std;
//Validacion de las opciones de emociones
enum Emocion{
    Feliz=0, 
    Triste=1, 
    Neutral=2,
    Ansioso=3
};
//Definicion del tipo de dato Registro para manejo de Registros
struct Registro{
    string nombre;
    Emocion emocion;
    int felicidad;
    int energia;
    int horas_sueno;
    int comio_aguacate;
};
//Definicion de las funcionalidades del programa
bool validarRegistro(const Registro& r);
void agregarRegistro(Registro *& arr , int& n, const Registro& nuevo);
bool cargarBD(const std:: string& ruta , Registro *& arr , int& n);
bool guardarBD(const std:: string& ruta , Registro*& arr , int n);
Registro* buscarPorNombre(Registro* arr , int n, const std:: string& nombre);
int nivelAndoriano(const Registro& r);
double promedioUltimosK(Registro* arr , int n, int k);

#endif
