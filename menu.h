#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <iostream>
#include <string>
#include "BST.h"
#include "aeropuerto.h"

const int ANCHO_PANTALLA = 60;

using namespace std;

class Menu {

private:
    char opcion;
    BST<Aeropuerto*>* aeropuertos;

public:
    // Constructor sin par�metros de la clase Menu.
    //PRE: Ninguna
    //POST: Se crea un objeto de Clase Menu. 
    Menu();
    
    char getOpcion();
    
    void setAeropuertos(BST<Aeropuerto*>*);
    //PRE:  --
    //POST: Borra lo impreso en pantalla. Cursor vuelve a posicion (1, 1).
    void limpiarPantalla();
    //PRE:  --
    //POST: Muestra opciones del programa.
    void mostrarMenuPrincipal();
    
    void hacerEleccion();

    void consultarAeropuerto();

    void agregarAeropuerto();

    void darDeBajaAeropuerto();
    //PRE:  --
    //POST: Muestra cartel de despedida.
    void despedida();

    //PRE:  --
    //POST: Pide al usuario pulsar tecla Enter para continuar.
    void pausa();

    //PRE:  --
    //POST: Muestra texto en un marco.
    void enmarcar(string texto);

    //PRE:  --
    //POST: Secuencia a seguir antes de finalizar el programa.
    void salir();

    //Destructor
    //PRE:  --
    //POST: 
    ~Menu();
};


#endif // MENU_H_INCLUDED