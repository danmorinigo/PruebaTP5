#include "menu.h"

Menu::Menu(){
   this-> opcion = '.';
   this-> aeropuertos = NULL;

}

char Menu::getOpcion(){
    return this-> opcion;
}


void Menu::setAeropuertos(BST<Aeropuerto*>* aeropuertos){
    this-> aeropuertos = aeropuertos;
}

void Menu::limpiarPantalla(){
    #ifdef _WIN32
        system ("cls");
    #else
        // Assume POSIX
        system ("clear");
    #endif
}

void Menu::mostrarMenuPrincipal(){
    this->limpiarPantalla();
    cout << endl;
    cout << "\t1- Consultar por un aeropuerto en particular." << endl;
    cout << "\t2- Dar de alta un nuevo aeropuerto." << endl;
    cout << "\t3- Dar de baja un aeropuerto." << endl;
    cout << "\t4- Mostrar todos los aeropuertos (recorrido in orden)." << endl;
    cout << "\t5- Mostrar arbol de aeropuertos (recorrido en ancho)." << endl;
    cout << "\t0- Salir." << endl;
    cout << endl;
    cout << "\tEleccion: ";
    cin >> this->opcion;
}

void Menu::hacerEleccion(){
    char opcion2;
    switch (this->opcion){
        case '1': { this-> limpiarPantalla();
                    this->consultarAeropuerto();
                    //cout << "ACA DEBERIA MOSTRAR: 'Ingrese código IATA del aeropuerto: '"<<endl;
                   // cin>> opcion2;
                    this->pausa();
                }break;
        case '2': { this-> limpiarPantalla();
                    this-> agregarAeropuerto();
                    //cout << "ACA DEBERIA MOSTRAR MENU DE INGRESO DE NUEVO AEROPUERTO."<<endl;
                    this->pausa();
                }break;
        case '3': { this-> limpiarPantalla();
                    this->darDeBajaAeropuerto();
//                     cout << "ACA DEBERIA MOSTRAR: 'Ingrese codigo IATA del aeropuerto a dar de baja: '"<<endl;
                    this->pausa();
                }break;
        case '4': { this-> limpiarPantalla();
                    //cout << "ACA DEBERIA MOSTRAR LOS AEROPUERTOS IN-ORDER."<<endl;
                    this->aeropuertos->print_in_order();
                    cout<<endl;
                    this->pausa();
                }break;
        case '5': { this-> limpiarPantalla();
                    this->aeropuertos->imprime_en_ancho();
                    cout<<endl;
                    //cout << "ACA DEBERIA MOSTRAR ARBOL RECORRIDO EN ANCHO"<<endl;
                    this->pausa();
                }break;
        case '0': { this-> limpiarPantalla();
                    this-> despedida();
                    this->pausa();
                }break;
    }
}

void Menu::consultarAeropuerto(){
    string abuscar;
    BSTNode<Aeropuerto*>* aeropuerto;
    this->limpiarPantalla();
    cout<<endl<<"Ingrese el codigo IATA del aeropuerto que desea buscar: ";
    cin >> abuscar;
    aeropuerto = this->aeropuertos->buscar (abuscar);
    if (aeropuerto){
       aeropuerto->get_data()->mostrarInformacion();
    }
}

void Menu::agregarAeropuerto(){
    Aeropuerto* nuevoAeropuerto = new Aeropuerto;
    string palabra;
    unsigned entero;
    double real;

    cout<<endl<<"INGRESAR NUEVO AEROPUERTO: "<<endl;
    cout<<"Ingrese codigo IATA: ";
    cin >> palabra;
    nuevoAeropuerto->asignarCodigo(palabra);
    cout<<endl;
    cout<<"Ingrese el nombre: ";
    cin >> palabra;
    nuevoAeropuerto->asignarNombre(palabra);
    cout<<endl;
    cout<<"Ingrese el ciudad: ";
    cin >> palabra;
    nuevoAeropuerto->asignarCiudad(palabra);
    cout<<endl;
    cout<<"Ingrese el pais: ";
    cin >> palabra;
    nuevoAeropuerto->asignarPais(palabra);
    cout<<endl;
    cout<<"Ingrese el superficie: ";
    cin >> real;
    nuevoAeropuerto->asignarSup(real);
    cout<<endl;
    cout<<"Ingrese cantindad de terminales: ";
    cin >> entero;
    nuevoAeropuerto->asignarTerminales(entero);
    cout<<endl;
    cout<<"Ingrese cantindad de destinos nacionales: ";
    cin >> entero;
    nuevoAeropuerto->asignarDestNac(entero);
    cout<<endl;
    cout<<"Ingrese cantindad de destinos internacionales: ";
    cin >> entero;
    nuevoAeropuerto->asignarDestInternac(entero);
    cout<<endl;

    this->aeropuertos->insert(nuevoAeropuerto, nuevoAeropuerto->obtenerCodigo());

}

