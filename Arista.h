#ifndef ARISTA_H_INCLUDED
#define ARISTA_H_INCLUDED
#include <iostream>
using namespace std;

class Vertice;

class Arista{
private:
    Arista* sig;
    Vertice* destino;
    int precio;
    double horasVuelo;
public:

    //PRE:  objeto destino debe estar creado
    //POST: Crea un objeto Arista, atributo sig apuntando a Null, destino apunta al vertice pasado
    //      como parametro, precio vale -1 y horasVuelo vale -1.0.
    Arista(Vertice* destino);

    //PRE:  --
    //POST: --
    ~Arista();

    //PRE:  sig puede ser tanto un objeto Arista ya creado o null.
    //POST: sig apunta al valor pasado por parametro.
    void asignarSiguiente(Arista* sig);

    //PRE:  --
    //POST: a precio se le asigna el valor pasado por parametro.
    void asignarPrecio(int precio);

    //PRE:  --
    //POST: a horasVuelo se le asigna el valor pasado por parametro.
    void asignarHoras(double horasVuelo);

    //PRE:  --
    //POST: Devuelve el valor guardado en sig.
    Arista* consultarSiguiente();

    //PRE:  --
    //POST: Devuelve Vertice* al cual si dirije la arista.
    Vertice* ConsultarDestino();

    //PRE:  --
    //POST: Devuelve valor almacenado en precio.
    int consultarPrecio();

    //PRE:  --
    //POST: Devuelve valor almacenado en horasVuelo.
    double consultarHoras();

};

#endif // ARISTA_H_INCLUDED
