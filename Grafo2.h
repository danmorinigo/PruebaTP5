#ifndef GRAFO2_H_INCLUDED
#define GRAFO2_H_INCLUDED

#include <list>
#include <stack>

#include "colaPrioridad.h"
#include "vertice.h"
#include "Arista2.h"
#include "etiqueta.h"

using namespace std;

struct TuplaCompleta{
    Vertice* vertice = 0;
    int pesoAcumulado = 0;
    double pesoDouble = 0.0;
};

class Grafo2{
private:
    Vertice* primero;
    Vertice* ultimo;
    int tamanio;
public:
    //***********************************************************************************
    //**********************************LO BASICO****************************************
    //***********************************************************************************
    Grafo2();
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
    void mostrarVer3(list<Etiqueta> etiquetados, Vertice* recorriendoDesde, Vertice* destino, stack<TuplaCompleta> caminoRecorrido, bool primeraPasada, int criterio);
    void mostrarPila(stack<TuplaCompleta> aMostrar, int criterio);
    void mostrarVertices();
    //------------------------------------------------------------------------------

    //---------------------------------------------
    Vertice* obtenerPrimero(); // lo uso para el metodo mostrarVertices()
    //------------------------------------------------------------------------
    ~Grafo2();

    //***********************************************************************************
    //***********************************************************************************
    //***********************************************************************************
};

#endif // GRAFO2_H_INCLUDED
