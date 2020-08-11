#include "vertice.h"

Vertice::Vertice(string nombre){
    cout << "Constructor Vertice " << nombre << endl;
    siguiente = 0;
    arista = 0;
    this->nombre = nombre;
}
Vertice::~Vertice(){
    cout << "Destructor Vertice " << nombre << endl;
}
void Vertice::asignarProxVertice(Vertice* siguiente){
    this->siguiente = siguiente;
}
void Vertice::aliminarArista(Arista2* aristaAeliminar){
    if(this->arista == aristaAeliminar){
        this->arista = aristaAeliminar->consultarSiguiente();
        delete aristaAeliminar;
    }else{
        Arista2* previa = this->arista;
        Arista2* eliminamos = previa->consultarSiguiente();
        while(eliminamos){
            if(eliminamos == aristaAeliminar){
                previa->asignarSiguiente(eliminamos->consultarSiguiente());
                delete eliminamos;
                return;
            }
            previa = eliminamos;
            eliminamos = eliminamos->consultarSiguiente();
        }
    }
}

void Vertice::agregarArista(Arista2* nuevaArista){
    Arista2* aux = this->arista;
    if(aux == 0){
        this->arista = nuevaArista;
        return;
    }
    while(aux->consultarSiguiente() != 0){
        aux = aux->consultarSiguiente();
    }
    aux->asignarSiguiente(nuevaArista);
}

Vertice* Vertice::obtenerProxVertice(){
    return siguiente;
}
Arista2* Vertice::obtenerAristas(){
    return arista;
}
string Vertice::obtenerNombreVertice(){
    return nombre;
}
