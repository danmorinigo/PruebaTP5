#ifndef VERIFICADORDATOS_H_INCLUDED
#define VERIFICADORDATOS_H_INCLUDED
#include<iostream>
#include<sstream>
using namespace std;

class VerificadorDatos{
private:
public:
    VerificadorDatos();
    ~VerificadorDatos();
    bool esIATA(string aVerificar);
    bool esDouble(string aVerificar);
    bool esEntero(string aVerificar);
    bool esAeropuerto(string aVerificar);
    bool esVuelo(string aVerificar);
};

#endif // VERIFICADORDATOS_H_INCLUDED
