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
    return 0;
}
