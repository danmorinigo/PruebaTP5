#include "colaPrioridad.h"
ColaPrioridad::ColaPrioridad(int criterioOrden){
    primero = 0;
    primeroSegunPrioridad = 0;
    ultimo = 0;
    this->criterioOrden = criterioOrden;
    if(MEMORIA) std::cout << "Constructor ColaPrioridad (" << this << ")\n";
}
void ColaPrioridad::push(Vertice* evaluado, int precio, double horas, int iteracion){
    if(!primero){//cola vacia
        primero = new NodoColaPrioridad(evaluado, iteracion, precio, horas);
        primeroSegunPrioridad = primero;
        ultimo = primero;
    }else{//habia elementos en la cola
        int prioridadActual = primeroSegunPrioridad->getPrioridad();
        NodoColaPrioridad* aux = new NodoColaPrioridad(evaluado, iteracion, precio, horas);
        if(iteracion > prioridadActual){//nueva iteracion - inserta al final
            insertarAlFinal(aux);
            actualizarPrioridad(aux);
        }else if(iteracion == prioridadActual){//hay que ordenar...
            //mayor que el ultimo, inserta al final de cola
            if(((criterioOrden == 1) && (precio >= ultimo->getEntero())) || ((criterioOrden == 2) && (horas >= ultimo->getDouble()))){
                insertarAlFinal(aux);
            }else{
                //menor que el primero en esta prioridad
                if(((criterioOrden == 1) && (precio < primeroSegunPrioridad->getEntero())) || ((criterioOrden == 2) && (horas < primeroSegunPrioridad->getDouble()))){
                    //primero en cola y primero segun prioridad apuntando al mismo lugar
                    if(primero == primeroSegunPrioridad){
                        aux->setSiguiente(primero);
                        this->primero = aux;
                        actualizarPrioridad(aux);
                    }else{
                        //primero segun prioridad no apunta a PRIMERO
                        insertarNuevoEnPrioridad(aux);
                        actualizarPrioridad(aux);
                    }
                }else{//esta en medio de esta prioridad, pero no al final ni al principio
                    insertarOrdenado(aux);
                }
            }
        }else{
            cout << "ERROR - Iteracion no permitida" << endl;
            cin.get();
        }

    }
}
bool ColaPrioridad::vacia(){
    return (primero == 0);
}
int ColaPrioridad::topPrioridad(){
    return this->primero->getPrioridad();
}
int ColaPrioridad::topPrecio(){
    return this->primero->getEntero();
}
double ColaPrioridad::topHoras(){
    return this->primero->getDouble();
}
Vertice* ColaPrioridad::topVertice(){
    return this->primero->obtenerVertice();
}
void ColaPrioridad::pop(){
    NodoColaPrioridad* auxNodo = primero;
    this->primero = auxNodo->getSiguiente();
    if (primeroSegunPrioridad == auxNodo){
        primeroSegunPrioridad = primero;
    }
    if(!primero){
        ultimo = 0;
    }
    delete auxNodo;
}
void ColaPrioridad::insertarAlFinal(NodoColaPrioridad* aInsertar){
    this->ultimo->setSiguiente(aInsertar);
    this->ultimo = aInsertar;
}
void ColaPrioridad::actualizarPrioridad(NodoColaPrioridad* aInsertar){
    this->primeroSegunPrioridad = aInsertar;
}
void ColaPrioridad::insertarNuevoEnPrioridad(NodoColaPrioridad* aInsertar){
    NodoColaPrioridad* auxPrimero = primero;
    while(auxPrimero->getSiguiente() != this->primeroSegunPrioridad){
        auxPrimero = auxPrimero->getSiguiente();
    }
    aInsertar->setSiguiente(primeroSegunPrioridad);
    auxPrimero->setSiguiente(aInsertar);
}
void ColaPrioridad::insertarOrdenado(NodoColaPrioridad* aInsertar){
    NodoColaPrioridad* auxPrioridadActual = primeroSegunPrioridad;
    bool hecho = false;
    while(!hecho && auxPrioridadActual->getSiguiente()){
        if(((criterioOrden == 1) && (aInsertar->getEntero() <= auxPrioridadActual->getSiguiente()->getEntero())) || ((criterioOrden == 2) && (aInsertar->getDouble() <= auxPrioridadActual->getSiguiente()->getDouble()))){
            aInsertar->setSiguiente(auxPrioridadActual->getSiguiente());
            auxPrioridadActual->setSiguiente(aInsertar);
            hecho= true;
        }
        auxPrioridadActual = auxPrioridadActual->getSiguiente();
    }
    if(!hecho){
        cout << "Ha ocurrido un error ordenando dentro de la prioridad " << this->primeroSegunPrioridad->getPrioridad() << endl;
        cin.get();
    }
}
Vertice* ColaPrioridad::topAndPop(){
    NodoColaPrioridad* auxNodo = primero;
    Vertice* aux = primero->obtenerVertice();
    this->primero = auxNodo->getSiguiente();
    if (primeroSegunPrioridad == auxNodo){
        primeroSegunPrioridad = primero;
    }
    if(!primero){
        ultimo = 0;
    }
    delete auxNodo;
    return aux;
}
ColaPrioridad::~ColaPrioridad(){
    while(!vacia()){
        this->pop();
    }
    if(MEMORIA) std::cout << "Destructor ColaPrioridad (" << this << ")\n";
}
