//
// Created by Emiliano Ruiz on 25/07/2020.
//

#ifndef GRAFO_ARISTA_H
#define GRAFO_ARISTA_H

#include "NodoGrafo.h"

using namespace std;

class NodoGrafo;

class Arista {

private:
    int costo;
    float horasVuelo;
    NodoGrafo * adyacente;

public:
    Arista(int costo, float tiempo, NodoGrafo * destino);

    NodoGrafo * obtenerVerticeApunta();
    int obtenerCosto();
    float obtenerHorasVuelo();

};


#endif //GRAFO_ARISTA_H
