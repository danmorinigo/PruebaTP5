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

struct TuplaCompleta{
    Vertice* vertice;
    int pesoAcumulado;
    double pesoDouble;
};

class Grafo{
private:
    Vertice* primero;
    Vertice* ultimo;
    list<Etiqueta*> etiquetados;
    int criterioBusqueda;
    int tamanio;
public:
    //***********************************************************************************
    //**********************************LO BASICO****************************************
    //***********************************************************************************
    Grafo();
    void agregarVertice(string nombre);
    bool existeVertice(string nombre);
    int cantVertices();
    Vertice* obtenerVertice(string nombre);
    void agregarArista(Vertice* inicio, Vertice* destino, int precio, double horasVuelo);
    int obtenerPeso1(Vertice* inicio, Vertice* destino);
    double obtenerPeso2(Vertice* inicio, Vertice* destino);
    unsigned obtenerTamanio();

    //------ESTO HAY QUE MODULIZAR BASTANTE Y VER TEMA NOMBRES VARIABLES------------
    void caminoMinimo(Vertice* salida, Vertice* destino);
    void mostrarCaminos(Vertice* recorriendoDesde, Vertice* destino, stack<Vertice*> caminoRecorrido, bool primeraPasada);
    void presentarPila(stack<Vertice*> aMostrar);
    void setCriterioBusqueda(int criterio);
    bool caminoPorPrecio();
    bool caminoPorHoras();
    list<Vertice*> antecesoresDe(Vertice* consultado);
    int costoAcumulado(Vertice* consultado);
    double horasAcumuladas(Vertice* consultado);
    void mostrarVertices();
    bool fueVisitado(list<Vertice*> yaVisitados, Vertice* evaluado);
    void verificarPesoVerticeMarcado(Vertice* visitado, Vertice* destino, int iteracion, list<Vertice*> &vistos, ColaPrioridad &cola);
    void mostrarVerticesMarcados(list<Vertice*> vistos);
    bool existeCamino(Vertice* destino);
    void mostarEtiquetas();
    bool enTolerancia(double valor1, double valor2);
    void liberarEtiquetas();
    void etiquetarVertices();
    Etiqueta* obtenerEtiqueta(Vertice* buscado);
    void evaluarVerticeDestino(Etiqueta* partida, Etiqueta* destino, int iteracion);
    Vertice* obtenerPrimero();
    //------------------------------------------------------------------------
    ~Grafo();

    //***********************************************************************************
    //***********************************************************************************
    //***********************************************************************************
};

#endif // GRAFO_H_INCLUDED
