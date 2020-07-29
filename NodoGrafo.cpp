//
// Created by Emiliano Ruiz on 25/07/2020.
//
#include "NodoGrafo.h"

NodoGrafo::NodoGrafo(string datoNuevo) {
    siguiente = 0;
    this -> nombre = datoNuevo;
}


NodoGrafo::~NodoGrafo() {
    siguiente = 0;
}


void NodoGrafo::asignarSiguiente(NodoGrafo *ps) {
    siguiente = ps;
}


NodoGrafo * NodoGrafo::obtenerSiguiente() {
    return siguiente;
}

string NodoGrafo::obtenerNombre() {
    return nombre;
}

void NodoGrafo::insertarArista(Arista nueva) {
    aristas.push_back(nueva);
}

vector<Arista> NodoGrafo::obtenerCaminos() {
    return aristas;
}