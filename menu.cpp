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
                    //this->darDeBajaAeropuerto();
                     cout << "ACA DEBERIA MOSTRAR: 'Ingrese codigo IATA del aeropuerto a dar de baja: '"<<endl;
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
    cout<<endl<<"Ingrese el codigo IATA o nombre del aeropuerto que desea buscar: ";
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

void Menu::darDeBajaAeropuerto(){
    string codigo;
    cout<<"DAR DE BAJA UN AEROPUERTO."<<endl;
    cout<< "Ingrese el codigo IATA del aeropuerto que quiere dar de baja: ";
    cin >> codigo;
    //this->aeropuertos->remove(codigo);
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

/*void Menu::inicializar(string vistas, string noVistas){

    ifstream archivoNoVistas;
    ifstream archivoVistas;

    try {
        archivoNoVistas.open(noVistas);
        archivoVistas.open(vistas);
        if (!archivoNoVistas.fail())
            if (!archivoVistas.fail())
                throw 1;
            else
                throw 2;
        else
            throw 0;

    } catch (int bandera){

        switch (bandera) {
            case 0: //No existe peliculas no vistas
                definirArranque(false);
                archivoNoVistas.close();
                archivoVistas.close();
                cabecera();
                cout << "\n\n\n\n";
                enmarcar("ERROR!");
                enmarcar("No existe el archivo de peliculas no vistas");
                enmarcar("Nombre archivo: " + noVistas);
                cout << "\n\n\n\n\n\n";
                enmarcar("Pulse Enter para finalizar programa");
                cout << endl;
                pausa();
                salir();
                break;

            case 1: //Existen ambos archivos
                definirArranque(true);
                llenarLista(pelisNoVistas, noVistas);
                llenarLista(pelisVistas, vistas);
                recomendar();
                break;

            case 2: //No existe peliculas vistas
                definirArranque(true);
                llenarLista(pelisNoVistas, noVistas);
                recomendarSoloPuntaje();
                break;

            default:
                break;
        }
    }
}

char Menu::comenzar() {

    if (obtenerArranque()) {
        unsigned char eleccion;
        string aux;
        do{
            limpiarPantalla();
            cabecera();         //en clase Pantalla
            menuPrincipal();    //en clase Pantalla
            cin >> aux;
            eleccion = aux[0];
        }while(eleccion < 48 || eleccion > 51);

        cin.get();

        switch (eleccion){
            case 48:
                salir();
                break;

            case 49:
                peliculasVistas();
                break;

            case 50:
                peliculasNoVistas();
                break;

            case 51:
                peliculasRecomendadas();
                break;

            default:
                break;
        }
        return eleccion;
    } else
        return 48;
}
*/
/*void Menu::peliculasVistas(){
    limpiarPantalla();
    if(pelisVistas -> obtenerTamanio()){
        enmarcar("MOSTRAMOS LISTA PELICULAS VISTAS");
        mostrarListadoPeliculas(pelisVistas);
    }else{
        cabecera();
        cout << "\n\n\n\n\n\n";
        enmarcar("ATENCION!");
        enmarcar("NO HAY DATOS DE PELICULAS QUE HAYA VISTO");
        cout << "\n\n\n\n\n\n";
    }
    pausa();
}

void Menu::peliculasNoVistas(){
    limpiarPantalla();
    enmarcar("MOSTRAMOS LISTA PELICULAS NO VISTAS");
    mostrarListadoPeliculas(pelisNoVistas);
    pausa();
}

void Menu::peliculasRecomendadas(){
    limpiarPantalla();
    if(pelisRecomendadas->obtenerTamanio()){
        enmarcar("MOSTRAMOS LISTA PELICULAS RECOMENDADAS");
        mostrarListadoPeliculas(pelisRecomendadas);
    }else{
        cabecera();
        cout << "\n\n\n\n\n\n";
        enmarcar("ATENCION!");
        enmarcar("NO HAY PELICULAS PARA RECOMENDAR");
        cout << "\n\n\n\n\n\n";
    }
    pausa();
}

void Menu::recomendar(){

    Pelicula* vista;
    Pelicula* noVista;
    unsigned int cantPelisNoVistas = pelisNoVistas -> obtenerTamanio();
    unsigned int cantPelisVistas = pelisVistas -> obtenerTamanio();

    for (unsigned i = 1; i < cantPelisNoVistas + 1; i++){
        noVista = pelisNoVistas -> obtenerDato (i);
        if (tienePuntajeAdecuado(noVista)){
            pelisRecomendadas->insertar(noVista, 1);
        } else {
            for (unsigned j = 1; j < cantPelisVistas + 1; j++) {
                vista = pelisVistas -> obtenerDato(j);
                if ((coincideGenero(noVista, vista) && ((coincideDirector(noVista, vista)) || coincideAlMenosUnActor(noVista, vista)))) {
                    pelisRecomendadas -> insertar(noVista, 1);
                }
            }
        }
    }
}

void Menu::recomendarSoloPuntaje(){
    unsigned int cantPelisNoVistas = pelisNoVistas -> obtenerTamanio();
    for (unsigned i = 1; i < cantPelisNoVistas + 1; i++){
        if (tienePuntajeAdecuado(pelisNoVistas -> obtenerDato(i))){ 
            pelisRecomendadas -> insertar(pelisNoVistas -> obtenerDato(i),1);
        }
    }
}

bool Menu::obtenerArranque() const {
    return arranque;
}

void Menu::definirArranque(bool estado){
    this -> arranque = estado;
}
*/

Menu::~Menu(){
    /*for (unsigned i = 0; i < pelisVistas -> obtenerTamanio(); i++){
        delete pelisVistas -> obtenerDato(i + 1);
    }
    delete pelisVistas;

    for (unsigned i = 0; i < pelisNoVistas -> obtenerTamanio(); i++){
        delete pelisNoVistas -> obtenerDato(i + 1);
    }
    delete pelisNoVistas;

    delete pelisRecomendadas;*/
}