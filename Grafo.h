#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

#include <list>
#include <stack>

#include "colaPrioridad.h"
#include "vertice.h"
#include "Arista.h"
#include "etiqueta.h"

using namespace std;

const double TOLERANCIA = 0.000001;

class Grafo{
private:
    Vertice* primero;
    Vertice* ultimo;
    list<Etiqueta*> etiquetados;
    int criterioBusqueda;
    int tamanio;
public:
    //PRE:  --
    //POST: Constructor del objeto.
    Grafo();

    //PRE:  --
    //POST: Agrega nuevo puntero Vertice.
    //      Si el grafo tenia vertices se lo inserta directamente al final.
    void agregarVertice(string nombre);

    //PRE:  --
    //POST: Devuelve false si no encuentra el vertice, de lo contrario devuelve true.
    bool existeVertice(string nombre);

    //PRE:  --
    //POST: Devuelve Vertice si esta en el grafo, sino devuelve null.
    Vertice* obtenerVertice(string nombre);

    //PRE:  Vertices inicio y destino deben existir.
    //POST: Suma una nueva arista al Vertice inicio con los datos de precio y horasVuelo pasados por parametro.
    void agregarArista(Vertice* inicio, Vertice* destino, int precio, double horasVuelo);

    //PRE:  Vertices inicio y destino deben existir.
    //POST: Devuelve el valor precio guardado en la arista.
    //      Si no existe arista devuelve -1.
    int obtenerPrecio(Vertice* inicio, Vertice* destino);

    //PRE:  Vertices inicio y destino deben existir.
    //POST: Devuelve el valor horasVuelo guardado en la arista.
    //      Si no existe arista devuelve -1.
    double obtenerTiempoDeVuelo(Vertice* inicio, Vertice* destino);

    //PRE:  --
    //POST: Devuelve cantidad de vertices cargados en el grafo.
    unsigned obtenerTamanio();

    //PRE:  Vertice salida y destino deben existir.
    //POST: Recorre vertices en el grafo buscando una conexion entre salida y destino.
    //      Si encuentra el camino sera el de menor costo.
    //      Si no hay camino muestra cartel inicando que no existe conexion.
    void caminoMinimo(Vertice* salida, Vertice* destino);

    //PRE:  criterio debe ser 1 o 2.
    //POST: Setea criterio por el cual se ordenaran los caminos buscados.
    //      Con criterio 1 se ordena teniendo en cuenta el precio del vuelo.
    //      Con criterio 2 se ordena teniendo en cuenta las horas que toma el vuelo.
    void setCriterioBusqueda(int criterio);

    //PRE:  --
    //POST: Devuelve true si criterio == 1, sino devuelve false.
    bool caminoPorPrecio();

    //PRE:  --
    //POST: Devuelve true si criterio == 2, sino devuelve false.
    bool caminoPorHoras();

    //PRE:  --
    //POST: Lista los vertices cargados en el grafo.
    void mostrarVertices();

    //PRE:  --
    //POST: Devuelve valor contenido en primero.
    Vertice* obtenerPrimero();

    //PRE:  --
    //POST: Libera recursos utilizados. (Vertices y aristas)
    ~Grafo();
private:
    //PRE:  Debe haber conexion entre recorriendoDesde hasta destino.
    //POST: Prepara una pila de Vertices* para mostrar en pantalla el camino recorrido.
    void mostrarCaminos(Vertice* recorriendoDesde, Vertice* destino, stack<Vertice*> caminoRecorrido, bool primeraPasada);

    //PRE:  La pila no debe ser vacia.
    //POST: Presenta por pantalla el camino recorrido.
    void presentarPila(stack<Vertice*> aMostrar);

    //PRE:  consultado debe existir.
    //POST: Devuelve lista de antecesores del vertice consultado.
    list<Vertice*> antecesoresDe(Vertice* consultado);

    //PRE:  consultado debe existir.
    //POST: Devuelve el precio acumulado del vertice consultado.
    int costoAcumulado(Vertice* consultado);

    //PRE:  consultado debe existir.
    //POST: Devuelve las horas acumuladas del vertice consultado.
    double horasAcumuladas(Vertice* consultado);

    //PRE:  buscado debe existir.
    //POST: Devuelve la etiqueta asociada al vertice buscado.
    Etiqueta* obtenerEtiqueta(Vertice* buscado);

    //PRE:  evaludado y yaVisitados deben existir.
    //POST: Si evaluado se encuentra dentro de la lista yaVIsitados devuelve true, sino devuelve false.
    bool fueVisitado(list<Vertice*> yaVisitados, Vertice* evaluado);

    //PRE:  Vertices deben existir.
    //POST: Si el peso del vertice destino es mayor al peso del vertice visitado + el valor de la arista que los une,
    //      se reemplazan datos del vertice destino, tanto de sus pesos como su iteracion.
    //      Se lo agrega a la cola de prioridad para que sean nuevamente evaluados sus vertices adyacentes.
    //      Se lo retira de la lista vistos.
    void verificarPesoVerticeMarcado(Vertice* visitado, Vertice* destino, int iteracion, list<Vertice*> &vistos, ColaPrioridad &cola);

    //PRE:  destino debe existir.
    //POST: Devuelve true si el vertice destino tiene antecesores, caso contrario devuelve false.
    bool existeCamino(Vertice* destino);

    //PRE:  visitado debe existir.
    //POST: Evalua vertice destino de la arista auxArista.
    //      Si no esta marcado como visto:
    //          Agrega el vertice destino de la arista a la cola de prioridad.
    //          llama al metodo evaluarVerticeDestino.
    //      Si ya fue visitado:
    //          llama al metodo verificarPesoVerticeMarcado.
    void trabajoAdyacente(Arista* auxAristas,  list<Vertice*> * vistos, Vertice * visitado, ColaPrioridad * cola, Etiqueta * auxActual, int iteracion);

    //PRE:  Etiquetas deben existir.
    //POST: En caso de que el peso acumulado en el vertice destino sea mayor al peso acumulado por el vertice* partida
    //      sumado a la arista que los une, cambia valores de peso en destino, asi como la iteracion.
    void evaluarVerticeDestino(Etiqueta* partida, Etiqueta* destino, int iteracion);

    //PRE:  --
    //POST: Asocia a cada Vertice cargado en el grafo un objeto Etiqueta.
    void etiquetarVertices();

    //PRE:  --
    //POST: Libera memoria pedida al etiquetar los vertices.
    void liberarEtiquetas();

    //PRE:  --
    //POST: Si el valor absoluto de la resta entre valor1 y valor2 es menor a TOLERANCIA definido, que esta definida
    //      al antes de declarar esta clase, devuelve true, caso contrario devuelve false.
    bool enTolerancia(double valor1, double valor2);

    //PRE:  --
    //POST: Muestra los vertices marcados como visitados en el orden con el que fueron recorridos.
    void mostrarVerticesMarcados(list<Vertice*> vistos);

    //PRE:  --
    //POST: Muestra valores dentro de las etiquetas de cade vertice.
    void mostarEtiquetas();

};

#endif // GRAFO_H_INCLUDED
