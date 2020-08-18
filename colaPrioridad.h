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
    //PRE:  criterioOrden debe ser valer 1 o 2
    //POST: Crea objeto indicandole cual sera el criterio por el cual hará las comparaciones al ordenar
    ColaPrioridad(int criterioOrden);

    //PRE:  --
    //POST: Devuelve true si primero apunta a null, caso contrario devuelve false.
    bool vacia();

    //PRE:  Cola no debe estar vacía.
    //POST: Devuelve Vertice* dentro del NodoColaPrioridad y elimina dicho nodo.
    Vertice* topAndPop();

    //PRE:  Cola no debe estar vacía.
    //POST: Devuelve Vertice* dentro del NodoColaPrioridad.
    Vertice* topVertice();

    //PRE:  Cola no debe estar vacía.
    //POST: Devuelve la prioridad actual de la cola.
    int topPrioridad();

    //PRE:  Cola no debe estar vacía.
    //POST: Devuelve pesoEntero de dentro del NodoColaPrioridad.
    int topPrecio();

    //PRE:  Cola no debe estar vacía.
    //POST: Devuelve pesoDouble de dentro del NodoColaPrioridad.
    double topHoras();

    //PRE:  Cola no debe estar vacía.
    //POST: Elimina primer nodo.
    void pop();

    //PRE:  Objeto evaluado debe estar creado, la iteracion no puede ser menor a la actualmente activa.
    //POST: Inserta dentro de la cola el Vertice* en el orden que le corresponde.
    void push(Vertice* evaluado, int precio, double horas, int iteracion);

    //PRE:  --
    //POST: Libera recursos utilizados.
    ~ColaPrioridad();
private:
    //PRE:  --
    //POST: Inserta al final de la cola.
    void insertarAlFinal(NodoColaPrioridad* aInsertar);

    //PRE:  --
    //POST: El nodo se inserta delante del que estaba primero en la prioridad actual.
    void insertarNuevoEnPrioridad(NodoColaPrioridad* aInsertar);

    //PRE:  --
    //POST: El nodo se inserta ordenandolo dentro de la actual prioridad.
    void insertarOrdenado(NodoColaPrioridad* aInsertar);

    //PRE:  --
    //POST: primeroSegunPrioridad apuntara a valor pasado como parametro.
    void actualizarPrioridad(NodoColaPrioridad* aInsertar);

    //PRE:  --
    //POST: Devuelve true si criterioOrden vale 1, sino devuelve false.
    bool ordenPorPrecio();

    //PRE:  --
    //POST: Devuelve true si criterioOrden vale 2, sino devuelve false.
    bool ordenPorHoras();

    //PRE:  --
    //POST: Se encarga de insertar el nodo cuando la cola ya tiene elementos cargados.
    void insertarElemento(NodoColaPrioridad* aInsertar);
};

#endif // COLAPRIORIDAD_H_INCLUDED
