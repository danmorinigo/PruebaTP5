#ifndef ARISTA_H_INCLUDED
#define ARISTA_H_INCLUDED
#include <iostream>
using namespace std;

class Vertice;

class Arista2{
private:
    Arista2* sig;
    Vertice* destino;
    int precio;
    double horasVuelo;
public:
    Arista2(Vertice* destino);
    ~Arista2();
    void asignarSiguiente(Arista2* sig);
    void asignarPrecio(int precio);
    void asignarHoras(double horasVuelo);

    Arista2* consultarSiguiente();
    Vertice* ConsultarDestino();
    int cunsultarPrecio();
    double consultarHoras();

};

#endif // ARISTA_H_INCLUDED
