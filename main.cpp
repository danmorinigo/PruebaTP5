//
//

#include<iostream>
#include "BST.h"
#include "menu.h"
#include "manejoDeArchivos.h"
#include "verificadorDatos.h"
#include "Grafo.h"
const string ARCHIVO_IATA = "Aeropuertos.txt";
const string ARCHIVO_VUELOS = "vuelos.txt";

using namespace std;

int main()
{

    VerificadorDatos chequeo;
    manejoDeArchivos archivo;
    Menu menu;
    BST<Aeropuerto*>* aeropuertos = new BST<Aeropuerto*>();
    Grafo* vuelos = new Grafo;

    if(archivo.existe(ARCHIVO_IATA)){
        archivo.cargarAeropuertos(aeropuertos, ARCHIVO_IATA);
    }
    menu.setAeropuertos(aeropuertos);
    if(archivo.existe(ARCHIVO_VUELOS)){
        archivo.cargarVuelos(vuelos, ARCHIVO_VUELOS);
    } else{
        vuelos = NULL;
    }
    menu.setVuelos(vuelos);
    while (menu.getOpcion() != '0'){
        menu.mostrarMenuPrincipal();
        menu.hacerEleccion();
        menu.pausa();
    }

    delete aeropuertos;
    delete vuelos;

    return 0;
}
