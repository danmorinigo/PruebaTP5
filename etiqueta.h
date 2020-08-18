#ifndef ETIQUETA_H_INCLUDED
#define ETIQUETA_H_INCLUDED
#include <list>
#include<iostream>
#include "vertice.h"

const int ENTERO_INFINITO = 99999;
const double DOUBLE_INFINITO = 99999.9;

class Etiqueta{
private:
    Vertice* vertice;
    list<Vertice*> anterior;
    int pesoAcumulado;
    double pesoDouble;
    int iteracion;
public:
    Etiqueta(Vertice* actual);
    ~Etiqueta();

    //PRE:  Vertice* debe estac creado
    //POST: Agrega Vertice* a la lista de Vertices* anterior.
    //      Si anteriormente habia sido agregado se descarta.
    void sumoAnterior(Vertice* anterior);

    //PRE:  --
    //POST: pesoAcumulado valdra el valor peso pasado como parametro.
    void setPesoAcumulado(int peso);

    //PRE:  --
    //POST: pesoDouble valdra el valor pesoDouble pasado como parametro.
    void setPesoDouble(double pesoDouble);

    //PRE:  --
    //POST: iteracion valdra el valor iteracion pasado como parametro.
    void setIteracion(int iteracion);

    //PRE:  --
    //POST: Devuelve el valor almacenado en Vertice
    Vertice* getVertice();

    //PRE:  --
    //POST: Devuelve lista de antecesores del Vertice*
    list<Vertice*> getAnterior();

    //PRE:  --
    //POST: Devuelve valor guardado en pesoAcumulado.
    int getPesoAcumulado();

    //PRE:  --
    //POST: Devuelve valor guardado en pesoDouble.
    double getPesoDouble();

    //PRE:  --
    //POST: Devuelve valor guardado en iteracion.
    int getIteracion();
};

#endif // ETIQUETA_H_INCLUDED
