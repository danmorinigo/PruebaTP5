#include "manejoDeArchivos.h"

manejoDeArchivos::manejoDeArchivos(){
}
void manejoDeArchivos::cargarAeropuertos(BST<Aeropuerto*>* arbol, string nombreArchivo){
    if(existe(nombreArchivo)){
        ifstream archivoConDatos(nombreArchivo);
        Aeropuerto* auxAero;
        string auxS;
        unsigned auxU;
        double auxD;
        while(archivoConDatos >> auxS){
            auxAero = new Aeropuerto;
            auxAero->asignarCodigo(auxS);
            archivoConDatos >> auxS;
            auxAero->asignarNombre(auxS);
            archivoConDatos >> auxS;
            auxAero->asignarCiudad(auxS);
            archivoConDatos >> auxS;
            auxAero->asignarPais(auxS);
            archivoConDatos >> auxD;
            auxAero->asignarSup(auxD);
            archivoConDatos >> auxU;
            auxAero->asignarTerminales(auxU);
            archivoConDatos >> auxU;
            auxAero->asignarDestNac(auxU);
            archivoConDatos >> auxU;
            auxAero->asignarDestInternac(5);
            arbol->insert(auxAero, auxAero->obtenerCodigo());
        }
        archivoConDatos.close();
    }else{
        cout << "NO ARCHIVO" << endl;
    }
}
bool manejoDeArchivos::existe(string nombreArchivo){
    ifstream auxiliar(nombreArchivo);
    bool hallado = !auxiliar.fail(); //TRUE existe
    auxiliar.close();
    return hallado;
}
manejoDeArchivos::~manejoDeArchivos(){
}
