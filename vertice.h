#ifndef VERTICE_H_INCLUDED
#define VERTICE_H_INCLUDED
#include <iostream>
#include "Arista.h"

using namespace std;

class Vertice{
private:
    Vertice* siguiente;
    Arista* arista;
    string nombre;
public:
    // Constructor sin parametros de la clase Vertice.
    //PRE: Ninguna
    //POST: Se crea un objeto de Clase Vertice.
    Vertice(string nombre);

    //Destructor de la clase Vertice
    ~Vertice();

    //PRE:Debe existir el objeto de clase Vertice
    //POST: Se le asigna al atributo siguiente el valor ingresado por parametro.
    void asignarProxVertice(Vertice* siguiente);

    //PRE:--
    //POST: Se agrega al atributo arista el parametro ingresado.
    void agregarArista(Arista* nuevaArista);

    //PRE: --
    //POST: Se elimina la arista recibida por parametro.
    void eliminarArista(Arista* aristaAeliminar);
    
    //PRE:  Debe existir el objeto de clase Vertice.
    //POST: Devuelve el valor del atributo siguiente.
    Vertice* obtenerProxVertice();

    //PRE: Debe existir el objeto de clase Vertice
    //POST: devuelve el valor del atributo arista.
    Arista* obtenerAristas();

    //PRE: Debe existir el objeto de clase Vertice.
    //POST: Devuelve el valor del atributo nombre.
    string obtenerNombreVertice();
};


#endif // VERTICE_H_INCLUDED
