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

    /*Uso para buscar el menor de los dos hijos*/
    BSTNode<Aeropuerto*>* buscarMenor(BSTNode<Aeropuerto*> *aeropuerto);

    /*Uso para reemplazar un nodo por otro*/
    void reemplazar(BSTNode<Aeropuerto*>* antiguo, BSTNode<Aeropuerto*>* nuevo);

    /*Uso para destruir un nodo*/
    void destruir(BSTNode<Aeropuerto*>* aeropuerto);

    /*Cree este metodo porque necesitaba volver a llamarlo recursivamente, pero si usaba el metodo darDeBaja otra vez
     tenia que pasar por el cin del codigo, entonces la funcion darDeBaja, llama a esta, con el codigo que introduce el usuario.*/
    void eliminarAeropuerto(string codigo);

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
