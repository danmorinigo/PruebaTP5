#include "Grafo.h"

Grafo::Grafo(){
    primero = 0;
    ultimo = 0;
    criterioBusqueda = 0;
    tamanio = 0;
}

void Grafo::setCriterioBusqueda(int criterio){
    this->criterioBusqueda = criterio;
}

bool Grafo::caminoPorPrecio(){
    return (criterioBusqueda == 1);
}

bool Grafo::caminoPorHoras(){
    return (criterioBusqueda == 2);
}

void Grafo::agregarVertice(string nombre){
    Vertice * ingresante = new Vertice(nombre);
    if (!primero){
        primero = ingresante;
        ultimo = ingresante;
        tamanio++;
        return;
    }
    Vertice* aux = primero;
    while(aux -> obtenerProxVertice() != 0){
        aux = aux -> obtenerProxVertice();
    }
    aux -> asignarProxVertice(ingresante);
    ultimo = ingresante;
    tamanio++;
}

int Grafo::obtenerPrecio(Vertice* inicio, Vertice* destino){
    Arista* aux1 = inicio -> obtenerAristas();
    while(aux1){
        if(aux1 -> ConsultarDestino() == destino){
            return aux1 -> consultarPrecio();
        }
        aux1 = aux1 -> consultarSiguiente();
    }
    return -1;
}

double Grafo::obtenerTiempoDeVuelo(Vertice* inicio, Vertice* destino){
    Arista* aux1 = inicio -> obtenerAristas();
    while(aux1){
        if(aux1 -> ConsultarDestino() == destino){
            return aux1 -> consultarHoras();
        }
        aux1 = aux1 -> consultarSiguiente();
    }
    return -1;
}

Vertice* Grafo::obtenerPrimero(){
    return this -> primero;
}

bool Grafo::existeVertice(string nombre){
    return (obtenerVertice(nombre) != 0);
}

Vertice* Grafo::obtenerVertice(string nombre){
    Vertice* aux = primero;
    for(int i = 0; i < tamanio; i++){
        if(aux -> obtenerNombreVertice() == nombre){
            return aux;
        }
        aux = aux -> obtenerProxVertice();
    }
    return 0;
}

int Grafo::cantVertices(){
    return this -> tamanio;
}

void Grafo::agregarArista(Vertice* inicio, Vertice* destino, int precio, double horasVuelo){
    Arista* nuevaArista = new Arista(destino);
    nuevaArista -> asignarPrecio(precio);
    nuevaArista -> asignarHoras(horasVuelo);
    inicio -> agregarArista(nuevaArista);
}

bool Grafo::existeCamino(Vertice* destino){
    return (!this->obtenerEtiqueta(destino)->getAnterior().empty());
}

void Grafo::etiquetarVertices(){
    Vertice* verticeEnGrafo = this->primero;
    Etiqueta* nuevaEtiqueta;
    while(verticeEnGrafo){
        nuevaEtiqueta = new Etiqueta(verticeEnGrafo);
        this->etiquetados.push_back(nuevaEtiqueta);
        verticeEnGrafo = verticeEnGrafo->obtenerProxVertice();
    }
}

void Grafo::liberarEtiquetas(){
    Etiqueta* aux;
    while(!etiquetados.empty()){
        aux = etiquetados.front();
        this->etiquetados.pop_front();
        delete aux;
    }
}

Etiqueta* Grafo::obtenerEtiqueta(Vertice* buscado){
    list<Etiqueta*>::iterator itEtiq;
    itEtiq = this->etiquetados.begin();
    bool hecho = false;
    while(!hecho && itEtiq  != this->etiquetados.end()){
        if((*itEtiq)->getVertice() == buscado){
            return *itEtiq;
            hecho = true;
        }
        itEtiq++;
    }
    return 0;
}

list<Vertice*> Grafo::antecesoresDe(Vertice* consultado){
    return obtenerEtiqueta(consultado)->getAnterior();
}

