#include "nodoCola.h"
NodoCola::NodoCola (BSTNode<Aeropuerto*>* dato){
    if(MEMORIA) std::cout << "Constructor NODOCOLA (" << this << ")\n";
    this->dato = dato;
    siguiente = 0;
}
BSTNode<Aeropuerto*>* NodoCola::obtenerDato(){
    return this->dato;
}
void NodoCola::asignarSiguiente(NodoCola* alSiguiente){
    this->siguiente = alSiguiente;
}
NodoCola* NodoCola::obtenerSiguiente(){
    return this->siguiente;
}

NodoCola::~NodoCola(){
    if(MEMORIA) std::cout << "Destructor NODOCOLA (" << this << ")\n";
}
