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
    }else{//hay elementos en la cola
        NodoColaPrioridad* aux = new NodoColaPrioridad(evaluado, iteracion, precio, horas);
        insertarElemento(aux);
    }
}

void ColaPrioridad::insertarElemento(NodoColaPrioridad* aInsertar){
    int prioridadActual = primeroSegunPrioridad->getPrioridad();
    int iteracion = aInsertar->getPrioridad();
    int precio = aInsertar->getEntero();
    double horas = aInsertar->getDouble();
    if(iteracion > prioridadActual){//nueva iteracion - inserta al final
        insertarAlFinal(aInsertar);
        actualizarPrioridad(aInsertar);
    }else if(iteracion == prioridadActual){//hay que ordenar...
        //mayor que el ultimo, inserta al final de cola
        if((ordenPorPrecio() && (precio >= ultimo->getEntero())) || (ordenPorHoras() && (horas >= ultimo->getDouble()))){
            insertarAlFinal(aInsertar);
        }else{
            //menor que el primero en esta prioridad
            if((ordenPorPrecio() && (precio < primeroSegunPrioridad->getEntero())) || (ordenPorHoras() && (horas < primeroSegunPrioridad->getDouble()))){
                //primero en cola y primero segun prioridad apuntando al mismo lugar
                if(primero == primeroSegunPrioridad){
                    aInsertar->setSiguiente(primero);
                    this->primero = aInsertar;
                    actualizarPrioridad(aInsertar);
                }else{
                    //primero segun prioridad no apunta a PRIMERO
                    insertarNuevoEnPrioridad(aInsertar);
                    actualizarPrioridad(aInsertar);
                }
            }else{//esta en medio de esta prioridad, pero no al final ni al principio
                insertarOrdenado(aInsertar);
            }
        }
    }else{
        cout << "ERROR - Iteracion no permitida" << endl;
        cin.get();
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
        if((ordenPorPrecio() && (aInsertar->getEntero() <= auxPrioridadActual->getSiguiente()->getEntero())) || (ordenPorHoras() && (aInsertar->getDouble() <= auxPrioridadActual->getSiguiente()->getDouble()))){
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
bool ColaPrioridad::ordenPorPrecio(){
    return (this->criterioOrden == 1);
}

bool ColaPrioridad::ordenPorHoras(){
    return (this->criterioOrden == 2);
}

Vertice* ColaPrioridad::topAndPop(){
    Vertice* aux = primero->obtenerVertice();
    this->pop();
    return aux;
}

ColaPrioridad::~ColaPrioridad(){
    while(!vacia()){
        this->pop();
    }
    if(MEMORIA) std::cout << "Destructor ColaPrioridad (" << this << ")\n";
}
