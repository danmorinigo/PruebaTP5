//
//

#include<iostream>
#include "BST.h"
#include "menu.h"
#include "manejoDeArchivos.h"
#include "verificadorDatos.h"
#include "grafo.h"

//******para probar*****
#include <fstream>
//**********************

const string ARCHIVO_IATA = "Aeropuertos.txt";
const string ARCHIVO_VUELOS = "vuelos.txt";

using namespace std;

int main()
{
    //****************************************************************************
    //*********************PARA PROBAR GRAFO**************************************
    ifstream prueba(ARCHIVO_VUELOS);
    string linea;
    string vertice1, vertice2;
    unsigned costo, cont = 1;
    double horas;

    Grafo test;
    while(!prueba.eof()){
        cout << "Linea: " << cont << endl;
        getline(prueba, linea);
        cout << linea << endl;
        istringstream cadena(linea);
        cadena >> vertice1;
        cadena >> vertice2;
        cadena >> costo;
        cadena >> horas;
        if(!test.existeVertice(vertice1)){
            test.agregarVertice(vertice1);
        }
        if(!test.existeVertice(vertice2)){
            test.agregarVertice(vertice2);
        }
        test.agregarArista(test.obtenerVertice(vertice1), test.obtenerVertice(vertice2), costo, horas);
        cont++;
    }
    prueba.close();
    cout << "Vertices en grafo:" << endl;
    Vertice* otroAuxiliar = test.obtenerPrimero();
    for(int i = 0; i < test.cantVertices(); i++){
        cout << otroAuxiliar->obtenerNombreVertice() << endl;
        otroAuxiliar = otroAuxiliar->obtenerProxVertice();
    }

    string desde, hasta;
    bool existe1 = false, existe2 = false;
    do{
        do{
            cout << "Desde ('salir' para salir menu): ";
            cin >> desde;
            if(test.existeVertice(desde)){
                existe1 = true;
            }
        }while((desde != "salir") && !existe1);
        while((desde != "salir") && ((hasta != "salir") && !existe2)){
            cout << "Hasta ('salir' para salir menu): ";
            cin >> hasta;
            if(test.existeVertice(hasta)){
                existe2 = true;
            }
        }
        if(existe1 && existe2){
            cout << "Consulta desde: " << desde << endl;
            cout << "Hasta: " << hasta << endl;
            cout << endl;
            cout << "MEJOR PRECIO" << endl;
            cout << "------------" << endl;
            test.caminoMinimo(test.obtenerVertice(desde), test.obtenerVertice(hasta), 1);
            cin.get();
            cin.get();
            cout << "MEJOR HORA VUELO" << endl;
            cout << "----------------" << endl;
            test.caminoMinimo(test.obtenerVertice(desde), test.obtenerVertice(hasta), 2);
            cin.get();
            //cin.get();
        }
        existe1 = false;
        existe2 = false;

    }while((desde != "salir") && (hasta != "salir"));

    return 0;
    //****************************************************************************
    //****************************************************************************

    VerificadorDatos chequeo;
    manejoDeArchivos archivo;
    Menu menu;
    BST<Aeropuerto*>* aeropuertos = new BST<Aeropuerto*>();
//**********************************************
//    Grafo* vuelos = new Grafo;
//**********************************************
    if(archivo.existe(ARCHIVO_IATA)){
        archivo.cargarAeropuertos(aeropuertos, ARCHIVO_IATA);
    }
    menu.setAeropuertos(aeropuertos);
    if(archivo.existe(ARCHIVO_VUELOS)){
        //**********************************************
        //archivo.cargarVuelos(vuelos, ARCHIVO_VUELOS);
        //**********************************************
    } else{
//**********************************************
        //vuelos = NULL;
//**********************************************
    }
//**********************************************
//    menu.setVuelos(vuelos);
//**********************************************
    while (menu.getOpcion() != '0'){
        menu.mostrarMenuPrincipal();
        menu.hacerEleccion();
        menu.pausa();
    }

    delete aeropuertos;
//**********************************************
    //delete vuelos;
//**********************************************
    return 0;
}

    //===================================PARA PROBAR EL GRAFO====================================
    /*
    Grafo grafo;

    grafo.insertarVertice("TIJ", 1);
    grafo.insertarVertice("MZT", 1);
    grafo.insertarVertice("MTY", 1);
    grafo.insertarVertice("BJX", 1);
    grafo.insertarVertice("GDL", 1);
    grafo.insertarVertice("SAN", 1);
    grafo.insertarVertice("TAM", 1);
    grafo.insertarVertice("MEX", 1);
    grafo.insertarVertice("CUN", 1);
    grafo.insertarVertice("GDL", 1);
    grafo.insertarVertice("MID", 1);

    //Recibe la direccion de memoria del origen y destino (vertices) y los datos del camino
    grafo.insertarArista(grafo.obtenerVertice("TIJ"), grafo.obtenerVertice("MTY"), 800, 9.2);
    grafo.insertarArista(grafo.obtenerVertice("MTY"), grafo.obtenerVertice("BJX"), 700, 13);
    grafo.insertarArista(grafo.obtenerVertice("BJX"), grafo.obtenerVertice("SAN"), 400, 2.2);
    grafo.insertarArista(grafo.obtenerVertice("BJX"), grafo.obtenerVertice("TAM"), 9000, 10.8);
    grafo.insertarArista(grafo.obtenerVertice("BJX"), grafo.obtenerVertice("MEX"), 350, 5.5);
    grafo.insertarArista(grafo.obtenerVertice("SAN"), grafo.obtenerVertice("MID"), 9900, 5.5);
    grafo.insertarArista(grafo.obtenerVertice("TAM"), grafo.obtenerVertice("MID"), 200, 5.5);
    grafo.insertarArista(grafo.obtenerVertice("MEX"), grafo.obtenerVertice("MID"), 450, 5.5);
    grafo.insertarArista(grafo.obtenerVertice("MEX"), grafo.obtenerVertice("CUN"), 650, 5.5);
    grafo.insertarArista(grafo.obtenerVertice("CUN"), grafo.obtenerVertice("GDL"), 650, 5.5);
    grafo.insertarArista(grafo.obtenerVertice("GDL"), grafo.obtenerVertice("BJX"), 250, 5.5);
    grafo.insertarArista(grafo.obtenerVertice("GDL"), grafo.obtenerVertice("MTY"), 450, 5.5);
    grafo.insertarArista(grafo.obtenerVertice("GDL"), grafo.obtenerVertice("MZT"), 500, 5.5);
    grafo.insertarArista(grafo.obtenerVertice("MZT"), grafo.obtenerVertice("BJX"), 300, 5.5);
    grafo.insertarArista(grafo.obtenerVertice("MZT"), grafo.obtenerVertice("TIJ"), 400, 5.5);


    //Cantidad de vertices
    //cout << grafo.obtenerTamanio() << endl;

    //Aca hice una prueba de obtener el costo entre 2 vertices pasandole solo los nombres de origen y destino (Deberia hacerse con Djikstra)
    //El metodo obtenerArista se encarga de recorrer el vector de aristas de el vertice ORIGEN
    //y cuando la direccion del destino que esta cargada en la arista coincide con el pasado como atributo devuelve esa arista
    //habilitando a consultar los datos (precio y horasVuelo).

    //cout << endl << grafo.mejorCamino(grafo.obtenerVertice("EZE"), grafo.obtenerVertice("MIA"));
    //cout << endl << grafo.mejorCamino(grafo.obtenerVertice("EZE"), grafo.obtenerVertice("TXL"));
    grafo.mejorCamino(grafo.obtenerVertice("MTY"), grafo.obtenerVertice("TAM"));
    grafo.mejorCamino(grafo.obtenerVertice("TIJ"), grafo.obtenerVertice("MID"));
    */

