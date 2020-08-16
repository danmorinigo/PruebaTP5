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

    //ESTOS SE PODRIAN ELIMINAR SI TODA ANDA BIEN
    void mostrarVer3(list<Etiqueta*> etiquetados, Vertice* recorriendoDesde, Vertice* destino, stack<TuplaCompleta> caminoRecorrido, bool primeraPasada);
    void mostrarPila(stack<TuplaCompleta> aMostrar);
    //------------------------------------------------------

    //ESTOS SON LOS METODOS QUE LOS REEMPLAZAN
    void mostrarCaminos(Vertice* recorriendoDesde, Vertice* destino, stack<Vertice*> caminoRecorrido, bool primeraPasada);
    //void mostrarCaminos(list<Etiqueta*> etiquetados, Vertice* recorriendoDesde, Vertice* destino, stack<Vertice*> caminoRecorrido, bool primeraPasada);
    void presentarPila(stack<Vertice*> aMostrar);
    //void presentarPila(stack<Vertice*> aMostrar, list<Etiqueta*> etiquetados);
    //--------------------

    //METODOS QUE HICE ESTA MAÑANA
    void setCriterioBusqueda(int criterio);
    bool caminoPorPrecio();
    bool caminoPorHoras();
    list<Vertice*> antecesoresDe(Vertice* consultado);
    //list<Vertice*> antecesoresDe(Vertice* consultado, list<Etiqueta*> etiquetados);
    int costoAcumulado(Vertice* consultado);
    double horasAcumuladas(Vertice* consultado);
    //int costoAcumulado(Vertice* consultado, list<Etiqueta*> etiquetados);
    //double horasAcumuladas(Vertice* consultado, list<Etiqueta*> etiquetados);
    //-----------------------------
    //bool marcadoComoVisitado(list<Vertice*> yaVisitados, Vertice* evaluado);


    void mostrarVertices();
    bool fueVisitado(list<Vertice*> yaVisitados, Vertice* evaluado);
    void verificarPesoVerticeMarcado(Vertice* visitado, Vertice* destino, int iteracion, list<Vertice*> &vistos, ColaPrioridad &cola);
    //void verificarPesoVerticeMarcado(Vertice* visitado, Vertice* destino, list<Etiqueta*> etiquetados, int iteracion, list<Vertice*> &vistos, ColaPrioridad &cola);
    void mostrarVerticesMarcados(list<Vertice*> vistos);
    bool existeCamino(Vertice* destino);
    //bool existeCamino(list<Etiqueta*> etiquetados, Vertice* destino);
    void mostarEtiquetas();
    //void mostarEtiquetas(list<Etiqueta*> etiquetados);
    bool enTolerancia(double valor1, double valor2);
    void liberarEtiquetas();
    //void liberarEtiquetas(list<Etiqueta*> etiquetados);
    void etiquetarVertices();
    //void etiquetarVertices(list<Etiqueta*> &etiquetados);
    Etiqueta* obtenerEtiqueta(Vertice* buscado);
    //Etiqueta* obtenerEtiqueta(Vertice* buscado, list<Etiqueta*> etiquetados);
    void evaluarVerticeDestino(Etiqueta* partida, Etiqueta* destino, int iteracion);

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
