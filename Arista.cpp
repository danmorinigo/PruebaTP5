//
// Created by Emiliano Ruiz on 25/07/2020.
//

#include "Arista.h"

Arista::Arista(int costo, float tiempo, NodoGrafo *destino) {
    this -> costo = costo;
    this -> horasVuelo = tiempo;
    this -> adyacente = destino;
}

void Arista::insertarCosto(int costo) {
    this -> costo = costo;
}

void Arista::insertarHorasVuelo(float horasVuelo) {
    this -> horasVuelo = horasVuelo;
}

void Arista::insertarVerticeApunta(NodoGrafo *vertice) {
    this -> adyacente = vertice;
}


NodoGrafo * Arista::obtenerVerticeApunta() {
    return adyacente;
}

int Arista::obtenerCosto() {
    return costo;
}

float Arista:: obtenerHorasVuelo() {
    return horasVuelo;
}