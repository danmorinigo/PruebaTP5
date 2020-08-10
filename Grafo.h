#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

#include <list>
#include <stack>

#include "colaPrioridad.h"
#include "vertice.h"
#include "arista.h"
#include "etiqueta.h"

using namespace std;

struct TuplaCompleta{
    Vertice* vertice = 0;
    int pesoAcumulado = 0;
    double pesoDouble = 0.0;
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

    //------ESTO HAY QUE MODULIZAR BASTANTE Y VER TEMA NOMBRES VARIABLES------------
    void caminoMinimo(Vertice* salida, Vertice* destino, int precioUhorasVuelo);
    void mostrarVer3(list<Etiqueta> etiquetados, Vertice* recorriendoDesde, Vertice* destino, stack<TuplaCompleta> caminoRecorrido, bool primeraPasada, int criterio);
    void mostrarPila(stack<TuplaCompleta> aMostrar, int criterio);
    //------------------------------------------------------------------------------

    //--------------------NO SE SI ES TAN NECESARIO---------------------------
    Vertice* obtenerPrimero();
    //------------------------------------------------------------------------
    ~Grafo();

    //***********************************************************************************
    //***********************************************************************************
    //***********************************************************************************
};

#endif // GRAFO_H_INCLUDED
