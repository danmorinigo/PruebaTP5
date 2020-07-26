#include "aeropuerto.h"

Aeropuerto::Aeropuerto(){
    IATA = "";
    nombre = "";
    ciudad = "";
    pais = "";
    superficie = 0.0;
    terminales = 0;
    destinosNacionales = 0;
    destinosInternacionales = 0;
    if(MUESTRAMEM) cout << "\nContructor AEROPUERTO (" << this << ")\n";
}
Aeropuerto::~Aeropuerto(){
    if(MUESTRAMEM) cout << "\nDestructor AEROPUERTO (" << this << ")\n";
}
void Aeropuerto::asignarCodigo(string codigo){
    this->IATA = codigo;
}
void Aeropuerto::asignarNombre(string nombre){
    this->nombre = nombre;
}
void Aeropuerto::asignarCiudad(string ciudad){
    this->ciudad = ciudad;
}
void Aeropuerto::asignarPais(string pais){
    this->pais = pais;
}
void Aeropuerto::asignarSup(double sup){
    this->superficie = sup;
}
void Aeropuerto::asignarTerminales(unsigned teminales){
    this->terminales = terminales;
}
void Aeropuerto::asignarDestNac(unsigned nacionales){
    this->destinosNacionales = nacionales;
}
void Aeropuerto::asignarDestInternac(unsigned internacionales){
    this->destinosInternacionales = internacionales;
}
string Aeropuerto::obtenerCodigo(){
    return this->IATA;
}
string Aeropuerto::obtenerNombre(){
    return this->nombre;
}
string Aeropuerto::obtenerCiudad(){
    return this->ciudad;
}
string Aeropuerto::obtenerPais(){
    return this->pais;
}
double Aeropuerto::obtenerSup(){
    return this->superficie;
}
unsigned Aeropuerto::obtenerTerminales(){
    return this->terminales;
}
unsigned Aeropuerto::obtenerDestNac(){
    return this->destinosNacionales;
}
unsigned Aeropuerto::obtenerDestInternac(){
    return this->destinosInternacionales;
}
