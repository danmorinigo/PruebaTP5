#include "Arista2.h"

Arista2::Arista2(Vertice* destino){
    sig = 0;
    this->destino = destino;
    precio = -1;
    horasVuelo = -1.0;
    cout << "Constructor Arista" << endl;
}
Arista2::~Arista2(){
    cout << "Destructor Arista" << endl;
}
void Arista2::asignarSiguiente(Arista2* sig){
    this->sig = sig;
}
void Arista2::asignarPrecio(int precio){
    this->precio = precio;
}
void Arista2::asignarHoras(double horasVuelo){
    this->horasVuelo = horasVuelo;
}

Arista2* Arista2::consultarSiguiente(){
    return sig;
}
Vertice* Arista2::ConsultarDestino(){
    return destino;
}
int Arista2::cunsultarPrecio(){
    return precio;
}
double Arista2::consultarHoras(){
    return horasVuelo;
}
