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
    int topPrecio();
    double topHoras();
    void pop();
    void push(Vertice* evaluado, int precio, double horas, int iteracion);
    ~ColaPrioridad();
private:
    void insertarAlFinal(NodoColaPrioridad* aInsertar);
    void insertarNuevoEnPrioridad(NodoColaPrioridad* aInsertar);
    void insertarOrdenado(NodoColaPrioridad* aInsertar);
    void actualizarPrioridad(NodoColaPrioridad* aInsertar);
    bool ordenPorPrecio();
    bool ordenPorHoras();
    void insertarElemento(NodoColaPrioridad* aInsertar);
};


#endif // COLAPRIORIDAD_H_INCLUDED
