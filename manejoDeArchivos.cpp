#include "manejoDeArchivos.h"

ManejoDeArchivos::ManejoDeArchivos(){
}

string ManejoDeArchivos::quitarGuion(string texto){
    for(unsigned i = 0; i < texto.length(); i++){
        if(texto[i] == '-'){
            texto[i] = ' ';
        }
    }
    return texto;
}

void ManejoDeArchivos::agregarAero(BST<Aeropuerto*>* arbol, string linea){
    istringstream cadena(linea);
    Aeropuerto* auxAero = new Aeropuerto;
    string auxS;
    unsigned auxU;
    double auxD;
    cadena >> auxS;
    auxAero->asignarCodigo(auxS);
    cadena >> auxS;
    auxAero->asignarNombre(quitarGuion(auxS));
    cadena >> auxS;
    auxAero->asignarCiudad(quitarGuion(auxS));
    cadena >> auxS;
    auxAero->asignarPais(quitarGuion(auxS));
    cadena >> auxD;
    auxAero->asignarSup(auxD);
    cadena >> auxU;
    auxAero->asignarTerminales(auxU);
    cadena >> auxU;
    auxAero->asignarDestNac(auxU);
    cadena >> auxU;
    auxAero->asignarDestInternac(auxU);
    arbol->insert(auxAero, auxAero->obtenerCodigo());
}

void ManejoDeArchivos::cargarAeropuertos(BST<Aeropuerto*>* arbol, string nombreArchivo){
    cout << "Procesando [" << nombreArchivo << "]..." << endl;
    unsigned contador = 0, errores = 0;
    ifstream archivoConDatos(nombreArchivo);
    string linea;
    while(!archivoConDatos.eof()){
        contador++;
        cout << "Linea " << contador << "-> ";
        getline(archivoConDatos, linea);
        if(chequear.esAeropuerto(linea)){
            agregarAero(arbol, linea);
            cout << "OK" << endl;
        }else{
            cout << "ERROR" << endl;
            errores++;
        }
    }
    archivoConDatos.close();
    cout << "Fin [" << nombreArchivo << "]" << endl;
    cout << contador << " lineas leidas.\n";
    cout << errores << " con errores.\n";
}


void ManejoDeArchivos::agregarVuelo(Grafo* vuelos, string linea){
    istringstream cadena(linea);
    string auxS;
    string auxS2;
    unsigned auxU;
    double auxD;

    cadena >> auxS;
    if (!vuelos->existeVertice(auxS)){
        vuelos->agregarVertice(auxS);
    }
    cadena >> auxS2;
    if (!vuelos->existeVertice(auxS2)){
        vuelos->agregarVertice(auxS2);
    }
    cadena >> auxU;
    cadena >> auxD;

    vuelos->agregarArista(vuelos->obtenerVertice(auxS),vuelos->obtenerVertice(auxS2),auxU,auxD);
}

void ManejoDeArchivos::cargarVuelos(Grafo* vuelos, string nombreArchivo){
    cout << "Procesando [" << nombreArchivo << "]..." << endl;
    unsigned contador = 0, errores = 0;
    ifstream archivoConDatos(nombreArchivo);
    string linea;
    while(!archivoConDatos.eof()){
        getline(archivoConDatos, linea);
        if(chequear.esVuelo(linea)){
          agregarVuelo(vuelos, linea);
        } else{
            errores++;
         }
    }
    archivoConDatos.close();
}

bool ManejoDeArchivos::existe(string nombreArchivo){
    ifstream auxiliar(nombreArchivo);
    bool hallado = !auxiliar.fail(); //TRUE existe
    auxiliar.close();
    return hallado;
}

ManejoDeArchivos::~ManejoDeArchivos(){
}
