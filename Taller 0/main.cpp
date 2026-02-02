#include "bitacora.h"
#include <iostream>
#include <fstream>
#include <cstdint>

void help();
int crear_base(const string& nombre_archivo);
bool crear_registro(int argc, char* argv[], Registro& nuevo);
void imprimir_registro(Registro n);
void imprimir_registro2(Registro* n);
bool faltan_argumentos(int argc, char* argv[]);

int main(int argc, char* argv[]){
    if (argc < 2){
        cout<<"Ingrese un argumento, para guia use help"<<endl;
        return 1;
    }
    bool completos = faltan_argumentos(argc, argv);
    if (!completos){
        cout<<"No se cumplen con el numero de argumentos. Para ayuda ./biatcora help"<<endl;
        return 1;
    }
    string arg = argv[1];
    if (arg == "help"){
        help();
    }
    else if (arg == "init"){
        string nombre_archivo = argv[2];
        int creado= crear_base(nombre_archivo);
        if (creado == 1){
            cout<<"El archivo "<<nombre_archivo<<" ya existe y no se modifico"<<endl;
        } else if (creado == 2){
            cout<<"ERROR: No se pudo crear el archivo"<<endl;
        } else if (creado == 3){
            cout<<"El archivo "<<nombre_archivo<<" fue creado con exito (N=0)"<<endl;
        }
    }
    else if (arg == "add"){
        Registro nuevo;
        string nombre_archivo = argv[2];
        if (!crear_registro(argc, argv, nuevo)) {
            return 1;
        } else{
            Registro* arr;
            int n=0;
            if (!cargarBD(nombre_archivo, arr, n)){
                cout<<"ERROR: no se modifico ningun dato"<<endl;
            } else{
                agregarRegistro(arr, n, nuevo);
                if(!guardarBD(nombre_archivo, arr, n)){
                    cout<<"ERROR: escritura"<<endl;
                } else{
                    cout<<"Registro guardado con exito. Total de registros en "<<nombre_archivo<<": "<<n<<endl;
                }
            }
        }
    }
    else if (arg == "list"){
        string nombre_archivo = argv[2];
        Registro* arr;
        int n;
        if (!cargarBD(nombre_archivo, arr, n)){
                cout<<"ERROR: no se modifico ningun dato"<<endl;
        } else{
            cout<<"Bitacora Andoriana - "<<n<<" registros"<<endl;
            for(int i=0; i<n; i++){
                cout<<"["<<i+1<<"] ";
                imprimir_registro(arr[i]);
            }
        }
    } 
    else if (arg == "find"){
        string nombre_archivo = argv[2];
        string nombre_buscar = argv[4];
        Registro* arr;
        int n;
        if (!cargarBD(nombre_archivo, arr, n)){
                cout<<"ERROR: no se modifico ningun dato"<<endl;
        } else{
            Registro* encontrado = buscarPorNombre(arr,n,nombre_buscar);
            if (encontrado == nullptr){
                cout<<"Registro no encontrado en "<<nombre_archivo<<endl;
            } else{
                cout<<"Encontrado:"<<endl;
                imprimir_registro2(encontrado);
            }
        }
    }
    else if (arg == "stats"){
        string nombre_archivo = argv[2];
        Registro* arr;
        int n;
        if (!cargarBD(nombre_archivo, arr, n)){
                cout<<"ERROR: no se modifico ningun dato"<<endl;
        } else if (n == 0){
            cout<<"No se puede realizar ninguna operacion"<<endl;
            return 1;
        } else{
            int k = stoi(argv[4]);
            if (k < 0){
                cout<<"k solicitado invalido"<<endl;
                return 1;
            }
            double calculado = promedioUltimosK(arr, n, k);
            cout<<"Stats Andorianas"<<endl<<"Registros disponibles: "<<n<<endl<<"K solicitado: "<<k;
            if(k > n){
                cout<<" (se usaran "<<n<<")";
            }
            cout<<endl<<"Promedio nivel andoriano ";
            if(k > n){
                cout<<"(ultimos "<<n<<"): ";
            } else{
                cout<<"(ultimos "<<k<<"): ";
            }
            cout<<calculado;
        }
    }
    else{
        cout<<"Comando no reconocido"<<endl;
        return 1;
    }
    return 0;
}

