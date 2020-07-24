//
// Created by carolina on 3/6/20.
//

#include<iostream>
#include "include/BST.h"
#include "include/aeropuerto.h"
#include "include/manejoDeArchivos.h"

const string ARCHIVO_IATA = "Aeropuertos.txt";
using namespace std;

int main()
{
    manejoDeArchivos archivo;
    BST<Aeropuerto*>* aeropuertos = new BST<Aeropuerto*>();

    archivo.cargarAeropuertos(aeropuertos, ARCHIVO_IATA);

    cout << "-------------INORDER:-------------------------\n";
    aeropuertos->print_in_order();
    cout << "\n----------------------------------------------\n";
    cout << "<Enter>"; cin.get();
    cout << "-------------EN ANCHO:-------------------------\n";
    aeropuertos->imprime_en_ancho();
    cout << "----------------------------------------------\n";
    cout << "<Enter>"; cin.get();
    cout << "-------------ACOSTADO:-------------------------\n";
    aeropuertos->imprime_acostado();
    cout << "----------------------------------------------\n";
    //delete aero;
    delete aeropuertos;
}

