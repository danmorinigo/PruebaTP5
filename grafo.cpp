#include "Grafo.h"

Grafo::Grafo(){
    primero = 0;
    ultimo = 0;
    tamanio = 0;
}
void Grafo::agregarVertice(string nombre){
    Vertice* ingresante = new Vertice(nombre);
    if (!primero){
        primero = ingresante;
        ultimo = ingresante;
        tamanio++;
        return;
    }
    Vertice* aux = primero;
    while(aux->obtenerProxVertice() != 0){
        aux = aux->obtenerProxVertice();
    }
    aux->asignarProxVertice(ingresante);
    ultimo = ingresante;
    tamanio++;
}
int Grafo::obtenerPeso1(Vertice* inicio, Vertice* destino){
    if(!inicio || !destino){
        cout << "Error salida / llegada\n";
        return 0;
    }
    Arista* aux1 = inicio->obtenerAristas();
    while(aux1){
        if(aux1->ConsultarDestino() == destino){
            return aux1->cunsultarPrecio();
        }
        aux1 = aux1->consultarSiguiente();
    }
    return -1;
}
double Grafo::obtenerPeso2(Vertice* inicio, Vertice* destino){
    if(!inicio || !destino){
        cout << "Error salida / llegada\n";
        return 0;
    }
    Arista* aux1 = inicio->obtenerAristas();
    while(aux1){
        if(aux1->ConsultarDestino() == destino){
            return aux1->consultarHoras();
        }
        aux1 = aux1->consultarSiguiente();
    }
    return -1;
}

Vertice* Grafo::obtenerPrimero(){
    return this->primero;
}
bool Grafo::existeVertice(string nombre){
    return (obtenerVertice(nombre) != 0);
}
Vertice* Grafo::obtenerVertice(string nombre){
    Vertice* aux = primero;
    for(int i = 0; i < tamanio; i++){
        if(aux->obtenerNombreVertice() == nombre){
            return aux;
        }
        aux = aux->obtenerProxVertice();
    }
    return 0;
}
int Grafo::cantVertices(){
    return this->tamanio;
}
void Grafo::agregarArista(Vertice* inicio, Vertice* destino, int precio, double horasVuelo){
    if(!inicio || !destino){
        cout << "Error salida / llegada\n";
        return;
    }
    Arista* nuevaArista = new Arista(destino);
    nuevaArista->asignarPrecio(precio);
    nuevaArista->asignarHoras(horasVuelo);
    inicio->agregarArista(nuevaArista);
}

