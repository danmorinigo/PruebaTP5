//
// Created by Emiliano Ruiz on 25/07/2020.
//

#ifndef GRAFO_GRAFO_H
#define GRAFO_GRAFO_H
#include "NodoGrafo.h"
typedef pair<NodoGrafo*, int> verticeCosto;

class Grafo{
    //Atributos

private:
    NodoGrafo * primero;
    int tam;


    //Metodos
public:
    // PRE : -
    // POST : construye una lista vacia
    Grafo();

    // PRE : lista creada
    // POST : Libera todos los recursos de la lista
    ~Grafo();

    // PRE : lista creada
    // POST : devuelve verdadero si la lista es vacia falso de lo contrario
    bool grafoVacio();

    // PRE : lista creada
    // POST : agrega un dato en la posicion pos incrementa tam en 1
    void insertarVertice(string nombre, unsigned pos);


    void insertarArista(NodoGrafo *origen, NodoGrafo *destino, int precio, float horas);

    // PRE : - lista creada y no vacia
    // - 0 < pos <= tam
    // POST : libera el nodo que esta en la posición pos se toma 1 como el primero
    void eliminarDato(unsigned pos);

    // PRE : Lista creada
    // POST : Devuelve tam ( cantidad de nodos de la lista )
    unsigned obtenerTamanio();

    // Obtiene un puntero al nodo de la posicion pos
    // PRE : 0 < pos <= tam
    // POST : devuelve un puntero al nodo solicitado
    NodoGrafo * obtenerNodo (unsigned pos);

    NodoGrafo * obtenerVertice (string nombre);

    Arista obtenerArista(NodoGrafo *origen, NodoGrafo *destino);

    int mejorCamino(NodoGrafo *origen, NodoGrafo * destino);

    void actualizarCosto(priority_queue<verticeCosto> * colaPrioridad, int costoActual, NodoGrafo * adyacente, int costo, vector<verticeCosto> * distancia);

    void setearVerticesComoNoVistos();

    void setearDistanciaInfinito(vector<verticeCosto> * distancia);

    void cambiarDistancia(vector<verticeCosto> * distancia, NodoGrafo * vertice, int valor);

    int obtenerDistancia(vector<verticeCosto> * distancia, NodoGrafo * vertice);
};


#endif //GRAFO_GRAFO_H