BSTNode<Aeropuerto*>* Menu::buscarMenor(BSTNode<Aeropuerto*> *aeropuerto){
    if(aeropuerto == NULL){
        return NULL;
    }
    if(aeropuerto->get_left()){
        return buscarMenor(aeropuerto->get_left());
    }
    return aeropuerto;
}

void Menu::reemplazar(BSTNode<Aeropuerto*>* antiguo, BSTNode<Aeropuerto*>* nuevo){
    if(antiguo->get_parent()){
        if(antiguo->get_data() == antiguo->get_parent()->get_left()->get_data()){
            antiguo->get_parent()->set_left(nuevo);
        }
        else if(antiguo->get_data() == antiguo->get_parent()->get_right()->get_data()){
            antiguo->get_parent()->set_right(nuevo);
        }
    }
    if(nuevo){
        nuevo->set_parent(antiguo->get_parent());
    }
}

void Menu::destruir(BSTNode<Aeropuerto*>* aeropuerto){
    aeropuerto->set_left(NULL);
    aeropuerto->set_right(NULL);

    delete aeropuerto;
}


void Menu::eliminarAeropuerto(string codigo){
    BSTNode<Aeropuerto*>* aeropuerto;
    aeropuerto = this->aeropuertos->buscar (codigo);

    if(aeropuerto->get_right() && aeropuerto->get_left()){
        BSTNode<Aeropuerto*>* menor = buscarMenor(aeropuerto->get_right());
        aeropuerto->set_data(menor->get_data());
        eliminarAeropuerto(menor->get_IATA());
    }
    else if(aeropuerto->get_left()){
        reemplazar(aeropuerto, aeropuerto->get_left());
        destruir(aeropuerto);
    }
    else if(aeropuerto->get_right()){
        reemplazar(aeropuerto, aeropuerto->get_right());
        destruir(aeropuerto);
    }
    else{
        reemplazar(aeropuerto, NULL);
        destruir(aeropuerto);
    }


}

void Menu::darDeBajaAeropuerto(){
    string codigo;
    cout<<"DAR DE BAJA UN AEROPUERTO."<<endl;
    //----------------------------------------------------------------------
    cout<< "Ingrese el codigo IATA nombre del aeropuerto que quiere dar de baja: \n";
    cout << "Aeropuerto: ";
    cin >> codigo;

    //----------------------------------------------------------------------
    /* A PARTIR DE ACA MODIFICO
    cout<< "Ingrese el codigo IATA del aeropuerto que quiere dar de baja: ";
    cin >> codigo;

    eliminarAeropuerto(codigo);
    */
}

void Menu::despedida(){
    enmarcar("FIN DEL PROGRAMA");
}

void Menu::pausa(){
    cout << "<Enter>";
    cin.get();
}

void Menu::enmarcar(string texto){
    int margen, tamanio = texto.length();
    margen = ((ANCHO_PANTALLA / 2) - (tamanio / 2));    //Utilizp para centrar recuadro.
    for( int i = 0; i < margen; i++) cout << " ";
    cout << "[";//(char)218;
    for( int i = 0; i < tamanio; i++) cout <<"-";// (char)196;
    cout << "]"/*(char)191 */<< endl;
    for( int i = 0; i < margen; i++) cout << " ";
    cout << /*(char)179*/"|" << texto << /*(char)179*/"|"  << endl;
    for( int i = 0; i < margen; i++) cout << " ";
    cout <<"[";// (char)192;
    for( int i = 0; i < tamanio; i++) cout <<"-";//(char)196;
    cout << "]"/*(char)217*/ << endl;
}

void Menu::salir(){
    this->limpiarPantalla();
    //cabecera();
    despedida();
    this-> pausa();
}

Menu::~Menu(){

}
