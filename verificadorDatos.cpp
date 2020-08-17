#include "verificadorDatos.h"

VerificadorDatos::VerificadorDatos(){
}
bool VerificadorDatos::esEntero(string aVerificar){
    bool esEntero;
    for(unsigned i = 0; i < aVerificar.length(); i++){
        esEntero = (aVerificar[i] > 47 && aVerificar[i] < 58);//es un numero 0 al 9
        if(!esEntero){
            return false;
        }
    }
    return true;
}

bool VerificadorDatos::esDouble(string aVerificar){
    bool esEntero, esUnPunto, esUnaComa;
    unsigned signoPuntuacion = 0;
    for(unsigned i = 0; i < aVerificar.length(); i++){
        esEntero = (aVerificar[i] > 47 && aVerificar[i] < 58);//es un numero 0 al 9
        esUnPunto = (aVerificar[i] == 46);//es un punto
        esUnaComa = (aVerificar[i] == 44);//es una coma
        if(!esEntero && !esUnPunto && !esUnaComa){//si no es ninguno de los anteriores no pasa
            return false;
        }
        if(esUnPunto || esUnaComa){
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
    bool esValido = false;
    if(aVerificar.length() == 3){//IATA son 3 letras
        for(int i = 0; i < 3; i++){
            esValido = true;
            bool esMayuscula = (aVerificar[i] > 64 && aVerificar[i] < 91); //es una mayuscula
            bool esMinuscula = (aVerificar[i] > 96 && aVerificar[i] < 123);//es una minuscula
            if(!esMayuscula /*&& !esMinuscula*/){//si ambas son falsas no pasa verificacion
                return false;
            }
        }
    }
    return esValido;
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

bool VerificadorDatos::esVuelo(string aVerificar){
    istringstream cadena(aVerificar);
    string tempStr;
    unsigned cantDatos = 0;
    while(!cadena.eof()){
        cadena >> tempStr;// partida
        cout<<"Se va verificar si "<<tempStr<<" es IATA."<<endl;
        if(!esIATA(tempStr)){
            return false;
        }
        cantDatos++;
        cadena >> tempStr;// destino
        cout<<"Se va verificar si "<<tempStr<<" es IATA."<<endl;
        if(!esIATA(tempStr)){
            return false;
        }
        cantDatos++;
        cadena >> tempStr;// COSTO EN DINERO
        cout<<"Se va verificar si "<<tempStr<<" es entero."<<endl;
        if(!esEntero(tempStr)){
            return false;
        }
        cantDatos++;
        cadena >> tempStr;// TIEMPO
        cout<<"Se va verificar si "<<tempStr<<" es double."<<endl;
        if(!esDouble(tempStr)){
            return false;
        }
        cantDatos++;
    }
    if(cantDatos != 4){
        return false;
    }
    return true;
}
VerificadorDatos::~VerificadorDatos(){
}
