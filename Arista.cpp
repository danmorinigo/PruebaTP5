#include "Arista.h"

Arista::Arista(Vertice* destino){
    sig = 0;
    this->destino = destino;
    precio = -1;
    horasVuelo = -1.0;
    cout << "Constructor Arista" << endl;
}
Arista::~Arista(){
    cout << "Destructor Arista" << endl;
}
void Arista::asignarSiguiente(Arista* sig){
    this->sig = sig;
}
void Arista::asignarPrecio(int precio){
    this->precio = precio;
}
void Arista::asignarHoras(double horasVuelo){
    this->horasVuelo = horasVuelo;
}

Arista* Arista::consultarSiguiente(){
    return sig;
}
Vertice* Arista::ConsultarDestino(){
    return destino;
}
int Arista::cunsultarPrecio(){
    return precio;
}
double Arista::consultarHoras(){
    return horasVuelo;
}
