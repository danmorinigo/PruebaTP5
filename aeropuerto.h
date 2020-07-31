#ifndef AEROPUERTO_H_INCLUDED
#define AEROPUERTO_H_INCLUDED
#include <iostream>

using namespace std;

const bool MUESTRAMEM = true;

class Aeropuerto{
private:
    string IATA;
    string nombre;
    string ciudad;
    string pais;
    double superficie;
    unsigned terminales;
    unsigned destinosNacionales;
    unsigned destinosInternacionales;
public:
    Aeropuerto();
    ~Aeropuerto();

    void asignarCodigo(string);
    void asignarNombre(string);
    void asignarCiudad(string);
    void asignarPais(string);
    void asignarSup(double);
    void asignarTerminales(unsigned);
    void asignarDestNac(unsigned);
    void asignarDestInternac(unsigned);

    string obtenerCodigo();
    string obtenerNombre();
    string obtenerCiudad();
    string obtenerPais();
    double obtenerSup();
    unsigned obtenerTerminales();
    unsigned obtenerDestNac();
    unsigned obtenerDestInternac();
    void mostrarInformacion();
};


#endif // AEROPUERTO_H_INCLUDED
