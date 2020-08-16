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

int Grafo::obtenerPeso1(Vertice* inicio, Vertice* destino){
    Arista* aux1 = inicio -> obtenerAristas();
    while(aux1){
        if(aux1 -> ConsultarDestino() == destino){
            return aux1 -> cunsultarPrecio();
        }
        aux1 = aux1 -> consultarSiguiente();
    }
    return -1;
}

double Grafo::obtenerPeso2(Vertice* inicio, Vertice* destino){
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

/*
bool Grafo::existeCamino(list<Etiqueta*> etiquetados, Vertice* destino){
    return (!this->obtenerEtiqueta(destino, etiquetados)->getAnterior().empty());
}
*/
void Grafo::mostarEtiquetas(){
    list<Etiqueta*>::iterator itEtiq;
    cout << "---------------------------------------------------------------\n";
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
    cout << "---------------------------------------------------------------\n";
}
/*
void Grafo::mostarEtiquetas(list<Etiqueta*> etiquetados){
    list<Etiqueta*>::iterator itEtiq;
    cout << "---------------------------------------------------------------\n";
    for(itEtiq = etiquetados.begin(); itEtiq != etiquetados.end(); itEtiq++){
        cout << "Vertice: " << (*itEtiq)->getVertice()->obtenerNombreVertice() << endl;
        cout << "\tAnterior(es):\n";
        if(!(*itEtiq)->getAnterior().empty()){
            list<Vertice*> auxAnteriores = (*itEtiq)->getAnterior();
            list<Vertice*>::iterator i;
            for(i = auxAnteriores.begin(); i != auxAnteriores.end(); i++){
                cout << "\t\t" << (*i)->obtenerNombreVertice() << endl;
            }
        }else{
            cout << "\t\t-NO TIENE-\n";
        }
        cout << "\tCosto Acumulado: $" << (*itEtiq)->getPesoAcumulado() << endl;
        cout << "\tHoras Acumuladas: " << (*itEtiq)->getPesoDouble() << endl;;
        cout << "\tIteracion: " << (*itEtiq)->getIteracion() << endl;
    }
    cout << "---------------------------------------------------------------\n";
}
*/
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
/*
void Grafo::etiquetarVertices(list<Etiqueta*> &etiquetados){
    Vertice* verticeEnGrafo = this->primero;
    Etiqueta* nuevaEtiqueta;
    while(verticeEnGrafo){
        nuevaEtiqueta = new Etiqueta(verticeEnGrafo);
        etiquetados.push_back(nuevaEtiqueta);
        verticeEnGrafo = verticeEnGrafo->obtenerProxVertice();
    }
}
*/
void Grafo::liberarEtiquetas(){
    Etiqueta* aux;
    while(!etiquetados.empty()){
        aux = etiquetados.front();
        this->etiquetados.pop_front();
        delete aux;
    }
}
/*
void Grafo::liberarEtiquetas(list<Etiqueta*> etiquetados){
    Etiqueta* aux;
    while(!etiquetados.empty()){
        aux = etiquetados.front();
        etiquetados.pop_front();
        delete aux;
    }
}
*/
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
/*
Etiqueta* Grafo::obtenerEtiqueta(Vertice* buscado, list<Etiqueta*> etiquetados){
    list<Etiqueta*>::iterator itEtiq;
    itEtiq = etiquetados.begin();
    bool hecho = false;
    while(!hecho && itEtiq  != etiquetados.end()){
        if((*itEtiq)->getVertice() == buscado){
            return *itEtiq;
            hecho = true;
        }
        itEtiq++;
    }
    return 0;
}
*/
list<Vertice*> Grafo::antecesoresDe(Vertice* consultado){
    return obtenerEtiqueta(consultado)->getAnterior();
}
/*
list<Vertice*> Grafo::antecesoresDe(Vertice* consultado, list<Etiqueta*> etiquetados){
    return obtenerEtiqueta(consultado, etiquetados)->getAnterior();
}
*/
void Grafo::evaluarVerticeDestino(Etiqueta* partida, Etiqueta* destino, int iteracion){
    int partidaAcumulaCosto = 0, costoArista, pesoTotalCosto;
    double partidaAcumulaHoras = 0.0, horasArista, pesoTotalHoras;
    if(!partida->getAnterior().empty()){
        partidaAcumulaCosto = partida->getPesoAcumulado();
        partidaAcumulaHoras = partida->getPesoDouble();
    }
    costoArista = this->obtenerPeso1(partida->getVertice(), destino->getVertice());
    horasArista = this->obtenerPeso2(partida->getVertice(), destino->getVertice());
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
//void Grafo::verificarPesoVerticeMarcado(Vertice* visitado, Vertice* destino, list<Etiqueta*> etiquetados, int iteracion, list<Vertice*> &vistos, ColaPrioridad &cola){

    int costoVertMarcado, costoVertPrevio;
    double horasVertMarcado , horasVertPrevio;
    int costoArista = this -> obtenerPeso1(visitado, destino);
    double horasArista = this -> obtenerPeso2(visitado, destino);
    Etiqueta * aux;

    costoVertPrevio = obtenerEtiqueta(visitado) -> getPesoAcumulado();
    horasVertPrevio = obtenerEtiqueta(visitado) -> getPesoDouble();
    costoVertMarcado = obtenerEtiqueta(destino) -> getPesoAcumulado();
    horasVertMarcado = obtenerEtiqueta(destino) -> getPesoDouble();
    /*
    costoVertPrevio = obtenerEtiqueta(visitado, etiquetados) -> getPesoAcumulado();
    horasVertPrevio = obtenerEtiqueta(visitado, etiquetados) -> getPesoDouble();
    costoVertMarcado = obtenerEtiqueta(destino, etiquetados) -> getPesoAcumulado();
    horasVertMarcado = obtenerEtiqueta(destino, etiquetados) -> getPesoDouble();
    //horasVertMarcado = obtenerEtiqueta(visitado, etiquetados) -> getPesoDouble();
    */
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
    //list<Etiqueta*> etiquetados;
    etiquetarVertices();
    //etiquetarVertices(etiquetados);
    ColaPrioridad cola(this->criterioBusqueda);
    cola.push(salida, 0, 0.0, 0);
    while(!cola.vacia()){
        Vertice * verticeVisitado = cola.topAndPop();
        if(!fueVisitado(vistos, verticeVisitado)){
            Arista* auxAristas = verticeVisitado -> obtenerAristas();
            Etiqueta* auxActual = obtenerEtiqueta(verticeVisitado);
            //Etiqueta* auxActual = obtenerEtiqueta(verticeVisitado, etiquetados);
            while(auxAristas){
                Etiqueta* auxDestino = obtenerEtiqueta(auxAristas -> ConsultarDestino());
                //Etiqueta* auxDestino = obtenerEtiqueta(auxAristas -> ConsultarDestino(), etiquetados);
                if(!fueVisitado(vistos, auxAristas->ConsultarDestino())){
                    int aristaCosto = this->obtenerPeso1(verticeVisitado, auxAristas->ConsultarDestino());
                    double aristaHoras = this->obtenerPeso2(verticeVisitado, auxAristas->ConsultarDestino());
                    cola.push(auxAristas->ConsultarDestino(), aristaCosto, aristaHoras, iteracion);
                    //CAMBIO O NO ETIQUETA DE VERTICE DESTINO DE LA ACTUAL ARISTA???
                    evaluarVerticeDestino(auxActual, auxDestino, iteracion);
                }else{//Ya fue visitado, tengo que verificar si puedo cambiar su peso acumulado.
                    verificarPesoVerticeMarcado(verticeVisitado, auxAristas -> ConsultarDestino(), iteracion, vistos, cola);
                }
                //Agrego antecesor, hayan o no sido cambiado datos de su etiqueta
                auxDestino->sumoAnterior(verticeVisitado);
                auxAristas = auxAristas->consultarSiguiente();
            }
            vistos.push_back(verticeVisitado);
            iteracion++;
        }
    }
    //mostrarVerticesMarcados(vistos);
    if(existeCamino(destino)){
    //if(existeCamino(etiquetados, destino)){
        cout << "ETIQUETADO FINAL" << endl;
        mostarEtiquetas();
        //mostarEtiquetas(etiquetados);
        Vertice* inicioRecorrido = destino; //comienza desde el final
        stack<TuplaCompleta> pilaTuplas;
        stack<Vertice*> pilaVertices;
        bool primerLlamado = true;
        mostrarCaminos(destino, salida, pilaVertices, primerLlamado);
        //mostrarCaminos(etiquetados, destino, salida, pilaVertices, primerLlamado);
        //mostrarVer3(etiquetados, inicioRecorrido, salida, pilaTuplas, primerLlamado);
    }else{
        cout << "No hay conexion\n";
    }
    liberarEtiquetas();
}

int Grafo::costoAcumulado(Vertice* consultado){
    return obtenerEtiqueta(consultado)->getPesoAcumulado();
}

double Grafo::horasAcumuladas(Vertice* consultado){
    return obtenerEtiqueta(consultado)->getPesoDouble();
}
/*
int Grafo::costoAcumulado(Vertice* consultado, list<Etiqueta*> etiquetados){
    return obtenerEtiqueta(consultado, etiquetados)->getPesoAcumulado();
}

double Grafo::horasAcumuladas(Vertice* consultado, list<Etiqueta*> etiquetados){
    return obtenerEtiqueta(consultado, etiquetados)->getPesoDouble();
}
*/

//RECORRIENDODESDE NUNCA PUEDE SER NULL
void Grafo::mostrarCaminos(Vertice* recorriendoDesde, Vertice* destino, stack<Vertice*> caminoRecorrido, bool primeraPasada){
//void Grafo::mostrarCaminos(list<Etiqueta*> etiquetados, Vertice* recorriendoDesde, Vertice* destino, stack<Vertice*> caminoRecorrido, bool primeraPasada){
    stack<Vertice*> PilaLocal = caminoRecorrido;//entra vacio
    if((recorriendoDesde == destino) && !primeraPasada){
        PilaLocal.push(recorriendoDesde);
        cout << "+----------------------+" << endl;
        cout << "|MOSTRANDO EL RECORRIDO|" << endl;
        cout << "+----------------------+" << endl;
        cout << endl;
        presentarPila(PilaLocal);
        //presentarPila(PilaLocal, etiquetados);
        return;
    }else{
        PilaLocal.push(recorriendoDesde);
        list<Vertice*> antecesores = antecesoresDe(recorriendoDesde);
        //list<Vertice*> antecesores = antecesoresDe(recorriendoDesde, etiquetados);
        Vertice* recorriendoDesdeLocal;
        if(antecesores.size() > 1){
            while(!antecesores.empty()){
                recorriendoDesdeLocal = antecesores.front();
                antecesores.pop_front();
                int pesoAristaCosto = this->obtenerPeso1(recorriendoDesdeLocal, recorriendoDesde);
                double pesoAristaHoras = this->obtenerPeso2(recorriendoDesdeLocal, recorriendoDesde);
                int costoVerticeActual = costoAcumulado(recorriendoDesde);
                double horasVerticeActual = horasAcumuladas(recorriendoDesde);
                //int costoVerticeActual = costoAcumulado(recorriendoDesde, etiquetados);
                //double horasVerticeActual = horasAcumuladas(recorriendoDesde, etiquetados);
                int costoBuscado = costoVerticeActual - pesoAristaCosto;
                double horasBuscadas = horasVerticeActual - pesoAristaHoras;
                if(recorriendoDesdeLocal == destino){
                    //bool conTolerancia = enTolerancia(0.0, horasBuscadas);
                    //if(((criterio == 1) && (costoBuscado == 0)) || ((criterio == 2) && conTolerancia)){
                    //Aca parece que no necesita "tolerancia", sino comentar la linea de abajo y usar las 2 de arriba
                    if((caminoPorPrecio() && (costoBuscado == 0)) || (caminoPorHoras() && (horasBuscadas == 0.0))){
                        bool primerRecorrido = false;
                        mostrarCaminos(recorriendoDesdeLocal, destino, PilaLocal, primerRecorrido);
                        //mostrarCaminos(etiquetados, recorriendoDesdeLocal, destino, PilaLocal, primerRecorrido);
                    }
                }else{
                    int costoVertEvaluado = costoAcumulado(recorriendoDesdeLocal);
                    double horasVertEvaluado = horasAcumuladas(recorriendoDesdeLocal);
                    //int costoVertEvaluado = costoAcumulado(recorriendoDesdeLocal, etiquetados);
                    //double horasVertEvaluado = horasAcumuladas(recorriendoDesdeLocal, etiquetados);
                    bool conTolerancia = enTolerancia(horasVertEvaluado, horasBuscadas);
                    if((caminoPorPrecio() && (costoVertEvaluado == costoBuscado)) || (caminoPorHoras() && conTolerancia)){
                    //if((caminoPorPrecio() && (costoVertEvaluado == costoBuscado)) || (caminoPorHoras() && (horasVertEvaluado == horasBuscadas))){
                        bool primerRecorrido = false;
                        mostrarCaminos(recorriendoDesdeLocal, destino, PilaLocal, primerRecorrido);
                        //mostrarCaminos(etiquetados, recorriendoDesdeLocal, destino, PilaLocal, primerRecorrido);
                    }
                }
            }
            return;
        }else{
            recorriendoDesdeLocal = antecesores.front();
            bool primerRecorrido = false;
            mostrarCaminos(recorriendoDesdeLocal, destino, PilaLocal, primerRecorrido);
            //mostrarCaminos(etiquetados, recorriendoDesdeLocal, destino, PilaLocal, primerRecorrido);
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
        /*
        if (caminoPorPrecio()){
            pesoTotal = costoAcumulado(mostrando);
            pesoArista = pesoTotal - pesoAnterior;
            cout << "-(+" << pesoArista << ")->" << mostrando->obtenerNombreVertice();
            pesoAnterior = pesoTotal;
        }else if(caminoPorHoras()){
            pesoTotalDouble = horasAcumuladas(mostrando);
            pesoAristaDouble = pesoTotalDouble - pesoAnteriorDouble;
            cout <<"-(+" << pesoAristaDouble << ")->" << mostrando->obtenerNombreVertice();
            pesoAnteriorDouble = pesoTotalDouble;
        }
        */
        switch (this->criterioBusqueda) {
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
        cout <<endl<<endl<< "Costo total en horas: " << pesoTotalDouble << " hs." << endl;
    }

}
/*
void Grafo::presentarPila(stack<Vertice*> aMostrar, list<Etiqueta*> etiquetados){
    Vertice* mostrando;
    int pesoTotal = 0, pesoAnterior = 0, pesoArista = 0;
    double pesoTotalDouble = 0, pesoAnteriorDouble = 0, pesoAristaDouble = 0;
    mostrando = aMostrar.top();
    cout << mostrando->obtenerNombreVertice();
    aMostrar.pop();
    while(!aMostrar.empty()){
        mostrando = aMostrar.top();

        if (caminoPorPrecio()){
            pesoTotal = costoAcumulado(mostrando);
            pesoArista = pesoTotal - pesoAnterior;
            cout << "-(+" << pesoArista << ")->" << mostrando->obtenerNombreVertice();
            pesoAnterior = pesoTotal;
        }else if(caminoPorHoras()){
            pesoTotalDouble = horasAcumuladas(mostrando);
            pesoAristaDouble = pesoTotalDouble - pesoAnteriorDouble;
            cout <<"-(+" << pesoAristaDouble << ")->" << mostrando->obtenerNombreVertice();
            pesoAnteriorDouble = pesoTotalDouble;
        }

        switch (this->criterioBusqueda) {
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
        cout <<endl<<endl<< "Costo total en horas: " << pesoTotalDouble << " hs." << endl;
    }

}
*/
void Grafo::mostrarVer3(list<Etiqueta*> etiquetados, Vertice* recorriendoDesde, Vertice* destino, stack<TuplaCompleta> caminoRecorrido, bool primeraPasada){

    stack<TuplaCompleta> PilaLocal = caminoRecorrido;//entra vacio
    TuplaCompleta tuplaLocal;
    Vertice* aux;

    if(recorriendoDesde){
        tuplaLocal.vertice = recorriendoDesde;
        aux = recorriendoDesde;
        list<Etiqueta*>::iterator i;
        i = etiquetados.begin();
        bool encontrado = false;
        while(!encontrado && i != etiquetados.end()){
            if((*i)->getVertice() == aux){
                tuplaLocal.pesoAcumulado = (*i)->getPesoAcumulado();
                tuplaLocal.pesoDouble = (*i)->getPesoDouble();
                encontrado = true;
            }
            i++;
        }
        if((recorriendoDesde == destino) && !primeraPasada){
            PilaLocal.push(tuplaLocal);
            cout << "+----------------------+" << endl;
            cout << "|MOSTRANDO EL RECORRIDO|" << endl;
            cout << "+----------------------+" << endl;
            cout << endl;
            mostrarPila(PilaLocal);
            return;
        }else{
            PilaLocal.push(tuplaLocal);
            list<Vertice*> antecesores;
            i = etiquetados.begin();
            bool encontrado = false;
            while(!encontrado && i != etiquetados.end()){
                if((*i)->getVertice() == recorriendoDesde){
                    antecesores = (*i)->getAnterior();
                    encontrado = true;
                }
                i++;
            }
            Vertice* recorriendoDesdeLocal;
            if(antecesores.size() > 1){
                while(!antecesores.empty()){
                    recorriendoDesdeLocal = antecesores.front();
                    antecesores.pop_front();
                    int pesoAristaCosto = this->obtenerPeso1(recorriendoDesdeLocal, recorriendoDesde);
                    double pesoAristaHoras = this->obtenerPeso2(recorriendoDesdeLocal, recorriendoDesde);
                    int costoVerticeActual = tuplaLocal.pesoAcumulado;
                    double horasVerticeActual = tuplaLocal.pesoDouble;
                    int costoBuscado = costoVerticeActual - pesoAristaCosto;
                    double horasBuscadas = horasVerticeActual - pesoAristaHoras;
                    if(recorriendoDesdeLocal == destino){
                        //bool conTolerancia = enTolerancia(0.0, horasBuscadas);
                        //if(((criterio == 1) && (costoBuscado == 0)) || ((criterio == 2) && conTolerancia)){
                        //Aca parece que no necesita "tolerancia", sino comentar la linea de abajo y usar las 2 de arriba
                        if((caminoPorPrecio() && (costoBuscado == 0)) || (caminoPorHoras() && (horasBuscadas == 0.0))){
                            bool primerRecorrido = false;
                            mostrarVer3(etiquetados, recorriendoDesdeLocal, destino, PilaLocal, primerRecorrido);
                        }
                    }else{
                        int costoVertEvaluado = 0;
                        double horasVertEvaluado = 0.0;
                        list<Etiqueta*>::iterator i;
                        i = etiquetados.begin();
                        bool hecho = false;
                        while(!hecho && i != etiquetados.end()){
                            if((*i)->getVertice() == recorriendoDesdeLocal){
                                costoVertEvaluado = (*i)->getPesoAcumulado();
                                horasVertEvaluado = (*i)->getPesoDouble();
                                hecho = true;
                            }
                            i++;
                        }
                        bool conTolerancia = enTolerancia(horasVertEvaluado, horasBuscadas);
                        if((caminoPorPrecio() && (costoVertEvaluado == costoBuscado)) || (caminoPorHoras() && conTolerancia)){
                        //if(((criterio == 1) && (costoVertEvaluado == costoBuscado)) || ((criterio == 2) && (horasVertEvaluado == horasBuscadas))){
                            bool primerRecorrido = false;
                            mostrarVer3(etiquetados, recorriendoDesdeLocal, destino, PilaLocal, primerRecorrido);
                        }
                    }
                }
                return;
            }else{
                recorriendoDesdeLocal = antecesores.front();
                bool primerRecorrido = false;
                mostrarVer3(etiquetados, recorriendoDesdeLocal, destino, PilaLocal, primerRecorrido);
                return;
            }
        }
    }else{
        cout << "-------------------------------------" << endl;
        cout << "        ERROR - ERROR - ERROR!" << endl;
        cout << "(ARMANDO PILA PARA MOSTRAR RECORRIDO)" << endl;
        cout << "-------------------------------------" << endl;
        return;
    }
}

bool Grafo::enTolerancia(double valor1, double valor2){
    if(((valor1 - valor2) > -TOLERANCIA) && ((valor1 - valor2) < TOLERANCIA)){
        return true;
    }
    return false;
}

//Pila debe estar cargada!!
void Grafo::mostrarPila(stack<TuplaCompleta> aMostrar){
    TuplaCompleta mostrando;
    int pesoTotal = 0, pesoAnterior = 0, pesoArista = 0;
    double pesoTotalDouble = 0, pesoAnteriorDouble = 0, pesoAristaDouble = 0;
    mostrando = aMostrar.top();
    cout << (mostrando.vertice) -> obtenerNombreVertice();
    aMostrar.pop();
    while(!aMostrar.empty()){
        mostrando = aMostrar.top();
        if (caminoPorPrecio()){
            pesoTotal = mostrando.pesoAcumulado;
            pesoArista = pesoTotal - pesoAnterior;
            cout << "-(+" << pesoArista << ")->" << (mostrando.vertice)->obtenerNombreVertice();
            pesoAnterior = pesoTotal;
        }else if(caminoPorHoras()){
            pesoTotalDouble = mostrando.pesoDouble;
            pesoAristaDouble = pesoTotalDouble - pesoAnteriorDouble;
            cout <<"-(+" << pesoAristaDouble << ")->" << (mostrando.vertice)->obtenerNombreVertice();
            pesoAnteriorDouble = pesoTotalDouble;
        }
        /*
        switch (this->criterioBusqueda) {
            case 1:
                pesoTotal = mostrando.pesoAcumulado;
                pesoArista = pesoTotal - pesoAnterior;
                cout << "-(+" << pesoArista << ")->" << (mostrando.vertice)->obtenerNombreVertice();
                pesoAnterior = pesoTotal;
                break;
            case 2:
                pesoTotalDouble = mostrando.pesoDouble;
                pesoAristaDouble = pesoTotalDouble - pesoAnteriorDouble;
                cout <<"-(+" << pesoAristaDouble << ")->" << (mostrando.vertice)->obtenerNombreVertice();
                pesoAnteriorDouble = pesoTotalDouble;
                break;
        }
        */
        aMostrar.pop();
    }
    if (caminoPorPrecio()){
        cout <<endl<<endl<< "Costo total en pesos: $" << pesoTotal << ",00" << endl;
    }else if(caminoPorHoras()){
        cout <<endl<<endl<< "Costo total en horas: " << pesoTotalDouble << " hs." << endl;
    }

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
//bool Grafo::marcadoComoVisitado(list<Vertice*> yaVisitados, Vertice* evaluado){
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
