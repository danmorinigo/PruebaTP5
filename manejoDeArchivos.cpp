#include "manejoDeArchivos.h"

manejoDeArchivos::manejoDeArchivos(){
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
    auxAero->asignarNombre(auxS);
    cadena >> auxS;
    auxAero->asignarCiudad(auxS);
    cadena >> auxS;
    auxAero->asignarPais(auxS);
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

bool manejoDeArchivos::existe(string nombreArchivo){
    ifstream auxiliar(nombreArchivo);
    bool hallado = !auxiliar.fail(); //TRUE existe
    auxiliar.close();
    return hallado;
}
manejoDeArchivos::~manejoDeArchivos(){
}
