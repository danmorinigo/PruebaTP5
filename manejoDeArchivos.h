#ifndef MANEJODEARCHIVOS_H_INCLUDED
#define MANEJODEARCHIVOS_H_INCLUDED
#include <fstream>

#include "BST.h"
#include "aeropuerto.h"
#include "Grafo.h"
#include "verificadorDatos.h"

using namespace std;

class manejoDeArchivos{
private:
    VerificadorDatos chequear;
public:
    manejoDeArchivos();
    
    bool existe(string nombreArchivo);

    //antes verificar que existe el archivo!
    void cargarAeropuertos(BST<Aeropuerto*>* arbol, string nombreArchivo);

    //antes verificar que la linea sea un aeropuerto
    void agregarAero(BST<Aeropuerto*>* arbol, string linea);
    
    void cargarVuelos(Grafo* vuelos, string nombreArchivo);
    
    void agregarVuelo(Grafo* vuelos, string linea);

    string quitarGuion(string texto);
    ~manejoDeArchivos();
};
#endif // MANEJODEARCHIVOS_H_INCLUDED