void Grafo::evaluarVerticeDestino(Etiqueta* partida, Etiqueta* destino, int iteracion){
    int partidaAcumulaCosto = 0, costoArista, pesoTotalCosto;
    double partidaAcumulaHoras = 0.0, horasArista, pesoTotalHoras;
    if(!partida->getAnterior().empty()){
        partidaAcumulaCosto = partida->getPesoAcumulado();
        partidaAcumulaHoras = partida->getPesoDouble();
    }
    costoArista = this->obtenerPrecio(partida->getVertice(), destino->getVertice());
    horasArista = this->obtenerTiempoDeVuelo(partida->getVertice(), destino->getVertice());
    pesoTotalCosto = partidaAcumulaCosto + costoArista;
    pesoTotalHoras = partidaAcumulaHoras + horasArista;
    if(destino->getAnterior().empty()){
        destino->setPesoAcumulado(pesoTotalCosto);
        destino->setPesoDouble(pesoTotalHoras);
        destino->setIteracion(iteracion);
    }else{  //tiene peso acumulado
        int destinoAcumulaCosto = destino->getPesoAcumulado();
        double destinoAcumulaHoras = destino->getPesoDouble();
        //Si peso total (acumulado del vertice visitado + arista) menor
        //al peso acumulado del vertice destino de la arista
        if((caminoPorPrecio() && (pesoTotalCosto < destinoAcumulaCosto)) || (caminoPorHoras() && (pesoTotalHoras < destinoAcumulaHoras))){
            destino->setPesoAcumulado(pesoTotalCosto);
            destino->setPesoDouble(pesoTotalHoras);
            destino->setIteracion(iteracion);
        }
    }
}

void Grafo::verificarPesoVerticeMarcado(Vertice* visitado, Vertice* destino, int iteracion, list<Vertice*> &vistos, ColaPrioridad &cola){

    int costoVertMarcado, costoVertPrevio;
    double horasVertMarcado , horasVertPrevio;
    int costoArista = this -> obtenerPrecio(visitado, destino);
    double horasArista = this -> obtenerTiempoDeVuelo(visitado, destino);
    Etiqueta * aux;

    costoVertPrevio = obtenerEtiqueta(visitado) -> getPesoAcumulado();
    horasVertPrevio = obtenerEtiqueta(visitado) -> getPesoDouble();
    costoVertMarcado = obtenerEtiqueta(destino) -> getPesoAcumulado();
    horasVertMarcado = obtenerEtiqueta(destino) -> getPesoDouble();

    bool costoMenorEncontrado = (costoVertPrevio + costoArista < costoVertMarcado);
    bool menosHorasEncontradas = (horasVertPrevio + horasArista < horasVertMarcado);

    if((caminoPorPrecio() && costoMenorEncontrado) || (caminoPorHoras() && menosHorasEncontradas)){
        aux = obtenerEtiqueta(destino);
        aux -> setPesoAcumulado(costoVertPrevio + costoArista);
        aux -> setPesoDouble(horasVertPrevio + horasArista);
        aux -> setIteracion(iteracion);
        vistos.remove(destino);
        cola.push(destino, costoVertPrevio + costoArista, horasVertPrevio + horasArista, iteracion);
    }
}

void Grafo::caminoMinimo(Vertice* salida, Vertice* destino){
    int iteracion = 1;
    list<Vertice*> vistos;  //Aca van los vertices ya visitados (marcados)
    etiquetarVertices();
    ColaPrioridad cola(this -> criterioBusqueda);
    cola.push(salida, 0, 0.0, 0);
    while(!cola.vacia()){
        Vertice * verticeVisitado = cola.topAndPop();
        if(!fueVisitado(vistos, verticeVisitado)){
            Arista* auxAristas = verticeVisitado -> obtenerAristas();
            Etiqueta* auxActual = obtenerEtiqueta(verticeVisitado);
            while(auxAristas){
                trabajoAdyacente(auxAristas, &vistos, verticeVisitado, &cola, auxActual, iteracion);
                auxAristas = auxAristas->consultarSiguiente();
            }
            vistos.push_back(verticeVisitado);
            iteracion++;
        }
    }
    if(existeCamino(destino)){
        stack<Vertice*> pilaVertices;
        bool primerLlamado = true;
        mostrarCaminos(destino, salida, pilaVertices, primerLlamado);
    }else{
        cout <<endl<< "No existen vuelos entre el origen y el destino ingresados. \n"; 
    }
    liberarEtiquetas();
}

