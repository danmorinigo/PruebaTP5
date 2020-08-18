#ifndef NODOCOLAPRIORIDAD_H_INCLUDED
#define NODOCOLAPRIORIDAD_H_INCLUDED
#include<iostream>
#include "vertice.h"
const bool MEMORIA = false;
class NodoColaPrioridad{
private:
    Vertice* vertice;
    int prioridad;
    int pesoEntero;
    double pesoDouble;
    NodoColaPrioridad* siguiente;
public:
    //PRE:  Vertice* debe estar creado.
    //POST: Crea el nodo con los valores pasados como parametro.
    NodoColaPrioridad(Vertice* vertice, int prioridad, int pesoEntero, double pesoDouble);

    //PRE:  --
    //POST: Devuelve valor guardado en vertice.
    Vertice* obtenerVertice();

    //PRE:  --
    //POST: Devuelve valor guardado en prioridad.
    int getPrioridad();

    //PRE:  --
    //POST: Devuelve valor guardado en pesoEntero.
    int getEntero();

    //PRE:  --
    //POST: Devuelve valor guardado en pesoDouble.
    double getDouble();

    //PRE:  --
    //POST: Cambia el valor de siguiente por el pasado como parametro.
    void setSiguiente(NodoColaPrioridad* siguiente);

    //PRE:  --
    //POST: Devuelve valor guardado en siguiente.
    NodoColaPrioridad* getSiguiente();

    //PRE:  --
    //POST: --
    ~NodoColaPrioridad();
};
#endif // NODOCOLAPRIORIDAD_H_INCLUDED
