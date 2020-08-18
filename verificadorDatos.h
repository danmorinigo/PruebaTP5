#ifndef VERIFICADORDATOS_H_INCLUDED
#define VERIFICADORDATOS_H_INCLUDED
#include<iostream>
#include<sstream>
using namespace std;

class VerificadorDatos{
private:
public:
	// Constructor sin parametros de la clase VerificadorDatos.
    //PRE: Ninguna
    //POST: Se crea un objeto de Clase VerificadorDatos.
    VerificadorDatos();

    //Destructor de la clase VerificadorDatos.
    ~VerificadorDatos();

    //PRE: Recibe una cadena de caracteres.
    //POST: Verifica si la cadena recibida corresponde a un codigo IATA devolviendo Verdadero si efectivamente lo es o falso en caso contrario.
    bool esIATA(string aVerificar);

    //PRE: Recibe una cadena de caracteres.
    //POST: Verifica si la cadena recibida corresponde a un numero real devolviendo Verdadero si efectivamente lo es o falso en caso contrario.
    bool esDouble(string aVerificar);

    //PRE: Recibe una cadena de caracteres.
    //POST: Verifica si la cadena recibida corresponde a un numero entero devolviendo Verdadero si efectivamente lo es o falso en caso contrario.
    bool esEntero(string aVerificar);

    //PRE: Recibe una cadena de caracteres.
    //POST: Verifica si la cadena recibida corresponde al formato valido de un aeropuerto devolviendo Verdadero si efectivamente lo es 
    //      o falso en caso contrario.
    bool esAeropuerto(string aVerificar);

    //PRE: Recibe una cadena de caracteres.
    //POST: Verifica si la cadena recibida corresponde al formato valido de un vuelo devolviendo Verdadero si efectivamente lo es 
    //      o falso en caso contrario.
    bool esVuelo(string aVerificar);
};

#endif // VERIFICADORDATOS_H_INCLUDED
