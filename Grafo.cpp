//
// Created by Emiliano Ruiz on 25/07/2020.
//

#include "Grafo.h"

Grafo::Grafo() {
    primero = 0;
    ultimo = 0;
    tam = 0;
}


Grafo::~Grafo() {
    while (!(grafoVacio()))
        eliminarDato(1);
}


bool Grafo::grafoVacio() {
    return ( primero == 0);
}


void Grafo::insertarVertice(string nombre, unsigned int pos) {
    NodoGrafo * nuevo = new NodoGrafo(nombre);
    if (pos == 1){
        nuevo -> asignarSiguiente(primero);
        primero = nuevo;
    } else {
        NodoGrafo * anterior = obtenerNodo(pos - 1);
        nuevo -> asignarSiguiente(anterior -> obtenerSiguiente());
        anterior -> asignarSiguiente(nuevo);
    }
    tam++;
}

////////////////////////////////////////////////////////////////////////////

NodoGrafo * Grafo::obtenerPrimero(){
    return this-> primero;
}
void Grafo::mostrarVertices(){
    cout << endl<<"Listado de aeropuertos en el grafo: \n"<<endl;
            NodoGrafo* aux = this->obtenerPrimero();
            for(int i = 0; i < this->obtenerTamanio(); i++){
                cout << "- " << aux->obtenerNombre() << endl;
                aux = aux->obtenerSiguiente();
            }
            cout<<endl;
            cin.get();
}

void Grafo::agregarVertice(string nombre){
    NodoGrafo* ingresante = new NodoGrafo(nombre);
    if (!primero){
        primero = ingresante;
        ultimo = ingresante;
        tam++;
        this->vertices.insert(nombre);
        return;
    }
    NodoGrafo* aux = primero;
    while(aux->obtenerSiguiente() != 0){
        aux = aux->obtenerSiguiente();
    }
    aux->asignarSiguiente(ingresante);
    ultimo = ingresante;
    tam++;
    this->vertices.insert(nombre);
}

bool Grafo::existeVertice(string nombre){
    return this->vertices.search(nombre);
}

/////////////////////////////////////////////////////////////////////////

void Grafo::eliminarDato(unsigned pos) {
    NodoGrafo * borrar = primero;
    if (pos == 1){
        primero = borrar -> obtenerSiguiente();
    } else {
        NodoGrafo * anterior = obtenerNodo( pos - 1);
        borrar = anterior -> obtenerSiguiente();
        anterior -> asignarSiguiente(borrar -> obtenerSiguiente());
    }
    delete borrar;
    tam--;
}


unsigned Grafo::obtenerTamanio() {
    return tam;
}

NodoGrafo * Grafo::obtenerNodo(unsigned int pos) {
    NodoGrafo * aux = primero;
    unsigned i = 1;
    while (i < pos){
        aux = aux -> obtenerSiguiente();
        i++;
    }
    return aux;
}

NodoGrafo * Grafo::obtenerVertice(string nombre) {
    NodoGrafo * aux = primero;
    while (aux != nullptr){
        if (aux -> obtenerNombre() == nombre){
            return aux;
        }
        aux = aux -> obtenerSiguiente();
    }
    return nullptr;
}

void Grafo::insertarArista(NodoGrafo *origen, NodoGrafo *destino, int precio, float horas) {

    Arista nueva(precio, horas, destino);
    origen -> insertarArista(nueva);

}

Arista Grafo::obtenerArista(NodoGrafo *origen, NodoGrafo *destino) {
    int i = 0;
    vector<Arista> aux = origen -> obtenerCaminos();

    while (  i < (aux.size()) ) {
        if (destino == aux[i].obtenerVerticeApunta()) {
            return aux[i];                          //ESTO HAY QUE CAMBIARLO ES MALA PRACTICA.
        }
        i++;
    }
}


void Grafo::mejorCamino(NodoGrafo *origen, NodoGrafo *destino) {

    vector<Arista> aux;
    vector<VerticeCosto> distancia;
    priority_queue<VerticeCosto> colaPrioridad;
    NodoGrafo * verticeActual;

    setearVerticesComoNoVistos();
    setearDistanciaInfinito(&distancia);


    cambiarDistancia(&distancia, origen, 0);
    colaPrioridad.push(VerticeCosto(origen,0));


    while (!colaPrioridad.empty() && verticeActual != destino){
        verticeActual = colaPrioridad.top().vertice;
        colaPrioridad.pop();
        verticeActual -> definirVisitado(true);
        aux = verticeActual -> obtenerCaminos(); // obtengo los adyacentes

        for (int i = 0; i < aux.size(); i++) {
            if (!(aux[i].obtenerVerticeApunta() -> obtenerVisitado())){
                actualizarCosto(verticeActual, &colaPrioridad, aux[i].obtenerVerticeApunta(), aux[i].obtenerCosto(), &distancia);
            }
        }
    }

    if (obtenerDistancia(&distancia, verticeActual) != 0){
        mostrarCamino(verticeActual, origen);
    } else {
        cout << "NO EXISTE UN CAMINO ENTRE ORIGEN-DESTINO" << endl;
    }

}

void Grafo::actualizarCosto(NodoGrafo * verticeActual, priority_queue<VerticeCosto> * colaPrioridad, NodoGrafo * adyacente, int costo, vector<VerticeCosto> * distancia) {
    if (obtenerDistancia(distancia, adyacente) > (obtenerDistancia(distancia, verticeActual) + costo)) {
        cambiarDistancia(distancia, adyacente, obtenerDistancia(distancia, verticeActual) + costo);
        adyacente -> definirAnterior(verticeActual);
        colaPrioridad -> push(VerticeCosto(adyacente, obtenerDistancia(distancia, verticeActual) + costo));
    }
 }

void Grafo::setearVerticesComoNoVistos() {
    for (int i = 1; i <= obtenerTamanio(); i++) {
        obtenerNodo(i) -> definirVisitado(false);
    }
}

void Grafo::setearDistanciaInfinito(vector<VerticeCosto> *distancia) {
    for (int i = 1; i <= obtenerTamanio(); ++i) {
        distancia -> push_back(VerticeCosto(obtenerNodo(i), 99999));
    }
}

void Grafo::cambiarDistancia(vector<VerticeCosto> *distancia, NodoGrafo *vertice, int valor) {
    int iterador = 0;
    while (vertice -> obtenerNombre() != distancia -> at(iterador).vertice -> obtenerNombre()){
        iterador++;
    }
    distancia -> at(iterador) = VerticeCosto(vertice, valor);
}

int Grafo::obtenerDistancia(vector<VerticeCosto> *distancia, NodoGrafo * vertice){
    int iterador = 0;
    while (vertice -> obtenerNombre() != distancia -> at(iterador).vertice -> obtenerNombre()){
        iterador++;
    }
    return distancia -> at(iterador).costo;
}

void Grafo::mostrarCamino(NodoGrafo *verticeActual, NodoGrafo *origen) {
    int totalCosto = 0;
    while (verticeActual != origen){
        cout << verticeActual -> obtenerNombre() << " <- ";
        cout << obtenerArista(verticeActual -> obtenerAnterior(), verticeActual).obtenerCosto() << " ";
        totalCosto = totalCosto + obtenerArista(verticeActual -> obtenerAnterior(), verticeActual).obtenerCosto();
        verticeActual = verticeActual -> obtenerAnterior();
    }
    cout << origen -> obtenerNombre() << endl;
    cout << "TOTAL: " << totalCosto << endl;
}

