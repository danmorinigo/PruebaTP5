#include "Grafo.h"

Grafo::Grafo(){
    primero = 0;
    ultimo = 0;
    tamanio = 0;
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
//vERIFICAR ANTES QUE EXISTAN VERTICES!
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
//vERIFICAR ANTES QUE EXISTAN VERTICES!
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
//vERIFICAR ANTES QUE EXISTAN VERTICES!
void Grafo::agregarArista(Vertice* inicio, Vertice* destino, int precio, double horasVuelo){
    Arista* nuevaArista = new Arista(destino);
    nuevaArista -> asignarPrecio(precio);
    nuevaArista -> asignarHoras(horasVuelo);
    inicio -> agregarArista(nuevaArista);
}

bool Grafo::existeCamino(list<Etiqueta> etiquetados, Vertice* destino){
    list<Etiqueta>::iterator itEtiq;
    itEtiq = etiquetados.begin();
    bool hayCamino = false;
    bool encontreDestino = false;
    list<Vertice*> comienzoDelCamino;
    while(!encontreDestino && itEtiq != etiquetados.end()){
        if((*itEtiq).getVertice() == destino ){
            if (!(*itEtiq).getAnterior().empty()){
                hayCamino = true;
            }
            encontreDestino = true;
        }
        itEtiq++;
    }
    return hayCamino;
}
void Grafo::mostarEtiquetas(list<Etiqueta> etiquetados){
    list<Etiqueta>::iterator itEtiq;
    //itEtiq = etiquetados.begin();
    for(itEtiq = etiquetados.begin(); itEtiq != etiquetados.end(); itEtiq++){
        cout << "Estacion: "<< (*itEtiq).getVertice()->obtenerNombreVertice();
        cout << " Anterior(es): ";

        if(!(*itEtiq).getAnterior().empty()){
            list<Vertice*> auxVerticesAnteriores = (*itEtiq).getAnterior();
            list<Vertice*>::iterator i;
            for(i = auxVerticesAnteriores.begin(); i != auxVerticesAnteriores.end(); i++){
                cout << (*i)->obtenerNombreVertice() << "-";
            }
        }else{
            cout << "NO";
        }
        cout << " Acumulado: " << (*itEtiq).getPesoAcumulado();
        cout << " Double: " << (*itEtiq).getPesoDouble();
        cout << " It: " << (*itEtiq).getIteracion() << endl;
    }
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
}
//deben estar verificadas las existencias de ambos vertices
//precioUhorasVuelo -> 1-precio, 2-horas
void Grafo::caminoMinimo(Vertice* salida, Vertice* destino, int precioUhorasVuelo){

    int modo = precioUhorasVuelo; //1 para INT, 2 para DOUble
    int iteracion = 1;

    ColaPrioridad cola(modo);
    cola.push(salida, 0, 0.0, iteracion);

    list<Vertice*> vistos;  //Aca van los vertices ya visitados (marcados)

    list<Etiqueta> etiquetados;
    list<Etiqueta>::iterator itEtiq;    //Iterador lo uso en todo lo que sigue

    //------------------------------------------------------
    //VA EN METODO CREAR_ETIQUETADOS
    Vertice* verticeEnGrafo = this->primero;
    while(verticeEnGrafo){
        Etiqueta ingresante(verticeEnGrafo);
        etiquetados.push_back(ingresante);
        verticeEnGrafo = verticeEnGrafo->obtenerProxVertice();
    }//------------------------------------------------------

    Vertice* verticeVisitado;
    //Unico vertice en la cola, al entrar, es el vertice de partida
    while(!cola.vacia()){
        verticeVisitado = cola.topAndPop();
        bool fueVisitadoAntes = marcadoComoVisitado(vistos, verticeVisitado);
        Arista* auxAristas;
        if(!fueVisitadoAntes){
            auxAristas = verticeVisitado -> obtenerAristas();
            while(auxAristas){
                bool fueVisitadoAntes = marcadoComoVisitado(vistos, auxAristas->ConsultarDestino());
                if(!fueVisitadoAntes){
                    int pesoEntero = this -> obtenerPeso1(verticeVisitado, auxAristas->ConsultarDestino());
                    double pesoDouble = this -> obtenerPeso2(verticeVisitado, auxAristas->ConsultarDestino());
                    cola.push(auxAristas->ConsultarDestino(), pesoEntero, pesoDouble, iteracion);

                    //Dos etiquetas auxiliares, uno apuntando al vertice visitado
                    //el otro apuntando al vertice destino de la arista
                    Etiqueta auxActual(verticeVisitado), auxDestino(auxAristas -> ConsultarDestino());
                    //Busco etiquetas correspondientes y copio sus datos
                    itEtiq = etiquetados.begin();
                    int losDos = 0;
                    while(losDos != 2){
                        if((*itEtiq).getVertice() == verticeVisitado){
                            auxActual = *itEtiq;
                            losDos++;
                        }
                        if((*itEtiq).getVertice() == auxAristas -> ConsultarDestino()){
                            auxDestino = *itEtiq;
                            losDos++;
                        }
                        itEtiq++;
                    }
                    //CAMBIO O NO ETIQUETA DE VERTICES DESTINO DE LA ACTUAL ARISTA???
                    //---------------------------------------------------------------
                    int miPeso = 0, pesoArista, pesoTotal;
                    double miPesoDouble = 0, pesoAristaDouble, pesoTotalDouble;
                    //******************************
                    if(!auxActual.getAnterior().empty()){
                        miPeso = auxActual.getPesoAcumulado();
                        miPesoDouble = auxActual.getPesoDouble();
                    }
                    pesoAristaDouble = this -> obtenerPeso2(verticeVisitado, auxDestino.getVertice());
                    pesoArista = this -> obtenerPeso1(verticeVisitado, auxDestino.getVertice());
                    pesoTotal = miPeso + pesoArista;
                    pesoTotalDouble = miPesoDouble + pesoAristaDouble;
                    if(auxDestino.getAnterior().empty()){   //Si no tiene predecesor tiene peso INFINITO
                                                            //Asigno anterior a el vertice que
                                                            //estoy visitando, peso = al peso
                                                            //del vertice que estoy visitando+peso
                                                            //de la arista
                        auxDestino.setPesoAcumulado(pesoTotal);
                        auxDestino.setPesoDouble(pesoTotalDouble);
                        auxDestino.setIteracion(iteracion);
                    }else{  //tiene peso acumulado
                        int suPeso;
                        double suPesoDouble;
                        suPeso = auxDestino.getPesoAcumulado();
                        suPesoDouble = auxDestino.getPesoDouble();
                        //Si peso total (acumulado del vertice visitado + arista) menor
                        //al peso acumulado del vertice destino de la arista
                        if(((modo == 1) && (pesoTotal < suPeso)) || ((modo == 2) && (pesoTotalDouble < suPesoDouble))){
                            auxDestino.setPesoAcumulado(pesoTotal);
                            auxDestino.setPesoDouble(pesoTotalDouble);
                            auxDestino.setIteracion(iteracion);
                        }else if(((modo == 1) && (pesoTotal == suPeso)) || ((modo == 2) && (pesoTotalDouble == suPesoDouble))){  //Si es igual, agrego un nuevo anterior
                                                        //y cambio iteracion
                            auxDestino.setIteracion(iteracion);
                        }
                    }
                    //----------------------------
                    //Reeplazo datos del vertice destino en la lista de etiquetas
                    itEtiq = etiquetados.begin();
                    bool hecho = false;
                    while(!hecho){
                        if((*itEtiq).getVertice() == auxDestino.getVertice()){
                            *itEtiq = auxDestino;
                            hecho = true;
                        }
                        itEtiq++;
                    }
                    //----------------------------
                }else{//Ya fue visitado, tengo que verificar si puedo cambiar su peso acumulado.
                    verificarPesoVerticeMarcado(verticeVisitado, auxAristas->ConsultarDestino(), etiquetados, modo, iteracion, vistos, cola);
                }
                //Aca se agrega un antecesor hayan o no sido cambiado datos de su etiqueta
                itEtiq = etiquetados.begin();
                bool agregado = false;
                while(!agregado && itEtiq != etiquetados.end()){
                    if((*itEtiq).getVertice() == auxAristas->ConsultarDestino()){
                        (*itEtiq).sumoAnterior(verticeVisitado);
                        agregado = true;
                    }
                    itEtiq++;
                }
                if (!agregado){
                    cout << "Error queriendo agregar padre" << endl;
                    cin.get();
                }
                auxAristas = auxAristas->consultarSiguiente();
            }
            vistos.push_back(verticeVisitado);
            iteracion++;
        }
    }
    //Solo muestro el orden en que fueron recorridos los vertices
    //mostrarVerticesMarcados(vistos);
    bool hayCamino = existeCamino(etiquetados, destino);
    if(hayCamino){
        /*
        cout << "----------------" << endl;
        cout << "ETIQUETADO FINAL" << endl;
        cout << "----------------" << endl;
        mostarEtiquetas(etiquetados);
        */
        Vertice* inicioRecorrido = destino; //comienza desde el final
        stack<TuplaCompleta> pilaTuplas;
        bool primerLlamado = true;
        mostrarVer3(etiquetados, inicioRecorrido, salida, pilaTuplas, primerLlamado, modo);
    }else{
        cout << "No hay conexion\n";
    }
}

void Grafo::mostrarVer3(list<Etiqueta> etiquetados, Vertice* recorriendoDesde, Vertice* destino, stack<TuplaCompleta> caminoRecorrido, bool primeraPasada, int criterio){
    stack<TuplaCompleta> PilaLocal = caminoRecorrido;//entra vacio

    TuplaCompleta tuplaLocal;
    Vertice* aux;

    if(recorriendoDesde){
        tuplaLocal.vertice = recorriendoDesde;
        aux = recorriendoDesde;
        list<Etiqueta>::iterator i;
        i = etiquetados.begin();
        bool encontrado = false;
        while(!encontrado && i != etiquetados.end()){
            if((*i).getVertice() == aux){
                tuplaLocal.pesoAcumulado = (*i).getPesoAcumulado();
                tuplaLocal.pesoDouble = (*i).getPesoDouble();
                encontrado = true;
            }
            i++;
        }

        if((recorriendoDesde == destino) && !primeraPasada){
            PilaLocal.push(tuplaLocal);
            cout << "+-------------------------+" << endl;
            cout << "|MOSTRANDO EL RECORRIDO|" << endl;
            cout << "+-------------------------+" << endl;
            cout << endl;
            mostrarPila(PilaLocal, criterio);
            return;
        }else{
            PilaLocal.push(tuplaLocal);
            list<Vertice*> antecesores;
            i = etiquetados.begin();
            bool encontrado = false;
            while(!encontrado && i != etiquetados.end()){
                if((*i).getVertice() == recorriendoDesde){
                    antecesores = (*i).getAnterior();
                    encontrado = true;
                }
                i++;
            }
            Vertice* recorriendoDesdeLocal;
            if(antecesores.size() > 1){
                while(!antecesores.empty()){
                    recorriendoDesdeLocal = antecesores.front();
                    antecesores.pop_front();
                    if(recorriendoDesdeLocal == destino){
                        int pesoEntero = this->obtenerPeso1(recorriendoDesdeLocal, recorriendoDesde);
                        double pesoDouble = this->obtenerPeso2(recorriendoDesdeLocal, recorriendoDesde);
                        int pesoQueTraiaElOtro = tuplaLocal.pesoAcumulado;
                        double pesoQueTraiaDouble = tuplaLocal.pesoDouble;
                        int anteriorDebeAcumular = pesoQueTraiaElOtro - pesoEntero;
                        double anteriorDebeDouble = pesoQueTraiaDouble - pesoDouble;
                        int anteriorAcumula = 0;
                        double anteriorAcumulaDouble = 0;

                        double tolerancia = 0.00001;
                        bool conTolerancia = (((anteriorAcumulaDouble - anteriorDebeDouble) > -tolerancia) && ((anteriorAcumulaDouble - anteriorDebeDouble) < tolerancia));
                        if(((criterio == 1) && (anteriorAcumula == anteriorDebeAcumular)) || ((criterio == 2) && conTolerancia)){
                        //if(((criterio == 1) && (anteriorAcumula == anteriorDebeAcumular)) || ((criterio == 2) && (anteriorAcumulaDouble == anteriorDebeDouble))){
                            bool primerRecorrido = false;
                            mostrarVer3(etiquetados, recorriendoDesdeLocal, destino, PilaLocal, primerRecorrido, criterio);
                        }
                    }else{
                        int pesoEntero = this->obtenerPeso1(recorriendoDesdeLocal, recorriendoDesde);
                        double pesoDouble = this->obtenerPeso2(recorriendoDesdeLocal, recorriendoDesde);
                        int pesoQueTraiaElOtro = tuplaLocal.pesoAcumulado;
                        double pesoQueTraiaDouble = tuplaLocal.pesoDouble;
                        int anteriorDebeAcumular = pesoQueTraiaElOtro - pesoEntero;
                        double anteriorDebeDouble = pesoQueTraiaDouble - pesoDouble;
                        int anteriorAcumula = 0;
                        double anteriorAcumulaDouble = 0.0;
                        list<Etiqueta>::iterator i;
                        i = etiquetados.begin();
                        bool hecho = false;
                        while(!hecho && i != etiquetados.end()){
                            if((*i).getVertice() == recorriendoDesdeLocal){
                                anteriorAcumula = (*i).getPesoAcumulado();
                                anteriorAcumulaDouble = (double)(*i).getPesoDouble();
                                hecho = true;
                            }
                            i++;
                        }
                        double tolerancia = 0.00001;
                        bool conTolerancia = (((anteriorAcumulaDouble - anteriorDebeDouble) > -tolerancia) && ((anteriorAcumulaDouble - anteriorDebeDouble) < tolerancia));
                        if(((criterio == 1) && (anteriorAcumula == anteriorDebeAcumular)) || ((criterio == 2) && conTolerancia)){
                        //if(((criterio == 1) && (anteriorAcumula == anteriorDebeAcumular)) || ((criterio == 2) && (anteriorAcumulaDouble == anteriorDebeDouble))){
                            bool primerRecorrido = false;
                            mostrarVer3(etiquetados, recorriendoDesdeLocal, destino, PilaLocal, primerRecorrido, criterio);
                        }
                    }
                }
                return;
            }else{
                recorriendoDesdeLocal = antecesores.front();
                bool primerRecorrido = false;
                mostrarVer3(etiquetados, recorriendoDesdeLocal, destino, PilaLocal, primerRecorrido, criterio);
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

void Grafo::mostrarPila(stack<TuplaCompleta> aMostrar, int criterio){
    TuplaCompleta mostrando;
    int pesoTotal = 0, pesoAnterior = 0, pesoArista = 0;
    double pesoTotalDouble = 0, pesoAnteriorDouble = 0, pesoAristaDouble = 0;
    bool primerVertice = true;
    while(!aMostrar.empty()){
        mostrando = aMostrar.top();
        if(primerVertice){
            cout << (mostrando.vertice)->obtenerNombreVertice();
            primerVertice = false;
        }else{
            if (criterio == 1){
                pesoTotal = mostrando.pesoAcumulado;
                pesoArista = pesoTotal - pesoAnterior;
                cout << "-(+" << pesoArista << ")->" << (mostrando.vertice)->obtenerNombreVertice();
                pesoAnterior = pesoTotal;
            }else if(criterio == 2){
                pesoTotalDouble = mostrando.pesoDouble;
                pesoAristaDouble = pesoTotalDouble - pesoAnteriorDouble;
                cout <<"-(+" << pesoAristaDouble << ")->" << (mostrando.vertice)->obtenerNombreVertice();
                pesoAnteriorDouble = pesoTotalDouble;
            }
        }
        aMostrar.pop();
    }
    if (criterio == 1){
        cout <<endl<<endl<< "Costo total en pesos: $" << pesoTotal << ",00" << endl;
    }else if(criterio == 2){
        cout <<endl<<endl<< "Costo total en horas: " << pesoTotalDouble << " hs." << endl;
    }

}

unsigned Grafo::obtenerTamanio() {
    return tamanio;
}

void Grafo::mostrarVertices(){
    cout << endl<<"Listado de aeropuertos en el grafo: \n"<<endl;
            Vertice* aux = this->obtenerPrimero();
            for(int i = 0; i < this->obtenerTamanio(); i++){
                cout << "- " << aux->obtenerNombreVertice() << endl;
                aux = aux->obtenerProxVertice();
            }
            cout<<endl;
            cin.get();
}

bool Grafo::marcadoComoVisitado(list<Vertice*> yaVisitados, Vertice* evaluado){
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

void Grafo::verificarPesoVerticeMarcado(Vertice* visitado, Vertice* destino, list<Etiqueta> &etiquetados, int modo, int iteracion, list<Vertice*> &vistos, ColaPrioridad &cola){
    int pesoYaEvaluado = 0;
    double pesoYaEvaluadoDouble = 0.0;

    int pesoArista = 0;
    double pesoAristaDouble = 0.0;
    pesoArista = this->obtenerPeso1(visitado, destino);
    pesoAristaDouble = this->obtenerPeso2(visitado, destino);

    int pesoQueCarga = 0;
    double pesoQueCargaDouble = 0.0;

    list<Etiqueta>::iterator itEtiq;
    itEtiq = etiquetados.begin();
    int encontrado = 0;
    while((encontrado != 2) && (itEtiq != etiquetados.end())){
        if((*itEtiq).getVertice() == visitado){//seria "el anterior"
            pesoQueCarga = (*itEtiq).getPesoAcumulado();
            pesoQueCargaDouble = (*itEtiq).getPesoDouble();
            encontrado++;
        }
        if((*itEtiq).getVertice() == destino){//seria "donde va la arista"
            pesoYaEvaluado = (*itEtiq).getPesoAcumulado();
            pesoYaEvaluadoDouble = (*itEtiq).getPesoDouble();
            encontrado++;
        }
        itEtiq++;
    }
    if(((modo == 1) && (pesoQueCarga + pesoArista < pesoYaEvaluado)) || ((modo == 2) && (pesoQueCargaDouble + pesoAristaDouble < pesoYaEvaluadoDouble))){
        itEtiq = etiquetados.begin();
        bool encontrado = false;
        while((!encontrado) && itEtiq != etiquetados.end()){
            if((*itEtiq).getVertice() == destino){
                (*itEtiq).setPesoAcumulado(pesoQueCarga + pesoArista);
                (*itEtiq).setPesoDouble(pesoQueCargaDouble + pesoAristaDouble);
                (*itEtiq).setIteracion(iteracion);
                vistos.remove(destino);
                cola.push(destino, pesoQueCarga + pesoArista, pesoQueCargaDouble + pesoAristaDouble, iteracion);
                encontrado = true;
            }
            itEtiq++;
        }
    }
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
