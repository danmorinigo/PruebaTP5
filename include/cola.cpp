#include "cola.h"
Cola::Cola(){
    primero = 0;
    ultimo = 0;
    tamanio = 0;
    if(MEMORIA) std::cout << "Constructor COLA (" << this << ")\n";
}
Cola::Cola(const Cola& copiado){
    primero = 0;
    ultimo = 0;
    tamanio = 0;
    int limite = copiado.tamanio;
    NodoCola* inserto = copiado.primero;
    for(int i = 0; i < limite; i++){
        insertar(inserto->obtenerDato());
        inserto = inserto->obtenerSiguiente();
    }
    if(MEMORIA) std::cout << "Constructor copia COLA (" << this << ")\n";
}
void Cola::insertar(BSTNode<Aeropuerto*>* aIngresar){
    NodoCola* aux = new NodoCola(aIngresar);
    if(primero == 0){
        primero = aux;
        ultimo = primero;
    }else{
        ultimo->asignarSiguiente(aux);
        ultimo = aux;
    }
    this->tamanio++;
}
BSTNode<Aeropuerto*>* Cola::consultar(){
    return primero->obtenerDato();
}
string Cola::eliminar(){
    string datoEliminado = primero->obtenerDato()->get_IATA();
    NodoCola* aux = primero;
    primero = primero->obtenerSiguiente();
    if(!primero){
        ultimo = 0;
    }
    delete aux;
    tamanio--;
    return datoEliminado;
}
bool Cola::vacia(){
    return (primero == 0);
}
int Cola::obtenerTamanio(){
    return this->tamanio;
}
NodoCola* Cola::anterior(int posicion){
    NodoCola* aux = 0;
    int posReal = posicion - 1;
    if(posReal == 0){//es el primero
        return 0;
    }else{//esta en la cola
        aux = primero;
        for(int i = 0; i < posReal - 1; i++){
            aux = aux->obtenerSiguiente();
        }
    }
    return aux;
}
Cola::~Cola(){
    string aux;
    while(!vacia()){
        aux = eliminar();
        if(MEMORIA) std::cout << "Eliminado: " << aux << std::endl;
    }
    if(MEMORIA) std::cout << "Destructor COLA (" << this << ")\n";
}
