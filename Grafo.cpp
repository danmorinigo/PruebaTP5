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
    while (aux != nullptr){
        if (aux -> obtenerNombre() == nombre){
            return aux;
        }
        aux = aux -> obtenerSiguiente();
    }
    return nullptr;
}

void Grafo::insertarArista(NodoGrafo *origen, NodoGrafo *destino, int precio, float horas) {

    Arista nueva(precio, horas, destino);
    origen -> insertarArista(nueva);

}

Arista Grafo::obtenerArista(NodoGrafo *origen, NodoGrafo *destino) {
    int i = 0;
    vector<Arista> aux = origen -> obtenerCaminos();

    while (  i < (aux.size()) ) {
        if (destino == aux[i].obtenerVerticeApunta()) {
            return aux[i];                          //ESTO HAY QUE CAMBIARLO ES MALA PRACTICA.
        }
        i++;
    }
}


int Grafo::mejorCamino(NodoGrafo *origen, NodoGrafo *destino) {

    priority_queue<verticeCosto> colaPrioridad;
    vector<Arista> aux;
    vector<verticeCosto> distancia;

    NodoGrafo * verticeActual;
    int costoActual;
    setearVerticesComoNoVistos();
    setearDistanciaInfinito(&distancia);

    colaPrioridad.push(verticeCosto(origen, 0));
    cambiarDistancia(&distancia, origen, 0);

    while (!colaPrioridad.empty()){
        verticeActual = colaPrioridad.top().first;
        costoActual = colaPrioridad.top().second;
        colaPrioridad.pop();
        verticeActual->definirVisitado(true);
        aux = verticeActual -> obtenerCaminos();
        if (verticeActual == destino){
             return obtenerDistancia(&distancia, verticeActual);
        }
        for (int i = 0; i < aux.size(); i++) {
            if (!(aux[i].obtenerVerticeApunta() -> obtenerVisitado())){
                actualizarCosto(&colaPrioridad, costoActual, aux[i].obtenerVerticeApunta(), aux[i].obtenerCosto(), &distancia);
            }
        }
    }
    return -1;
}

void Grafo::actualizarCosto(priority_queue<verticeCosto> * colaPrioridad, int costoActual, NodoGrafo *adyacente, int costo, vector<verticeCosto> * distancia) {
    if ((costoActual + costo) <= obtenerDistancia(distancia, adyacente)){
        colaPrioridad->push(verticeCosto(adyacente, costoActual + costo));
        cambiarDistancia(distancia, adyacente, costoActual + costo);
    }
}

void Grafo::setearVerticesComoNoVistos() {
    for (int i = 1; i <= obtenerTamanio(); i++) {
        obtenerNodo(i)->definirVisitado(false);
    }
}

void Grafo::setearDistanciaInfinito(vector<verticeCosto> *distancia) {
    for (int i = 1; i <= obtenerTamanio(); ++i) {
        distancia->push_back(verticeCosto(obtenerNodo(i), 99999999999));
    }
}

void Grafo::cambiarDistancia(vector<verticeCosto> *distancia, NodoGrafo *vertice, int valor) {
    int iterador = 0;
    while (vertice -> obtenerNombre() != distancia -> at(iterador).first -> obtenerNombre()){
        iterador++;
    }
    distancia -> at(iterador) = verticeCosto(vertice, valor);
}

int Grafo::obtenerDistancia(vector<verticeCosto> *distancia, NodoGrafo * vertice){
    int iterador = 0;
    while (vertice -> obtenerNombre() != distancia -> at(iterador).first -> obtenerNombre()){
        iterador++;
    }
    return distancia -> at(iterador).second;
}