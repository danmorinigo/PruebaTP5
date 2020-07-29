//
// Created by carolina on 3/6/20.
//

#include<iostream>
#include "BST.h"
#include "menu.h"
#include "manejoDeArchivos.h"
#include "verificadorDatos.h"
//#include "aeropuerto.h"

const string ARCHIVO_IATA = "Aeropuertos.txt";
using namespace std;

int main()
{

    VerificadorDatos chequeo;
    manejoDeArchivos archivo;
    Menu menu;
    BST<Aeropuerto*>* aeropuertos = new BST<Aeropuerto*>();

    if(archivo.existe(ARCHIVO_IATA)){
        archivo.cargarAeropuertos(aeropuertos, ARCHIVO_IATA);
    }
    menu.setAeropuertos(aeropuertos);

    while (menu.getOpcion() != '0'){
        menu.mostrarMenuPrincipal();
        menu.hacerEleccion();
        menu.pausa();
    }

    delete aeropuertos;
    

    //===================================PARA PROBAR EL GRAFO====================================
    /*

    Grafo grafo;


    grafo.insertarVertice("EZE", 1);
    grafo.insertarVertice("MIA", 1);
    grafo.insertarVertice("FCO", 1);
    grafo.insertarVertice("TXL", 1);


    //Recibe la direccion de memoria del origen y destino (vertices) y los datos del camino
    grafo.insertarArista(grafo.obtenerVertice("EZE"), grafo.obtenerVertice("MIA"), 122483, 9.2);
    grafo.insertarArista(grafo.obtenerVertice("EZE"), grafo.obtenerVertice("FCO"), 222205, 13);

    //Cantidad de vertices
    cout << grafo.obtenerTamanio() << endl;

    //Aca hice una prueba de obtener el costo entre 2 vertices pasandole solo los nombres de origen y destino (Deberia hacerse con Djikstra)
    //El metodo obtenerArista se encarga de recorrer el vector de aristas de el vertice ORIGEN
    //y cuando la direccion del destino que esta cargada en la arista coincide con el pasado como atributo devuelve esa arista
    //habilitando a consultar los datos (precio y horasVuelo).

    cout << grafo.obtenerArista(grafo.obtenerVertice("EZE"), grafo.obtenerVertice("FCO")).obtenerCosto();

    */

    return 0;
}