//deben estar verificadas las existencias de ambos vertices
//precioUhorasVuelo -> 1-precio, 2-horas
void Grafo::caminoMinimo(Vertice* salida, Vertice* destino, int precioUhorasVuelo){

    //APARENTA QUE SE PUEDE SACAR ESTA BOOL
    bool primeraEntrada = true; //Lo uso para el caso en que la salida y la
                                //llegada sea la misma

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
    }
    //------------------------------------------------------

    Vertice* verticeVisitado;
    //Unico vertice en la cola, al entrar, es el vertice de partida
    while(!cola.vacia()){
        verticeVisitado = cola.topAndPop();
        //bool fueVisitadoAntes = false;
        //**************
        bool fueVisitadoAntes = marcadoComoVisitado(vistos, verticeVisitado);
        //*************
        /*
        //SE PUEDE SACAR APARENTEMENTE--
        list<Vertice*>::iterator i;
        i = vistos.begin();
        //Si el vertice que quiero visitar ya fue marcado como visitado
        //no lo evalua
        while(i != vistos.end() && !fueVisitadoAntes){
            if(*i == verticeVisitado){
                fueVisitadoAntes = true;
            }
            i++;
        }
        */
        //-------------------------------------------------------------------

        Arista* auxAristas;
        if(!fueVisitadoAntes){
            auxAristas = verticeVisitado->obtenerAristas();
            while(auxAristas){

                //-------------------------------------------------------------------
                //Verifico que los destinos de cada arista del vertice evaluado
                //no estan marcados como visitados
                //fueVisitadoAntes = false;
                //**********************
                bool fueVisitadoAntes = marcadoComoVisitado(vistos, auxAristas->ConsultarDestino());
                //**********************

                /* LO LLEVO AL FINAL DEL IF
                list<Vertice*>::iterator i;
                i = vistos.begin();
                while(i != vistos.end() && !fueVisitadoAntes){
                    if(*i == auxAristas->ConsultarDestino()){
                        int pesoYaEvaluado = 0;
                        double pesoYaEvaluadoDouble = 0.0;

                        int pesoArista = 0;
                        double pesoAristaDouble = 0.0;
                        pesoArista = this->obtenerPeso1(verticeVisitado, auxAristas->ConsultarDestino());
                        pesoAristaDouble = this->obtenerPeso2(verticeVisitado, auxAristas->ConsultarDestino());

                        int pesoQueCarga = 0;
                        double pesoQueCargaDouble = 0.0;

                        itEtiq = etiquetados.begin();
                        int encontrado = 0;
                        while((encontrado != 2) && (itEtiq != etiquetados.end())){
                            if((*itEtiq).getVertice() == verticeVisitado){//seria "el anterior"
                                pesoQueCarga = (*itEtiq).getPesoAcumulado();
                                pesoQueCargaDouble = (*itEtiq).getPesoDouble();
                                encontrado++;
                            }
                            if((*itEtiq).getVertice() == auxAristas->ConsultarDestino()){//seria "donde va la arista"
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
                                if((*itEtiq).getVertice() == auxAristas->ConsultarDestino()){
                                    (*itEtiq).setPesoAcumulado(pesoQueCarga + pesoArista);
                                    (*itEtiq).setPesoDouble(pesoQueCargaDouble + pesoAristaDouble);
                                    (*itEtiq).setIteracion(iteracion);
                                    vistos.remove(auxAristas->ConsultarDestino());
                                    cola.push(auxAristas->ConsultarDestino(), pesoQueCarga + pesoArista, pesoQueCarga + pesoArista, iteracion);
                                    encontrado = true;
                                }
                                itEtiq++;
                            }
                        }
                        fueVisitadoAntes = true;
                    }
                    i++;
                }
                */
                //-------------------------------------------------------------------
                //Si fue visitado saltea este if, y continua con la siguiente arista
                if(!fueVisitadoAntes){
                    int pesoEntero = this->obtenerPeso1(verticeVisitado, auxAristas->ConsultarDestino());
                    int pesoDouble = this->obtenerPeso2(verticeVisitado, auxAristas->ConsultarDestino());
                    cola.push(auxAristas->ConsultarDestino(), pesoEntero, pesoDouble, iteracion);

                    //Dos etiquetas auxiliares, uno apuntando al vertice visitado
                    //el otro apuntando al vertice destino de la arista
                    Etiqueta auxActual(verticeVisitado), auxDestino(auxAristas->ConsultarDestino());
                    //Busco etiquetas correspondientes y copio sus datos
                    itEtiq = etiquetados.begin();
                    int losDos = 0;
                    while(losDos != 2){
                        if((*itEtiq).getVertice() == verticeVisitado){
                            auxActual = *itEtiq;
                            losDos++;
                        }
                        if((*itEtiq).getVertice() == auxAristas->ConsultarDestino()){
                            auxDestino = *itEtiq;
                            losDos++;
                        }
                        itEtiq++;
                    }
                    //CAMBIO O NO ETIQUETA DE VERTICES DESTINO DE LA ACTUAL ARISTA???
                    //---------------------------------------------------------------
                    int miPeso, pesoArista, pesoTotal;
                    double miPesoDouble, pesoAristaDouble, pesoTotalDouble;
                    //******************************
                    if(!auxActual.getAnterior().empty()){
                        //cout << "SIN PAPA" << endl;
                        miPeso = auxActual.getPesoAcumulado();
                        miPesoDouble = auxActual.getPesoDouble();
                    }else{
                        miPeso = 0;
                        miPesoDouble = 0.0;
                    }
                    //miPeso = auxActual.getPesoAcumulado();
                    //miPesoDouble = auxActual.getPesoDouble();
                    //******************************

                    pesoAristaDouble = this->obtenerPeso2(verticeVisitado, auxDestino.getVertice());
                    pesoArista = this->obtenerPeso1(verticeVisitado, auxDestino.getVertice());
                    pesoTotal = miPeso + pesoArista;
                    pesoTotalDouble = miPesoDouble + pesoAristaDouble;
                    if(auxDestino.getAnterior().empty()){   //Si no tiene predecesor no tiene peso
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
                        }else if(pesoTotal == suPeso){  //Si es igual, agrego un nuevo anterior
                                                        //y cambio iteracion
                                                        //iteracion nada, lo saque de no se que clase
                                                        //per no le encontre utilidad hasta ahora
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
                    /*
                    list<Vertice*>::iterator i;
                    i = vistos.begin();
                    while(i != vistos.end() && !fueVisitadoAntes){
                        if(*i == auxAristas->ConsultarDestino()){

                            //verificarPesoVerticeVisitado
                            int pesoYaEvaluado = 0;
                            double pesoYaEvaluadoDouble = 0.0;

                            int pesoArista = 0;
                            double pesoAristaDouble = 0.0;
                            pesoArista = this->obtenerPeso1(verticeVisitado, auxAristas->ConsultarDestino());
                            pesoAristaDouble = this->obtenerPeso2(verticeVisitado, auxAristas->ConsultarDestino());

                            int pesoQueCarga = 0;
                            double pesoQueCargaDouble = 0.0;

                            itEtiq = etiquetados.begin();
                            int encontrado = 0;
                            while((encontrado != 2) && (itEtiq != etiquetados.end())){
                                if((*itEtiq).getVertice() == verticeVisitado){//seria "el anterior"
                                    pesoQueCarga = (*itEtiq).getPesoAcumulado();
                                    pesoQueCargaDouble = (*itEtiq).getPesoDouble();
                                    encontrado++;
                                }
                                if((*itEtiq).getVertice() == auxAristas->ConsultarDestino()){//seria "donde va la arista"
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
                                    if((*itEtiq).getVertice() == auxAristas->ConsultarDestino()){
                                        (*itEtiq).setPesoAcumulado(pesoQueCarga + pesoArista);
                                        (*itEtiq).setPesoDouble(pesoQueCargaDouble + pesoAristaDouble);
                                        (*itEtiq).setIteracion(iteracion);
                                        vistos.remove(auxAristas->ConsultarDestino());
                                        cola.push(auxAristas->ConsultarDestino(), pesoQueCarga + pesoArista, pesoQueCarga + pesoArista, iteracion);
                                        encontrado = true;
                                    }
                                    itEtiq++;
                                }
                            }
                            fueVisitadoAntes = true;
                        }
                        i++;
                    }
                */
                }

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

            //Este condicional lo puse para el caso de que inicio y fin del viaje sea el mismo
            //De esta forma no marco el vertice de salida como visitado si es la primera iteracion
            //


            //*****************************
            /* PROBANDO COLOCANDO INICIO D ETIQUETAS EN INFINITO...
            //APARENTA QUE YA PODEMOS QUITAR ESTOS CONDICIONALES
            if(salida == destino){
                if(primeraEntrada){
                    primeraEntrada = false;
                }else{
                    //-----creo se puede sacar este if------------
                    if(verticeVisitado != destino){
                    //-----creo se puede sacar este if------------
                        vistos.push_back(verticeVisitado);
                    }
                }
            }else{
                //-----creo se puede sacar este if------------
                if(verticeVisitado != destino){
                //-----creo se puede sacar este if------------
                    vistos.push_back(verticeVisitado);
                }
            }
            */
            //****************************************************************
            vistos.push_back(verticeVisitado);
            //****************************************************************
            iteracion++;
        }
    }
    //------------------------------------------------------
    //HACER METODO APARTE
    //Solo muestro el orden en que fueron recorridos los vertices
    /*Vertice* auxilio;
    cout << "----------------------------" << endl;
    cout << "VERTICES MARCADOS (EN ORDEN)" << endl;
    cout << "----------------------------" << endl;
    list<Vertice*>::iterator i;
    for(i = vistos.begin(); i != vistos.end(); i++){
        auxilio = *i;
        cout << auxilio->obtenerNombreVertice() << endl;
    }*/
    //------------------------------------------------------
    //-------------------------------------------------
    //metodo aparte HAY CAMINO??
    //busca la etiqueta del vertide destino
    //si hay camino.....
    //comienzo del camino tiene la lista de ancestros de destino
    itEtiq = etiquetados.begin();
    bool hayCamino = false;
    list<Vertice*> comienzoDelCamino;
    while(!hayCamino && itEtiq != etiquetados.end()){
        if((*itEtiq).getVertice() == destino){
            if (!(*itEtiq).getAnterior().empty()){
                comienzoDelCamino = (*itEtiq).getAnterior();
                hayCamino = true;
            }
        }
        itEtiq++;
    }
    //------------------------------------------------
    if(hayCamino){
      /*  cout << "------------------" << endl;
        cout << "Se encontro camino\n";
        cout << "------------------" << endl;*/
        //-----------------------------------------------------------------
        //Solo muestro etiquetas finales
       /* cout << "----------------" << endl;
        cout << "ETIQUETADO FINAL" << endl;
        cout << "----------------" << endl;
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
        }*/
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
                        int pesoEntero = 0;
                        double pesoDouble = 0.0;
                        pesoEntero = this->obtenerPeso1(recorriendoDesdeLocal, recorriendoDesde);
                        pesoDouble = this->obtenerPeso2(recorriendoDesdeLocal, recorriendoDesde);
                        int pesoQueTraiaElOtro = tuplaLocal.pesoAcumulado;
                        double pesoQueTraiaDouble = tuplaLocal.pesoDouble;
                        int anteriorDebeAcumular = pesoQueTraiaElOtro - pesoEntero;
                        double anteriorDebeDouble = pesoQueTraiaDouble - pesoDouble;
                        int anteriorAcumula = 0;
                        double anteriorAcumulaDouble = 0;
                        if(((criterio == 1) && (anteriorAcumula == anteriorDebeAcumular)) || ((criterio == 2) && (anteriorAcumulaDouble == anteriorDebeDouble))){
                            bool primerRecorrido = false;
                            mostrarVer3(etiquetados, recorriendoDesdeLocal, destino, PilaLocal, primerRecorrido, criterio);
                        }
                    }else{
                        int pesoEntero = 0;
                        double pesoDouble = 0.0;
                        pesoEntero = this->obtenerPeso1(recorriendoDesdeLocal, recorriendoDesde);
                        pesoDouble = this->obtenerPeso2(recorriendoDesdeLocal, recorriendoDesde);
                        int pesoQueTraiaElOtro = tuplaLocal.pesoAcumulado;
                        double pesoQueTraiaDouble = tuplaLocal.pesoDouble;
                        int anteriorDebeAcumular = pesoQueTraiaElOtro - pesoEntero;
                        double anteriorDebeDouble = pesoQueTraiaDouble - pesoDouble;
                        int anteriorAcumula;
                        double anteriorAcumulaDouble;
                        list<Etiqueta>::iterator i;
                        i = etiquetados.begin();
                        bool hecho = false;
                        while(!hecho && i != etiquetados.end()){
                            if((*i).getVertice() == recorriendoDesdeLocal){
                                anteriorAcumula = (*i).getPesoAcumulado();
                                anteriorAcumulaDouble = (*i).getPesoDouble();
                                hecho = true;
                            }
                            i++;
                        }
                        if(((criterio == 1) && (anteriorAcumula == anteriorDebeAcumular)) || ((criterio == 2) && (anteriorAcumulaDouble == anteriorDebeDouble))){
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
