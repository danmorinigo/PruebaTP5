//
// Created by carolina on 3/6/20.
//

#include<iostream>
#include "BST.h"
#include "aeropuerto.h"
#include "manejoDeArchivos.h"
#include "verificadorDatos.h"


const string ARCHIVO_IATA = "Aeropuertos.txt";
using namespace std;

int main()
{
    VerificadorDatos chequeo;
    manejoDeArchivos archivo;
    BST<Aeropuerto*>* aeropuertos = new BST<Aeropuerto*>();

    if(archivo.existe(ARCHIVO_IATA)){
        archivo.cargarAeropuertos(aeropuertos, ARCHIVO_IATA);
    }

    /*cout << "-------------INORDER:-------------------------\n";
    aeropuertos->print_in_order();
    cout << "\n----------------------------------------------\n";
    cout << "<Enter>"; cin.get();*/
    cout << "-------------EN ANCHO:-------------------------\n";
    aeropuertos->imprime_en_ancho();
    cout << "----------------------------------------------\n";
    cout << "<Enter>"; cin.get();
    cout << "-------------ACOSTADO:-------------------------\n";
    aeropuertos->imprime_acostado();
    cout << "----------------------------------------------\n";
    //delete aero;
    cout<< "Altura del arbol: "<< aeropuertos->obtenerAltura()<<endl;
    delete aeropuertos;

    return 0;
}

