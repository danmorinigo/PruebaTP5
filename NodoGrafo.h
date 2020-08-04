//
// Created by Emiliano Ruiz on 25/07/2020.
//

#ifndef GRAFO_NODOGRAFO_H
#define GRAFO_NODOGRAFO_H
#include <string>
#include <iostream>
#include "Arista.h"
#include <vector>
#include <queue>

using namespace std;


class Arista;

class NodoGrafo{

private:

    string nombre;
    NodoGrafo * siguiente;
    vector<Arista> aristas;
    bool visitado;



public:
    //Constructor con parametro
    // PRE : Ninguna
    // POST : Crea un nodo con el dato d y el puntero a NULL
    NodoGrafo(string nombre);

    // Destructor
    // PRE : Nodo creado
    // POST : No hace nada
    ~NodoGrafo();

    // PRE : nodo creado
    // POST : el puntero al siguiente nodo apuntará a ps
    void asignarSiguiente(NodoGrafo * ps);

    void insertarArista(Arista nueva);

    bool obtenerVisitado();
    void definirVisitado(bool estado);

    string obtenerNombre();
    // PRE : nodo creado
    // POST : Devuelve el puntero al siguiente nodo
    // Si es el último devuelve NULL
    NodoGrafo * obtenerSiguiente();

    vector<Arista> obtenerCaminos(); //Metodo que devuelve todos los caminos de un vertice

};


#endif //GRAFO_NODOGRAFO_H
