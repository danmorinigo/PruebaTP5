#ifndef COLAPRIORIDAD_H_INCLUDED
#define COLAPRIORIDAD_H_INCLUDED
#include "nodoColaPrioridad.h"
class ColaPrioridad{
private:

    NodoColaPrioridad* primero;
    NodoColaPrioridad* primeroSegunPrioridad;
    NodoColaPrioridad* ultimo;
    int criterioOrden;//1-> pesoEntero / 2-> pesoDouble
public:

    ColaPrioridad(int criterioOrden);
    bool vacia();
    Vertice* topAndPop();
    Vertice* topVertice();
    int topPrioridad();
    int topEntero();
    double topDouble();
    void pop();
    void push(Vertice* evaluado, int pesoEntero, double pesoDouble, int iteracion);
    ~ColaPrioridad();
private:
    void insertarAlFinal(NodoColaPrioridad* aInsertar);
    //void insertarAlFinal(NodoColaPrioridad* aInsertar);
};


#endif // COLAPRIORIDAD_H_INCLUDED
