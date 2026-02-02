#include "bitacora.h"
#include <iostream>
#include <fstream>
#include <cstdint>

bool validarRegistro(const Registro& r){
    if (r.felicidad < 0 || r.felicidad > 100){
        cout<<"Felicidad fuera de rango"<<endl;
        return false; 
    } else if (r.energia < 0 || r.energia > 100){
        cout<<"Energia fuera de rango"<<endl;
        return false;
    } else if (r.horas_sueno < 0 || r.horas_sueno > 24){
        cout<<"Horas de sueno fuera de rango"<<endl;
        return false;
    } else{
        return true;
    }
}

void agregarRegistro(Registro *& arr , int& n, const Registro& nuevo){
    Registro* nuevoArr = new Registro[n + 1];
    for (int i = 0; i < n; i++) {
        nuevoArr[i] = arr[i];
    }
    nuevoArr[n] = nuevo;
    delete[] arr;
    arr = nuevoArr;
    n++;
}

bool cargarBD(const std:: string& ruta , Registro *& arr , int& n){
    ifstream in(ruta, ios::binary);
    //Validacion del archivo
    if (!in){
        cout<<ruta<<" No existe"<<endl;
        return false;
    }
    uint32_t N;
    if (!in.read(reinterpret_cast<char*>(&N), sizeof(N))){
        cout<<"BD corrupta o formato inválido"<<endl;
        return false;
    }
    //Si el archivo esta vacio se devuelve de inmediato
    if (N == 0){
        arr = nullptr;
        n = 0;
        cout<<ruta<<" esta vacio"<<endl;
        return true;
    }
    
    arr = new Registro[N];
    n = static_cast<int>(N);
    //Lectura de los registros
    for (int i=0; i<n; i++){
        // Nombre
        uint16_t name_len;
        if (!in.read(reinterpret_cast<char*>(&name_len), sizeof(name_len))){
            return false;
        } else if (name_len == 0 || name_len > 500){
            return false;
        }
        arr[i].nombre.resize(name_len);
        if (!in.read(&arr[i].nombre[0], name_len)){
            return false;
        }
        // Emocion
        uint8_t emocion;
        if (!in.read(reinterpret_cast<char*>(&emocion), 1)){
            return false;
        } else if (emocion > 3){
            return false;
        }

        arr[i].emocion = static_cast<Emocion>(emocion);
        //Atributos restantes
        uint8_t felicidad, energia, horas, aguacate;
        if (!in.read(reinterpret_cast<char*>(&felicidad), 1) ||
            !in.read(reinterpret_cast<char*>(&energia), 1) ||
            !in.read(reinterpret_cast<char*>(&horas), 1) ||
            !in.read(reinterpret_cast<char*>(&aguacate), 1)) {
            delete[] arr;
            return false;
        }
        if (felicidad > 100 || energia > 100 || horas > 24 || aguacate > 1){
            delete[] arr;
            return false;
        }
        arr[i].felicidad = felicidad;
        arr[i].energia = energia;
        arr[i].horas_sueno = horas;
        arr[i].comio_aguacate = (aguacate == 1);

    }
    return true;
}

bool guardarBD(const std:: string& ruta , Registro*& arr , int n){
    ofstream out(ruta, ios::binary);
    if (!out){
        return false;
    }
    //Escribir cantidad de registros
    uint32_t N = static_cast<uint32_t>(n);
    out.write(reinterpret_cast<char*>(&N), sizeof(N));
    if (!out){
        return false;
    }
    //Escribir cada uno de los registros
    for (int i = 0; i < n; i++) {
        // Nombre
        uint16_t name_len = static_cast<uint16_t>(arr[i].nombre.size());
        out.write(reinterpret_cast<char*>(&name_len), sizeof(name_len));
        out.write(arr[i].nombre.data(), name_len);
        // Emocion
        uint8_t emocion = static_cast<uint8_t>(arr[i].emocion);
        out.write(reinterpret_cast<char*>(&emocion), 1);
        //Atributos restantes
        uint8_t felicidad = static_cast<uint8_t>(arr[i].felicidad);
        uint8_t energia = static_cast<uint8_t>(arr[i].energia);
        uint8_t horas = static_cast<uint8_t>(arr[i].horas_sueno);
        uint8_t aguacate = arr[i].comio_aguacate ? 1 : 0;
        out.write(reinterpret_cast<char*>(&felicidad), 1);
        out.write(reinterpret_cast<char*>(&energia), 1);
        out.write(reinterpret_cast<char*>(&horas), 1);
        out.write(reinterpret_cast<char*>(&aguacate), 1);
    }
    return true;
}

Registro* buscarPorNombre(Registro* arr , int n, const std:: string& nombre){
    Registro* encontrado = nullptr;
    int coincidencias = 0;
    for (int i=0; i<n; i++){
        if((arr+i)->nombre == nombre){
            encontrado = arr+i;
            coincidencias ++;
        }
    }
    if (coincidencias > 1){
        cout <<"Se encontro mas de un registro con el mismo nombre. Devolviendo el primero"<<endl;
    }
    return encontrado;
}

int nivelAndoriano(const Registro& r){
    int base = (r.felicidad + r.energia)/2;
    if( r.horas_sueno >= 7){
        base +=10;
    } else{
        base -=10;
    }
    if (base < 0){
        base = 0;
    }
    if (base > 100){
        base = 100;
    }
    return base;
}
double promedioUltimosK(Registro* arr , int n, int k){
    double calculado=0;
    if (n < k){
        for (int i=0; i<n; i++){
            Registro r = *(arr+i);
            int suma = nivelAndoriano(r);
            calculado += suma;
        }
        calculado = calculado/n;
    } else{
        for (int i=0; i<k; i++){
            Registro r = *(arr+i);
            int suma = nivelAndoriano(r);
            calculado += suma;
        }
        calculado = calculado/k;
    }
    return calculado;
}
