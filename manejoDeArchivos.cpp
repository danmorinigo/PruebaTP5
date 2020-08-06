#include "manejoDeArchivos.h"

manejoDeArchivos::manejoDeArchivos(){
}

string manejoDeArchivos::quitarGuion(string texto){
    for(unsigned i = 0; i < texto.length(); i++){
        if(texto[i] == '-'){
            texto[i] = ' ';
        }
    }
    return texto;
}

void manejoDeArchivos::agregarAero(BST<Aeropuerto*>* arbol, string linea){
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

void manejoDeArchivos::cargarAeropuertos(BST<Aeropuerto*>* arbol, string nombreArchivo){
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

void manejoDeArchivos::agregarVuelo(Grafo* vuelos, string linea){
    istringstream cadena(linea);
    //Grafo* auxVuelo = new Grafo;
    string auxS;
    string auxS2;
    unsigned auxU;
    double auxD;

    cadena >> auxS;
    vuelos->insertarVertice(auxS, 1);
    cadena >> auxS2;
    vuelos->insertarVertice(auxS2, 1);
    
    cadena >> auxU;
    cadena >> auxD;

    vuelos->insertarArista(vuelos->obtenerVertice(auxS),vuelos->obtenerVertice(auxS2),auxU,auxD);
}

void manejoDeArchivos::cargarVuelos(Grafo* vuelos, string nombreArchivo){
    cout << "Procesando [" << nombreArchivo << "]..." << endl;
    unsigned contador = 0, errores = 0;
    ifstream archivoConDatos(nombreArchivo);
    string linea;
    while(!archivoConDatos.eof()){
        contador++;
        cout << "Linea " << contador << "-> ";
        getline(archivoConDatos, linea);
       if(linea != ""){
            cout << " Se va a cargar la linea: "<< linea<<endl;
            agregarVuelo(vuelos, linea);
            cout << "OK" << endl;
       }
    }
    archivoConDatos.close();
    cout << "Fin [" << nombreArchivo << "]" << endl;
    cout << contador << " lineas leidas.\n";
    cout << errores << " con errores.\n";
}

bool manejoDeArchivos::existe(string nombreArchivo){
    ifstream auxiliar(nombreArchivo);
    bool hallado = !auxiliar.fail(); //TRUE existe
    auxiliar.close();
    return hallado;
}
manejoDeArchivos::~manejoDeArchivos(){
}
