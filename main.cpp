//
// Created by carolina on 3/6/20.
//

#include<iostream>
#include<fstream>
#include "include/BST.h"
#include "include/aeropuerto.h"

using namespace std;

int main()
{
    ifstream archivo("Aeropuertos.txt");

    BST<Aeropuerto*>* bst = new BST<Aeropuerto*>();
    Aeropuerto* aero;

    string auxS;
    unsigned auxU;
    double auxD;

    if(!archivo.fail()){
        while(archivo >> auxS){
            aero = new Aeropuerto;
            aero->asignarCodigo(auxS);
            archivo >> auxS;
            aero->asignarNombre(auxS);
            archivo >> auxS;
            aero->asignarCiudad(auxS);
            archivo >> auxS;
            aero->asignarPais(auxS);
            archivo >> auxD;
            aero->asignarSup(auxD);
            archivo >> auxU;
            aero->asignarTerminales(auxU);
            archivo >> auxU;
            aero->asignarDestNac(auxU);
            archivo >> auxU;
            aero->asignarDestInternac(5);
            bst->insert(aero, aero->obtenerCodigo());
        }
    }else{
        cout << "NO ARCHIVO" << endl;
    }

    archivo.close();
    cout << "-------------INORDER:-------------------------\n";
    bst->print_in_order();
    cout << "\n----------------------------------------------\n";
    //delete aero;
    delete bst;
}

