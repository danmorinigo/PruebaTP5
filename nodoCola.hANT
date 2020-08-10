#ifndef NODOCOLA_H_INCLUDED
#define NODOCOLA_H_INCLUDED
#include<iostream>
#include "BSTNode.h"
#include "aeropuerto.h"
const bool MEMORIA = false;

class NodoCola{
private:
    BSTNode<Aeropuerto*>* dato;
    NodoCola* siguiente;
public:
    NodoCola (BSTNode<Aeropuerto*>* dato);
    BSTNode<Aeropuerto*>* obtenerDato();
    void asignarSiguiente(NodoCola* alSiguiente);
    NodoCola* obtenerSiguiente();

    ~NodoCola();
};


#endif // NODOCOLA_H_INCLUDED
