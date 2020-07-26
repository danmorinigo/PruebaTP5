#include "verificadorDatos.h"

VerificadorDatos::VerificadorDatos(){
}
bool VerificadorDatos::esEntero(string aVerificar){
    bool condicion;
    for(unsigned i = 0; i < aVerificar.length(); i++){
        condicion = (aVerificar[i] > 47 && aVerificar[i] < 58);//es un numero 0 al 9
        if(!condicion){
            return false;
        }
    }
    return true;
}
bool VerificadorDatos::esDouble(string aVerificar){
    bool condicion1, condicion2, condicion3;
    unsigned signoPuntuacion = 0;
    for(unsigned i = 0; i < aVerificar.length(); i++){
        condicion1 = (aVerificar[i] > 47 && aVerificar[i] < 58);//es un numero 0 al 9
        condicion2 = (aVerificar[i] == 46);//es un punto
        condicion3 = (aVerificar[i] == 44);//es una coma
        if(!condicion1 && !condicion2 && !condicion3){//si no es ninguno de los anteriores no pasa
            return false;
        }
        if(condicion2 || condicion3){
            signoPuntuacion++;
        }
        if(signoPuntuacion > 1){//solo se permite un punto o coma
            return false;
        }
    }
    return true;
}
//el if verifica que sea letra, o bien mayuscula o bien minuscula
bool VerificadorDatos::esIATA(string aVerificar){
    bool esOno = false;
    if(aVerificar.length() == 3){//IATA son 3 letras
        for(int i = 0; i < 3; i++){
            esOno = true;
            bool condicion1 = (aVerificar[i] > 64 && aVerificar[i] < 91); //es una mayuscula
            bool condicion2 = (aVerificar[i] > 96 && aVerificar[i] < 123);//es una minuscula
            if(!condicion1 && !condicion2){//si ambas son falsas no pasa verificacion
                return false;
            }
        }
    }
    return esOno;
}
bool VerificadorDatos::esAeropuerto(string aVerificar){
    istringstream cadena(aVerificar);
    string tempStr;
    unsigned cantDatos = 0;
    while(!cadena.eof()){
        cadena >> tempStr;//IATA?
        if(!esIATA(tempStr)){
            return false;
        }
        cantDatos++;
        cadena >> tempStr;//Nombre? siempre si
        cantDatos++;
        cadena >> tempStr;//Ciudad? siempre si
        cantDatos++;
        cadena >> tempStr;//Pais? siempre si
        cantDatos++;
        cadena >> tempStr;//Superficie?
        if(!esDouble(tempStr)){
            return false;
        }
        cantDatos++;
        cadena >> tempStr;//Terminales?
        if(!esEntero(tempStr)){
            return false;
        }
        cantDatos++;
        cadena >> tempStr;//Destinos Nacionales?
        if(!esEntero(tempStr)){
            return false;
        }
        cantDatos++;
        cadena >> tempStr;//Destinos InterNacionales?
        if(!esEntero(tempStr)){
            return false;
        }
        cantDatos++;
    }
    if(cantDatos != 8){
        return false;
    }
    return true;
}
VerificadorDatos::~VerificadorDatos(){
}