void Grafo::trabajoAdyacente(Arista* auxAristas, list<Vertice*> * vistos, Vertice * verticeVisitado, ColaPrioridad *cola, Etiqueta * auxActual, int iteracion) {
    Etiqueta* auxDestino = obtenerEtiqueta(auxAristas -> ConsultarDestino());
    if(!fueVisitado(*vistos, auxAristas->ConsultarDestino())){
        int aristaCosto = this->obtenerPrecio(verticeVisitado, auxAristas->ConsultarDestino());
        double aristaHoras = this->obtenerTiempoDeVuelo(verticeVisitado, auxAristas->ConsultarDestino());
        cola -> push(auxAristas->ConsultarDestino(), aristaCosto, aristaHoras, iteracion);
        //CAMBIO O NO ETIQUETA DE VERTICE DESTINO DE LA ACTUAL ARISTA???
        evaluarVerticeDestino(auxActual, auxDestino, iteracion);
    }else{//Ya fue visitado, tengo que verificar si puedo cambiar su peso acumulado.
        verificarPesoVerticeMarcado(verticeVisitado, auxAristas -> ConsultarDestino(), iteracion, *vistos, *cola);
    }
    //Agrego antecesor, hayan o no sido cambiado datos de su etiqueta
    auxDestino -> sumoAnterior(verticeVisitado);
}

int Grafo::costoAcumulado(Vertice* consultado){
    return obtenerEtiqueta(consultado)->getPesoAcumulado();
}

double Grafo::horasAcumuladas(Vertice* consultado){
    return obtenerEtiqueta(consultado)->getPesoDouble();
}

//RECORRIENDODESDE NUNCA PUEDE SER NULL
void Grafo::mostrarCaminos(Vertice* recorriendoDesde, Vertice* destino, stack<Vertice*> caminoRecorrido, bool primeraPasada){
    stack<Vertice*> PilaLocal = caminoRecorrido;//entra vacio
    if((recorriendoDesde == destino) && !primeraPasada){
        PilaLocal.push(recorriendoDesde);
        cout << "+----------------------+" << endl;
        cout << "|MOSTRANDO EL RECORRIDO|" << endl;
        cout << "+----------------------+" << endl;
        cout << endl;
        presentarPila(PilaLocal);
        return;
    }else{
        PilaLocal.push(recorriendoDesde);
        list<Vertice*> antecesores = antecesoresDe(recorriendoDesde);
        Vertice* recorriendoDesdeLocal;
        if(antecesores.size() > 1){
            while(!antecesores.empty()){
                recorriendoDesdeLocal = antecesores.front();
                antecesores.pop_front();
                int pesoAristaCosto = this->obtenerPrecio(recorriendoDesdeLocal, recorriendoDesde);
                double pesoAristaHoras = this->obtenerTiempoDeVuelo(recorriendoDesdeLocal, recorriendoDesde);
                int costoVerticeActual = costoAcumulado(recorriendoDesde);
                double horasVerticeActual = horasAcumuladas(recorriendoDesde);
                int costoBuscado = costoVerticeActual - pesoAristaCosto;
                double horasBuscadas = horasVerticeActual - pesoAristaHoras;
                if(recorriendoDesdeLocal == destino){
                    //bool conTolerancia = enTolerancia(0.0, horasBuscadas);
                    //if(((criterio == 1) && (costoBuscado == 0)) || ((criterio == 2) && conTolerancia)){
                    //Aca parece que no necesita "tolerancia", sino comentar la linea de abajo y usar las 2 de arriba
                    if((caminoPorPrecio() && (costoBuscado == 0)) || (caminoPorHoras() && (horasBuscadas == 0.0))){
                        bool primerRecorrido = false;
                        mostrarCaminos(recorriendoDesdeLocal, destino, PilaLocal, primerRecorrido);
                    }
                }else{
                    int costoVertEvaluado = costoAcumulado(recorriendoDesdeLocal);
                    double horasVertEvaluado = horasAcumuladas(recorriendoDesdeLocal);
                    bool conTolerancia = enTolerancia(horasVertEvaluado, horasBuscadas);
                    if((caminoPorPrecio() && (costoVertEvaluado == costoBuscado)) || (caminoPorHoras() && conTolerancia)){
                    //if((caminoPorPrecio() && (costoVertEvaluado == costoBuscado)) || (caminoPorHoras() && (horasVertEvaluado == horasBuscadas))){
                        bool primerRecorrido = false;
                        mostrarCaminos(recorriendoDesdeLocal, destino, PilaLocal, primerRecorrido);
                    }
                }
            }
            return;
        }else{
            recorriendoDesdeLocal = antecesores.front();
            bool primerRecorrido = false;
            mostrarCaminos(recorriendoDesdeLocal, destino, PilaLocal, primerRecorrido);
            return;
        }
    }
}

