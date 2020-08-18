#ifndef AEROPUERTO_H_INCLUDED
#define AEROPUERTO_H_INCLUDED
#include <iostream>

using namespace std;

const bool MUESTRAMEM = false;

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
    // Constructor sin parametros de la clase Aeropuerto.
    //PRE: Ninguna
    //POST: Se crea un objeto de Clase Aeropuerto con los atributos IATA, nombre, ciudad y pais inicializados en cadena vacia ("") 
    //y los atributos superficie, terminales, destinosNacionales y destinosInternacionales inicializados en 0.
    Aeropuerto();

    //Destructor de la clase Aeropuerto.
    ~Aeropuerto();
    
    //PRE: Debe estar creado el objeto de clase Aeropuerto.
    //POST: Se le asigna al atributo IATA el valor ingresado por parametro.
    void asignarCodigo(string);

    //PRE: Debe estar creado el objeto de clase Aeropuerto.
    //POST: Se le asigna al atributo nombre el valor ingresado por parametro.
    void asignarNombre(string);

    //PRE: Debe estar creado el objeto de clase Aeropuerto.
    //POST: Se le asigna al atributo ciudad el valor ingresado por parametro.
    void asignarCiudad(string);

    //PRE: Debe estar creado el objeto de clase Aeropuerto.
    //POST: Se le asigna al atributo pais el valor ingresado por parametro.
    void asignarPais(string);

    //PRE: Debe estar creado el objeto de clase Aeropuerto.
    //POST: Se le asigna al atributo superficie el valor double ingresado por parametro.
    void asignarSup(double);

    //PRE: Debe estar creado el objeto de clase Aeropuerto.
    //POST: Se le asigna al atributo terminales el valor entero ingresado por parametro.
    void asignarTerminales(unsigned);

    //PRE: Debe estar creado el objeto de clase Aeropuerto.
    //POST: Se le asigna al atributo destinosNacionales el valor entero ingresado por parametro.
    void asignarDestNac(unsigned);

    //PRE: Debe estar creado el objeto de clase Aeropuerto.
    //POST: Se le asigna al atributo destinosInternacionales el valor entero ingresado por parametro.
    void asignarDestInternac(unsigned);
    
    //PRE: Debe estar creado el objeto de clase Aeropuerto.
    //POST: Devuelve el codigo Iata del atributo IATA.
    string obtenerCodigo();

    //PRE: Debe estar creado el objeto de clase Aeropuerto.
    //POST: Devuelve el valor del atributo nombre.
    string obtenerNombre();

    //PRE: Debe estar creado el objeto de clase Aeropuerto.
    //POST: Devuelve el valor del atributo ciudad.
    string obtenerCiudad();

    //PRE: Debe estar creado el objeto de clase Aeropuerto.
    //POST: Devuelve el valor del atributo pais.
    string obtenerPais();

    //PRE: Debe estar creado el objeto de clase Aeropuerto.
    //POST: Devuelve el valor flotante del atributo superficie.
    double obtenerSup();

    //PRE: Debe estar creado el objeto de clase Aeropuerto.
    //POST: Devuelve el valor entero del atributo terminales.
    unsigned obtenerTerminales();

    //PRE: Debe estar creado el objeto de clase Aeropuerto.
    //POST: Devuelve el valor entero del atributo destinosNacionales.
    unsigned obtenerDestNac();

    //PRE: Debe estar creado el objeto de clase Aeropuerto.
    //POST: Devuelve el valor entero del atributo destinosInternacionales.
    unsigned obtenerDestInternac();

    //PRE: Debe estar creado el objeto de clase Aeropuerto.
    //POST: Muestra por pantalla toda la informacion del aeropuerto, el valor de sus atributos.
    void mostrarInformacion();
};


#endif // AEROPUERTO_H_INCLUDED