void help(){
    cout<<"Comandos disponibles:"<<endl;
    cout<<"  Iniciar base: ./ bitacora init <archivo.bd >"<<endl;
    cout<<"  Agregue un registro: ./ bitacora add <archivo.bd > --nombre <n> --emocion x --felicidad <0..100> --energia <0..100> --sueno <0..24> --aguacate <S|N>"<<endl;
    cout<<"  Liste todos los registros de la base: ./ bitacora list <archivo.bd >"<<endl;
    cout<<"  Busque un registro por nombre: ./ bitacora find <archivo.bd > --nombre <n>"<<endl;
    cout<<"  Estadisticas andorianas: ./ bitacora stats <archivo.bd > --k <entero >"<<endl;
}
int crear_base(const string& nombre_archivo){
    //Validar si el archivo existe
    ifstream in(nombre_archivo, ios::binary);
    if (in.good()) {
        return 1; 
    }
    //Archivo no existente, crearlo
    ofstream out(nombre_archivo, ios::binary);
    if (!out) {
        return 2; //Error
    }
    uint32_t N = 0;
    out.write(reinterpret_cast<char*>(&N), sizeof(N));
    return 3;
}
bool crear_registro(int argc, char* argv[], Registro& nuevo){
    //Validar si se cuenta con el numero necesario de entradas
    if (argc != 15){
        return false;
    }
    //Leer cada una de las entradas
    for (int i=3; i<argc; i+=2){
        string atributo = argv[i];
        string valor = argv[i + 1];
        if (atributo == "--nombre"){
            nuevo.nombre = valor;
        } else if (atributo == "--emocion"){
            if (valor == "Feliz"){
                nuevo.emocion = Feliz;
            } else if (valor == "Triste"){
                nuevo.emocion = Triste;
            } else if (valor == "Neutral"){
                nuevo.emocion = Neutral;
            } else if (valor == "Ansioso"){
                nuevo.emocion = Ansioso;
            } else{
                cout<<"La emocion ingresada no se reconoce"<<endl;
                return false; //Emocion invalida
            }
        } else if (atributo == "--felicidad"){
            nuevo.felicidad = stoi(valor);
        } else if (atributo == "--energia"){
            nuevo.energia = stoi(valor);
        } else if (atributo == "--sueno"){
            nuevo.horas_sueno = stoi(valor);
        } else if (atributo == "--aguacate"){
            if (valor == "S"){
                nuevo.comio_aguacate = true;
            } else if (valor == "N"){
                nuevo.comio_aguacate = false;
            } else{
                return false; //Ingreso invalido
            }
        }else{
            return false; //Atributo desconocido
        }
    }
    //Validar si todas las entradas tienen un formato valido
    if (!validarRegistro(nuevo)){
        return false;
    }
    return true;
}
void imprimir_registro(Registro n){
    cout<<n.nombre<<" | ";
    if (n.emocion == 0){
        cout<<"Feliz";
    } else if (n.emocion == 1){
        cout<<"Triste";
    } else if (n.emocion == 2){
        cout<<"Neutral";
    } else if (n.emocion == 3){
        cout<<"Ansioso";
    }
    cout<<" | F="<<n.felicidad<<" E="<<n.energia<<" | sueno="<<n.horas_sueno<<" | aguacate= ";
    if(n.comio_aguacate == 0){
        cout<<"No :(";
    } else if(n.comio_aguacate == 1){
        cout<<"Si :)";
    }
    cout<<endl;
}
void imprimir_registro2(Registro* n){
    cout<<n->nombre<<" | ";
    if (n->emocion == 0){
        cout<<"Feliz";
    } else if (n->emocion == 1){
        cout<<"Triste";
    } else if (n->emocion == 2){
        cout<<"Neutral";
    } else if (n->emocion == 3){
        cout<<"Ansioso";
    }
    cout<<" | F="<<n->felicidad<<" E="<<n->energia<<" | sueno="<<n->horas_sueno<<" | aguacate= ";
    if(n->comio_aguacate == 0){
        cout<<"No :(";
    } else if(n->comio_aguacate == 1){
        cout<<"Si :)";
    }
    cout<<endl;
}
bool faltan_argumentos(int argc, char* argv[]){
    string argumento = argv[1];
    bool n = true;
    if (argumento == "init"){
        if (argc != 3){
            n = false;
        }
    } else if (argumento == "add"){
        if (argc != 15){
            n = false;
        }
    } else if (argumento == "list"){
        if (argc != 3){
            n = false;
        }
    } else if (argumento == "find"){
        if (argc != 5){
            n = false;
        }   
    } else if (argumento == "stats"){
        if (argc != 5){
            n = false;
        }   
    }
    return n;
}

// g++ -std=c++11 -Wall -Wextra -pedantic -o bitacora main.cpp bitacora.cpp
