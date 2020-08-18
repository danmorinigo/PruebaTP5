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
    Arista(Vertice* destino);
    ~Arista();
    void asignarSiguiente(Arista* sig);
    void asignarPrecio(int precio);
    void asignarHoras(double horasVuelo);

    Arista* consultarSiguiente();
    Vertice* ConsultarDestino();
    int consultarPrecio();
    double consultarHoras();

};

#endif // ARISTA_H_INCLUDED
