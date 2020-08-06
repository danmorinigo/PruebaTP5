//
// Created by Emiliano Ruiz on 25/07/2020.
//

#include "Arista.h"

Arista::Arista(int costo, float tiempo, NodoGrafo *destino) {
    this -> costo = costo;
    this -> horasVuelo = tiempo;
    this -> adyacente = destino;
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