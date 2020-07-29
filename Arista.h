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
    Arista();
    void insertarCosto(int costo);
    void insertarHorasVuelo(float horasVuelo);
    void insertarVerticeApunta(NodoGrafo * vertice);


    NodoGrafo * obtenerVerticeApunta();
    int obtenerCosto();
    float obtenerHorasVuelo();

};


#endif //GRAFO_ARISTA_H
