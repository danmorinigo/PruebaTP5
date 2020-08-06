//
// Created by Emiliano Ruiz on 25/07/2020.
//

#ifndef GRAFO_GRAFO_H
#define GRAFO_GRAFO_H
#include "NodoGrafo.h"
#include "VerticeCosto.h"

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

    void mejorCamino(NodoGrafo *origen, NodoGrafo * destino);

    void mostrarCamino(NodoGrafo * verticeActual, NodoGrafo * origen);

    void actualizarCosto(NodoGrafo * verticeActual,priority_queue<VerticeCosto> * colaPrioridad, NodoGrafo * adyacente, int costo, vector<VerticeCosto> * distancia);

    void setearVerticesComoNoVistos();

    void setearDistanciaInfinito(vector<VerticeCosto> * distancia);

    void cambiarDistancia(vector<VerticeCosto> * distancia, NodoGrafo * vertice, int valor);

    int obtenerDistancia(vector<VerticeCosto> * distancia, NodoGrafo * vertice);
};


#endif //GRAFO_GRAFO_H
