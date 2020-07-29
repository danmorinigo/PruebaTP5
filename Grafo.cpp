//
// Created by Emiliano Ruiz on 25/07/2020.
//

#include "Grafo.h"

Grafo::Grafo() {
    primero = 0;
    tam = 0;
}


Grafo::~Grafo() {
    while (!(grafoVacio()))
        eliminarDato(1);
}


bool Grafo::grafoVacio() {
    return ( primero == 0);
}


void Grafo::insertarVertice(string nombre, unsigned int pos) {
    NodoGrafo * nuevo = new NodoGrafo(nombre);
    if (pos == 1){
        nuevo -> asignarSiguiente(primero);
        primero = nuevo;
    } else {
        NodoGrafo * anterior = obtenerNodo(pos - 1);
        nuevo -> asignarSiguiente(anterior -> obtenerSiguiente());
        anterior -> asignarSiguiente(nuevo);
    }
    tam++;
}


void Grafo::eliminarDato(unsigned pos) {
    NodoGrafo * borrar = primero;
    if (pos == 1){
        primero = borrar -> obtenerSiguiente();
    } else {
        NodoGrafo * anterior = obtenerNodo( pos - 1);
        borrar = anterior -> obtenerSiguiente();
        anterior -> asignarSiguiente(borrar -> obtenerSiguiente());
    }
    delete borrar;
    tam--;
}


unsigned Grafo::obtenerTamanio() {
    return tam;
}

NodoGrafo * Grafo::obtenerNodo(unsigned int pos) {
    NodoGrafo * aux = primero;
    unsigned i = 1;
    while (i < pos){
        aux = aux -> obtenerSiguiente();
        i++;
    }
    return aux;
}

NodoGrafo * Grafo::obtenerVertice(string nombre) {
    NodoGrafo * aux = primero;
    while (aux != NULL){
        aux = aux -> obtenerSiguiente();
        if (aux -> obtenerNombre() == nombre){
            return aux;
        }
    }
    return NULL;
}

void Grafo::insertarArista(NodoGrafo *origen, NodoGrafo *destino, int precio, float horas) {
    Arista nueva;
    nueva.insertarCosto(precio);
    nueva.insertarHorasVuelo(horas);
    nueva.insertarVerticeApunta(destino);
    origen -> insertarArista(nueva);
}

Arista Grafo::obtenerArista(NodoGrafo *origen, NodoGrafo *destino) {
    int i = 0;
    vector<Arista> aux = origen -> obtenerCaminos();

    while (  i < (aux.size()) ){
        if (destino == aux[i].obtenerVerticeApunta()){
            return aux[i];                          //ESTO HAY QUE CAMBIARLO ES MALA PRACTICA.
        }
        i++;
    }
}