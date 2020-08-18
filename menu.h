#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <iostream>
#include <string>
#include "BST.h"
#include "aeropuerto.h"
#include "Grafo.h"

const int ANCHO_PANTALLA = 60;

using namespace std;

class Menu {

private:
    char opcion;
    char opcionVuelos;
    string partida;
    string destino;
    BST<Aeropuerto*>* aeropuertos;
    Grafo* vuelos;

public:
    // Constructor sin parametros de la clase Menu.
    //PRE: Ninguna
    //POST: Se crea un objeto de Clase Menu.
    Menu();

    //PRE: Tiene que estar creado el objeto de clase Menu.
    //POST: Se obtiene el valor char del atributo opcion.
    char getOpcion();
    
    //PRE: Tiene que estar creado el objeto de clase Menu.
    //POST:Se obtiene el valor char del atributo opcionVuelos.
    char getOpcionVuelos();

    //PRE: Tiene que estar creado el objeto de clase Menu.
    //POST: Se asigna el valor del atributo aeropuertos ingresado por parametro. Recibe un puntero a un ABB de punteros a objetos Aeropuerto.
    void setAeropuertos(BST<Aeropuerto*>*);
    
    //PRE: Tiene que estar creado el objeto de clase Menu.
    //POST: Se asigna el valor del atributo vuelos ingresado por parametro. Recibe un puntero a un objeto de clase Grafo.
    void setVuelos(Grafo*);
    
    //PRE: Tiene que estar creado el objeto de clase Menu.
    //POST: Devuelve Verdadero si existe al menos un vuelo cargado y Falso en caso contrario.
    bool hayVuelosCargados();

    //PRE:  --
    //POST: Borra lo impreso en pantalla. Cursor vuelve a posicion (1, 1).
    void limpiarPantalla();

    //PRE: Tiene que estar creado el objeto de clase Menu.
    //POST: Muestra opciones del programa.
    void mostrarMenuPrincipal();
    
    //PRE: Se tiene que haber ingresado una opcion valida desde el Menu principal del programa.
    //POST: Hace lo correspondiente a la eleccion ingresada por el usuario en el Menu principal. 
    void hacerEleccion();
    
    //PRE: Tiene que estar creado el objeto de clase Menu y tiene que tener cargado el atributo aeropuertos.
    //     Recibe el codigo IATA en letras mayusculas o el nombre correcto del aeropuerto.
    //POST: Se muestra por pantalla toda la informacion del aeropuerto solicitado.
    void consultarAeropuerto();
    
    //PRE: Tiene que estar creado el objeto de clase Menu.
    //POST: Se realiza el ingreso de un aeropuerto nuevo solicitando cada uno de los datos necesarios. El valor del codigo IATA (debe ser
    //      ingresado en mayuscula para su correcta carga), del nombre, de la ciudad y del pais se ingresan como cadena de caracteres. 
    //      La superficie debe ser ingresada como un flotante, y la cantidad
    //      de terminales, los destinos nacionales e internacionales deben ser ingresadas como valores enteros.
    void agregarAeropuerto();

    //PRE: Debe estar cargado el atributo aeropuertos. Este metodo es usado por el metodo darDeBajaAeropuerto().
    //POST: Se elimina del arbol del atributo aeropuertos, el aeropuerto ingresado por parametro.
    void eliminarAeropuerto(string codigo);
    
    //PRE: Debe estar cargado el atributo aeropuertos.
    //POST: Se da debaja el aeropuerto ingresado por el usuario.
    void darDeBajaAeropuerto();
    
    //PRE: Debe estar cargado el atributo vuelos (puntero a clase Grafo).
    //POST: Solicita al usuario el aeropuerto de partida y de destino del vuelo a buscar.
    void solicitarPartidaYDestino();
    
    //PRE: Tiene que estar creado el objeto de clase Menu.
    //POST: Se muestra por pantalla la posibilidad para buscar el vuelo con mejor precio o el mas rapido.
    void mostrarMenuVuelos();
    
    //PRE: Se tiene que haber ejecutado el metodo mostrarMenuVuelos().
    //POST: Se muestra el resultado de la busqueda segun la eleccion del usuario. 
    void hacerEleccionMenuVuelos();

    //PRE: Tiene que estar creado el objeto de clase Menu.
    //POST: Recibe lo que el usuario ingresa por teclado, incluyendo espacios, y lo devuelve como un string con el contenido.
    string ingresarNombre();

    //PRE: Tiene que estar creado el objeto de clase Menu.
    //POST: Recibe lo que el usuario ingresa por teclado. Si el codigo ingresado ya existe solicita un nuevo ingreso.
    string ingresarIATA();

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

 /*Uso para buscar el menor de los dos hijos*/
    //PRE:--
    //POST: 
   // BSTNode<Aeropuerto*>* buscarMenor(BSTNode<Aeropuerto*> *aeropuerto);

    /*Uso para reemplazar un nodo por otro*/
    //PRE:--
    //POST: 
  //  void reemplazar(BSTNode<Aeropuerto*>* antiguo, BSTNode<Aeropuerto*>* nuevo);

    /*Uso para destruir un nodo*/
    //PRE:--
    //POST: 
  //  void destruir(BSTNode<Aeropuerto*>* aeropuerto);
