#ifndef VERTICE_H_INCLUDED
#define VERTICE_H_INCLUDED
#include <iostream>
#include "Arista2.h"

using namespace std;

class Vertice{
private:
    Vertice* siguiente;
    Arista2* arista;
    string nombre;
public:
    Vertice(string nombre);
    ~Vertice();
    void asignarProxVertice(Vertice* siguiente);
    void agregarArista(Arista2* nuevaArista);
    void aliminarArista(Arista2* aristaAeliminar);

    Vertice* obtenerProxVertice();
    Arista2* obtenerAristas();
    string obtenerNombreVertice();
};


#endif // VERTICE_H_INCLUDED
