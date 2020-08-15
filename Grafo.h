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
    void caminoMinimo(Vertice* salida, Vertice* destino, int precioUhorasVuelo);
    void mostrarVer3(list<Etiqueta*> etiquetados, Vertice* recorriendoDesde, Vertice* destino, stack<TuplaCompleta> caminoRecorrido, bool primeraPasada, int criterio);
    void mostrarPila(stack<TuplaCompleta> aMostrar, int criterio);
    void mostrarVertices();
    //bool marcadoComoVisitado(list<Vertice*> yaVisitados, Vertice* evaluado);
    bool fueVisitado(list<Vertice*> yaVisitados, Vertice* evaluado);
    void verificarPesoVerticeMarcado(Vertice* visitado, Vertice* destino, list<Etiqueta*> etiquetados, int modo, int iteracion, list<Vertice*> &vistos, ColaPrioridad &cola);
    void mostrarVerticesMarcados(list<Vertice*> vistos);
    bool existeCamino(list<Etiqueta*> etiquetados, Vertice* destino);
    void mostarEtiquetas(list<Etiqueta*> etiquetados);
    bool enTolerancia(double valor1, double valor2);
    void liberarEtiquetas(list<Etiqueta*> etiquetados);
    void etiquetarVertices(list<Etiqueta*> &etiquetados);
    Etiqueta* obtenerEtiqueta(Vertice* buscado, list<Etiqueta*> etiquetados);
    void evaluarVerticeDestino(Etiqueta* partida, Etiqueta* destino, int iteracion, int modo);
    //------------------------------------------------------------------------------

    //---------------------------------------------
    Vertice* obtenerPrimero(); // lo uso para el metodo mostrarVertices()
    //------------------------------------------------------------------------
    ~Grafo();

    //***********************************************************************************
    //***********************************************************************************
    //***********************************************************************************
};

#endif // GRAFO_H_INCLUDED
