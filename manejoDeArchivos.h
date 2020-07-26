#ifndef MANEJODEARCHIVOS_H_INCLUDED
#define MANEJODEARCHIVOS_H_INCLUDED
#include <fstream>

#include "BST.h"
#include "aeropuerto.h"

using namespace std;

class manejoDeArchivos{
private:
public:
    manejoDeArchivos();
    bool existe(string nombreArchivo);
    void cargarAeropuertos(BST<Aeropuerto*>* arbol, string nombreArchivo);
    ~manejoDeArchivos();
};
#endif // MANEJODEARCHIVOS_H_INCLUDED
