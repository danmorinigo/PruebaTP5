#ifndef MANEJODEARCHIVOS_H_INCLUDED
#define MANEJODEARCHIVOS_H_INCLUDED

#include <fstream>
#include "BST.h"
#include "aeropuerto.h"
#include "Grafo.h"
#include "verificadorDatos.h"

using namespace std;

class ManejoDeArchivos{
private:
    VerificadorDatos chequear;
public:
    // Constructor sin parametros de la clase Menu.
    //PRE: Ninguna
    //POST: Se crea un objeto de Clase ManejoDeArchivos.
    ManejoDeArchivos();
    
    //PRE: Debe existir el objeto de clase ManejoDeArchivos.
    //POST: Recibe por paramentro en una cadena de caracteres el nombre del archivo o la direccion.
    //      Devuelve Verdadero si el archivo existe y Falso en caso contrario.
    bool existe(string nombreArchivo);

    //PRE: Se debe haber verificado si el archivo existe, por ejemplo con el metodo existe(string).
    //POST: Devuelve el arbol pasado por parametro cargado con la lectura del archivo tambien pasado por parametro.
    void cargarAeropuertos(BST<Aeropuerto*>* arbol, string nombreArchivo);

    //PRE: Se debe verificar que la cadena de caracteres pasada por parametro sea un aeropuerto
    //POST: Se carga el aerpuerto al arbol.
    void agregarAero(BST<Aeropuerto*>* arbol, string linea);
    
    //PRE: Se debe verificar que la cadena de caracteres pasada por parametro corresponda a un archivo existente.
    //POST: Se carga el grafo enviado por paramentro con la lectura del archivo correspondiente a la cadena de caracteres.
    void cargarVuelos(Grafo* vuelos, string nombreArchivo);

    //PRE: La linea ingresada es un vuelo valido con el formato correcto.
    //POST: Se agrega un nuevo vuelo al grafo vuelos.
    void agregarVuelo(Grafo* vuelos, string linea);
    
    //PRE: Recibe una cadena de caracteres con el formato de vuelo leido desde el archivo txt, con guiones.
    //POST: Elimina los guiones de la cadena y los reemplaza con un espacio.
    string quitarGuion(string texto);

    //Destructor de la clase ManejoDeArchivos
    ~ManejoDeArchivos();
};
#endif // MANEJODEARCHIVOS_H_INCLUDED