void Grafo::presentarPila(stack<Vertice*> aMostrar){
    Vertice* mostrando;
    int pesoTotal = 0, pesoAnterior = 0, pesoArista = 0;
    double pesoTotalDouble = 0, pesoAnteriorDouble = 0, pesoAristaDouble = 0;
    mostrando = aMostrar.top();
    cout << mostrando->obtenerNombreVertice();
    aMostrar.pop();
    while(!aMostrar.empty()){
        mostrando = aMostrar.top();
        switch (this -> criterioBusqueda) {
            case 1:
                pesoTotal = costoAcumulado(mostrando);
                pesoArista = pesoTotal - pesoAnterior;
                cout << "-(+" << pesoArista << ")->" << mostrando->obtenerNombreVertice();
                pesoAnterior = pesoTotal;
                break;
            case 2:
                pesoTotalDouble = horasAcumuladas(mostrando);
                pesoAristaDouble = pesoTotalDouble - pesoAnteriorDouble;
                cout <<"-(+" << pesoAristaDouble << ")->" << mostrando->obtenerNombreVertice();
                pesoAnteriorDouble = pesoTotalDouble;
                break;
        }
        aMostrar.pop();
    }
    if (caminoPorPrecio()){
        cout <<endl<<endl<< "Costo total en pesos: $" << pesoTotal << ",00" << endl;
    }else if(caminoPorHoras()){
        cout <<endl<<endl<< "Tiempo de vuelo total en horas: " << pesoTotalDouble << " hs." << endl;
    }

}

bool Grafo::enTolerancia(double valor1, double valor2){
    if(((valor1 - valor2) > -TOLERANCIA) && ((valor1 - valor2) < TOLERANCIA)){
        return true;
    }
    return false;
}

unsigned Grafo::obtenerTamanio() {
    return tamanio;
}

void Grafo::mostrarVertices(){
    cout << endl << "Listado de aeropuertos en el grafo: \n" << endl;
            Vertice* aux = this -> obtenerPrimero();
            for(int i = 0; i < this -> obtenerTamanio(); i++){
                cout << "- " << aux -> obtenerNombreVertice() << endl;
                aux = aux -> obtenerProxVertice();
            }
            cout << endl;
            cin.get();
}

bool Grafo::fueVisitado(list<Vertice*> yaVisitados, Vertice* evaluado){
    list<Vertice*>::iterator i;
    i = yaVisitados.begin();
    while(i != yaVisitados.end()){
        if(*i == evaluado){
            return true;
        }
        i++;
    }
    return false;
}

Grafo::~Grafo(){
    Vertice* aux = primero, *prev;
    Arista* auxArista;
    Arista* auxAristaBorrar;
    while(tamanio){
        auxArista = aux->obtenerAristas();
        while(auxArista){
            auxAristaBorrar = auxArista;
            auxArista = auxArista->consultarSiguiente();
            delete auxAristaBorrar;
        }
        prev = aux;
        aux = aux->obtenerProxVertice();
        delete prev;
        tamanio--;
    }
}


/*void Grafo::mostarEtiquetas(){
    list<Etiqueta*>::iterator itEtiq;
    cout << "----------------------------------------------------------------------\n";
    cout << "----------------------------------------------------------------------\n";
    for(itEtiq = this->etiquetados.begin(); itEtiq != this->etiquetados.end(); itEtiq++){
        cout << "Vertice: " << (*itEtiq)->getVertice()->obtenerNombreVertice();
        cout << " - Iteracion: " << (*itEtiq)->getIteracion() << endl;
        cout << "\tAnterior(es): ";
        if(!(*itEtiq)->getAnterior().empty()){
            cout << endl;
            list<Vertice*> auxAnteriores = (*itEtiq)->getAnterior();
            list<Vertice*>::iterator i;
            for(i = auxAnteriores.begin(); i != auxAnteriores.end(); i++){
                cout << "         " << (*i)->obtenerNombreVertice() << "<---"<< endl;
            }
        }else{
            cout << "-NO TIENE-\n";
        }
        cout << "\tCosto Acumulado: $" << (*itEtiq)->getPesoAcumulado() << endl;
        cout << "\tHoras Acumuladas: " << (*itEtiq)->getPesoDouble() << endl;;

    }
    cout << "----------------------------------------------------------------------\n";
    cout << "----------------------------------------------------------------------\n";
}

void Grafo::mostrarVerticesMarcados(list<Vertice*> vistos){
    Vertice* auxilio;
    cout << "----------------------------" << endl;
    cout << "VERTICES MARCADOS (EN ORDEN)" << endl;
    cout << "----------------------------" << endl;
    list<Vertice*>::iterator i;
    for(i = vistos.begin(); i != vistos.end(); i++){
        auxilio = *i;
        cout << auxilio->obtenerNombreVertice() << endl;
    }
}*/
