//
// Created by carolina on 3/6/20.
//

#include "BSTNode.h"
//#include "cola.h"

#include<iostream>

#ifndef ABB_BST_H
#define ABB_BST_H

template <class T>
class BST
{
private:
    // attributes
    BSTNode<T>* root;

    // methods
    BSTNode<T>* insert(BSTNode<T>* node, T data, string codigoIATA);

    void eliminar(BSTNode<T>* nodo);
    void liberarNodo(BSTNode<T>* node);
    //BSTNode<T>* sucesorDirecto(BSTNode<T>* node);
    //BSTNode<T>* find_minDIRECTO(BSTNode<T>* node);
    int obtenerAltura(BSTNode<T>* node);
    void mostrarNivel(BSTNode<T> * node, int nivel);
    void print_in_order(BSTNode<T> * node);
    void imprime_acostado(BSTNode<T> * node, int cont);
    void imprime_en_ancho(BSTNode<T> * node);
    //void mostrarCola(Cola* mostrando);
    BSTNode<T>* search(BSTNode<T>* node, T data);
    BSTNode<T>* buscarIATA(BSTNode<T>* node, string IATA);
    BSTNode<T>* buscarNombre(BSTNode<T>* node, string IATA);
    T find_min(BSTNode<T>* node);
    T find_max(BSTNode<T>* node);
    T successor(BSTNode<T>* node);
    /************************************************/
    T sucesor(BSTNode<T>* node);
    /*************************************************/
    T predecessor(BSTNode<T>* node);
    BSTNode<T>* remove(BSTNode<T>* node, T data);
    /***********************************************/
    BSTNode<T>* eliminar(BSTNode<T>* node, string IATA);
    /*************************************************/
    void delete_all(BSTNode<T>* node);

    BSTNode<T>* quitar(BSTNode<T>* node, string IATA);
    T successorQUITAR(BSTNode<T>* node);
    T find_minQUITAR(BSTNode<T>* node);
public:
    //methods

    // Creates an empty tree
    BST();

    BSTNode<T>* buscar(string& aBuscar);

    BSTNode<T>* quitar(string IATA);
    T successorQUITAR(string IATA);
    T find_minQUITAR();

    int obtenerAltura ();

    void imprime_acostado();

    void imprime_en_ancho();

    //void eliminarDirecto(BSTNode<T>* node);
     // Adds a new node to the actual BST. If its the tree is empty
     // the node inserted will be the root
    void insert(T data, string codigoIATA);

    // Prints all the data stored in the BST, sorted from the
    // smallest value to the greatest value.
    void print_in_order();

    // Finds a given value in the BST. If the key exists it returns
    // TRUE, otherwise it returns FALSE.
    bool search(T data);

    // Finds the minimum value that exist in the BST.
    T find_min();

    // Finds the maximum value that exist in the BST.
    T find_max();

    // Finds the successor of a given data value.
    T successor(T data);
    /******************************************************************/
    T sucesor(string IATA);
    /*****************************************************************/
    // Finds the predecessor of a given data value.
    T predecessor(T data);

    // Removes a given data from the BST
    void remove(T data);
    /*************************************/
    void eliminar(string IATA);
    /**************************************/
    BSTNode<T>* get_root();

    bool empty();

    // Deletes all the nodes in the BST
    void delete_all();
    ~BST<T>();

};

template <class T>
BST<T>::BST() {
    this->root = NULL;
}

template <class T>
T BST<T>::find_minQUITAR(BSTNode<T>* node)
{
    if(node == NULL)
        return NULL;//-1;
    else if(node->get_left() == NULL)
        return node->get_data();
    else
        return find_minQUITAR(node->get_left());
}

template <class T>
T BST<T>::find_minQUITAR()
{
    return find_minQUITAR(this->root);
}
template <class T>
T BST<T>::successorQUITAR(string IATA)
{
    BSTNode<T>* data_node = this->buscarIATA(this->root, IATA);
    // Return the key. If the key is not found or successor is not found, return -1
    if(data_node == NULL)
        return 0;//-1;
    else return successorQUITAR(data_node);
}
template <class T>
T BST<T>::successorQUITAR(BSTNode<T>* node)
{
    if (node->get_right() != NULL)
    {
        return find_minQUITAR(node->get_right());
    }
    BSTNode<T>* sucesor = NULL;
    BSTNode<T>* anterior = this->root;
    while(anterior != node) {
        if(node->get_IATA() < anterior->get_IATA()) {
            sucesor = anterior;
            anterior = anterior->get_left();
        }
        else
            anterior = anterior->get_right();
    }
    return sucesor->get_data();
}
template <class T>
BSTNode<T>* BST<T>::quitar(BSTNode<T>* node, string IATA){
// The given node is not found in BST
    if (node == NULL)
        return NULL;

    if (node->get_IATA() == IATA)
    {
        if (node->isLeaf()){
            liberarNodo(node);
            node = 0;
        }
        else if (node->rightChildOnly())
        {
            // The only child will be connected to the parent's of node directly
            node->get_right()->set_parent(node->get_parent());
            // Bypass node
            BSTNode<T>* aux = node;
            node = node->get_right();
            liberarNodo(aux);
            //delete aux;
        }
        else if (node->leftChildOnly())
        {
            // The only child will be connected to the parent's of node directly
            node->get_left()->set_parent(node->get_parent());
            // Bypass node
            BSTNode<T>* aux = node;
            node = node->get_left();
            liberarNodo(aux);
            //delete aux;
        }

        // The node has two children (left and right)
        else
        {
            // Find successor or predecessor to avoid quarrel
            T dato_del_sucesor = this->successorQUITAR(IATA);

            // Replace node's key with successor's key
            node->set_data(dato_del_sucesor);
            node->set_IATA(dato_del_sucesor->obtenerCodigo());

            // Delete the old successor's key
            node->set_right(quitar(node->get_right(), dato_del_sucesor->obtenerCodigo()));
        }
    }

    else if (node->get_IATA() < IATA)
        node->set_right(quitar(node->get_right(), IATA));

    else
        node->set_left(quitar(node->get_left(), IATA));

    return node;
}
template <class T>
BSTNode<T>* BST<T>::quitar(string IATA){
    return this->quitar(this->root, IATA);
}

template <class T>
BSTNode<T>* BST<T>::buscar(string& aBuscar){
    cout << "Busca por IATA...\n";
    BSTNode<T>* encontrado = buscarIATA(this->root, aBuscar);
    if(!encontrado){
        cout << "Busca por Nombre...\n";
        encontrado = buscarNombre(this->root, aBuscar);
    }
    return encontrado;
}
template <class T>
BSTNode<T>* BST<T>::buscarIATA(BSTNode<T>* node, string IATA){
    if (node == NULL || node->get_IATA() == IATA)
        return node;

    if (IATA > node->get_IATA())
        return buscarIATA(node->get_right(), IATA);

    return buscarIATA(node->get_left(), IATA);
}

template <class T>
BSTNode<T>* BST<T>::buscarNombre(BSTNode<T>* node, string nombreAeropuerto){
    if (node == NULL || node->get_data()->obtenerNombre() == nombreAeropuerto)
        return node;
    BSTNode<T>* buscado = buscarNombre(node->get_left(), nombreAeropuerto);
    if(!buscado){
        buscado = buscarNombre(node->get_right(), nombreAeropuerto);
    }
    return buscado;
}

template <class T>
int BST<T>::obtenerAltura(BSTNode<T>* node) {
    if (node !=NULL){
        int alturaLadoIzquierdo = obtenerAltura(node->get_left()) + 1;
        int alturaLadoDerecho = obtenerAltura(node->get_right()) + 1;
        if (alturaLadoIzquierdo > alturaLadoDerecho){
            return alturaLadoIzquierdo;
        }
        return alturaLadoDerecho;
    }

    return -1;
}


template <class T>
int BST<T>::obtenerAltura() {
    return this->obtenerAltura(this->root);
}

template <class T>
BSTNode<T>* BST<T>::insert(BSTNode<T>* node, T data, string codigoIATA) {

    if (node == NULL) {
        node = new BSTNode<T>(data, codigoIATA);
    }

    else if (codigoIATA > node->get_IATA()) {
        node->set_right(insert(node->get_right(), data, codigoIATA), node);
    }

    else {
        node->set_left(insert(node->get_left(), data, codigoIATA), node);
    }
    return node;
}

template <class T>
void BST<T>::insert(T data, string codigoIATA)
{
    this->root = insert(this->root, data, codigoIATA);
}

template <class T>
void BST<T>::print_in_order(BSTNode<T>* node)
{
    if (node != NULL)
    {
        print_in_order(node->get_left());
        std::cout<<node->get_IATA()<<' ';
        print_in_order(node->get_right());
    }
}

template <class T>
void BST<T>::print_in_order()
{
    this->print_in_order(this->root);
}

template <class T>
void BST<T>::mostrarNivel(BSTNode<T> * node, int nivel){
    if(node != NULL){
        if(nivel == 0){
            std::cout<< node->get_data()->obtenerCodigo()<< " - ";
        }
        mostrarNivel(node->get_left(), nivel-1);
        mostrarNivel(node->get_right(), nivel-1);
    }
}

template <class T>
void BST<T>::imprime_en_ancho(){
    this->imprime_en_ancho(this->root);
}

template <class T>
void BST<T>::imprime_en_ancho(BSTNode<T> * node){
    if(!this->root){
        cout << "\nArbol vacio\n";
        return;
    }
    int alturaDelArbol = this->obtenerAltura();
    for (int i = 0; i< alturaDelArbol +1; i++){
        std::cout<< "Nivel "<<i<<": ";
        this->mostrarNivel(node,i);
        std::cout<<std::endl;
    }
}
/*template <class T>
void BST<T>::imprime_en_ancho(BSTNode<T> * node){
    if(!this->root){
        cout << "\nArbol vacio\n";
        return;
    }
    Cola conForma, paraMostrar;
    conForma.insertar(node);
    BSTNode<T>* visitado;
    int largoLista, nivel = 0;
    while(!conForma.vacia()){
        largoLista = conForma.obtenerTamanio();
        for(int i = 0; i < largoLista; i++){
            BSTNode<T>* aLista = conForma.consultar();
            conForma.eliminar();
            paraMostrar.insertar(aLista);
        }
        Cola aux(paraMostrar);
        cout << "Nivel " << nivel++ << ": ";
        mostrarCola(&aux);
        largoLista = paraMostrar.obtenerTamanio();
        for(int f = 0; f < largoLista; f++){
            visitado = paraMostrar.consultar();
            paraMostrar.eliminar();
            if(visitado->get_left()){
                conForma.insertar(visitado->get_left());
            }
            if(visitado->get_right()){
                conForma.insertar(visitado->get_right());
            }
        }
    }
}*/


/*template <class T>
void BST<T>::mostrarCola(Cola* mostrando){
    int tamanio = mostrando->obtenerTamanio();
    for (int i = 0; i < tamanio; i++){
        cout << mostrando->eliminar();
        if(i < tamanio - 1) cout << " * ";
    }
    cout << endl;//aca impreime la linea de ese nivel si
}
*/
template <class T>
void BST<T>::imprime_acostado(BSTNode<T> * node, int cont){
    if (!node){
        return;
    }else{
        imprime_acostado(node->get_right(), cont + 1);
        for(int i = 0; i < cont; i++){
            cout << "   ";
        }
        cout << node->get_IATA() << endl;
        imprime_acostado(node->get_left(), cont + 1);
    }
}

template <class T>
void BST<T>::imprime_acostado(){
    imprime_acostado(this->root, 0);
}

template <class T>
BSTNode<T>* BST<T>::search(BSTNode<T>* node, T data)//aca hay que cambiar que busque por codigo
{
    if (node == NULL || node->get_data() == data)
        return node;

    if (data > node->get_data())
        return search(node->get_right(), data);

    return search(node->get_left(), data);
}

template <class T>
bool BST<T>::search(T data)
{
    BSTNode<T>* result = search(this->root, data);

    return result != NULL;
}

template <class T>
T BST<T>::find_min(BSTNode<T>* node)
{
    if(node == NULL)
        return NULL;//-1;
    else if(node->get_left() == NULL)
        return node->get_data();
    else
        return find_min(node->get_left());
}

template <class T>
T BST<T>::find_min()
{
    return find_min(this->root);
}

template <class T>
T BST<T>::find_max(BSTNode<T>* node)
{
    if(node == NULL)
        return NULL;//-1;
    else if(node->get_right() == NULL)
        return node->get_data();
    else
        return find_max(node->get_right());
}

template <class T>
T BST<T>::find_max()
{
    return find_max(this->root);
}

template <class T>
T BST<T>::successor(BSTNode<T>* node)
{
    if (node->get_right() != NULL)
    {
        return find_min(node->get_right());
    }
    BSTNode<T>* successor = NULL;
    BSTNode<T>* ancestor = this->root;
    while(ancestor != node) {
        if(node->get_data() < ancestor->get_data()) {
            successor = ancestor;
            ancestor = ancestor->get_left();
        }
        else
            ancestor = ancestor->get_right();
    }
    return successor->get_data();
}

template <class T>
T BST<T>::successor(T data)
{
    BSTNode<T>* data_node = this->search(this->root, data);
    // Return the key. If the key is not found or successor is not found, return -1
    if(data_node == NULL)
        return -1;
    else return successor(data_node);
}

template <class T>
T BST<T>::predecessor(BSTNode<T> * node)
{
    if (node->get_left() != NULL)
    {
        return find_max(node->get_left());
    }

    BSTNode<T>* successor = NULL;
    BSTNode<T>* ancestor = this->root;
    while(ancestor != node) {
        if(node->get_data() > ancestor->get_data()) {
            successor = ancestor; // so far this is the deepest node for which current node is in left
            ancestor = ancestor->get_right();
        }
        else
            ancestor = ancestor->get_left();
    }
    return successor->get_data();
}

template <class T>
T BST<T>::predecessor(T data)
{
    BSTNode<T> * data_node = this->search(this->root, data);

    if(data_node == NULL)
        return -1;
    else return predecessor(data_node);
}

template <class T>
BSTNode<T> * BST<T>::remove(BSTNode<T>* node, T data)
{
    // The given node is not found in BST
    if (node == NULL)
        return NULL;

    if (node->get_data() == data)
    {
        if (node->isLeaf())
            delete node;
        else if (node->rightChildOnly())
        {
            // The only child will be connected to the parent's of node directly
            node->get_right()->set_parent(node->get_parent());
            // Bypass node
            BSTNode<T>* aux = node;
            node = node->get_right();
            delete aux;
        }
        else if (node->leftChildOnly())
        {
            // The only child will be connected to the parent's of node directly
            node->get_left()->set_parent(node->get_parent());
            // Bypass node
            BSTNode<T>* aux = node;
            node = node->get_left();
            delete aux;
        }

        // The node has two children (left and right)
        else
        {
            // Find successor or predecessor to avoid quarrel
            T successor_data = this->successor(data);

            // Replace node's key with successor's key
            node->set_data(successor_data);

            // Delete the old successor's key
            node->set_right(remove(node->get_right(), successor_data));
        }
    }

    else if (node->get_data() < data)
        node->set_right(remove(node->get_right(), data));

    else
        node->set_left(remove(node->get_left(), data));

    return node;
}

template <class T>
void BST<T>::remove(T data)
{
    this->root = remove(this->root, data);
}

/**************************************************************/
/*************************************************************/
template <class T>
T BST<T>::sucesor(BSTNode<T>* node)
{
    if (node->get_right() != NULL)
    {
        return find_min(node->get_right());
    }
    BSTNode<T>* successor = NULL;
    BSTNode<T>* ancestor = this->root;
    while(ancestor != node) {
        if(node->get_data()->obtenerCodigo() < ancestor->get_data()->obtenerCodigo()) {
            successor = ancestor;
            ancestor = ancestor->get_left();
        }
        else
            ancestor = ancestor->get_right();
    }
    return successor->get_data();
}

template <class T>
T BST<T>::sucesor(string IATA)
{
    BSTNode<T>* data_node = this->buscarIATA(this->root, IATA);
    // Return the key. If the key is not found or successor is not found, return -1
    if(data_node == NULL)
        return NULL;//-1;
    else return sucesor(data_node);
}

template <class T>
BSTNode<T> * BST<T>::eliminar(BSTNode<T>* node, string IATA)
{
    // The given node is not found in BST
    if (node == NULL)
        return NULL;

    if (node->get_data()->obtenerCodigo() == IATA)
    {
        if (node->isLeaf())
            delete node;
        else if (node->rightChildOnly())
        {
            // The only child will be connected to the parent's of node directly
            node->get_right()->set_parent(node->get_parent());
            // Bypass node
            BSTNode<T>* aux = node;
            node = node->get_right();
            delete aux;
        }
        else if (node->leftChildOnly())
        {
            // The only child will be connected to the parent's of node directly
            node->get_left()->set_parent(node->get_parent());
            // Bypass node
            BSTNode<T>* aux = node;
            node = node->get_left();
            delete aux;
        }

        // The node has two children (left and right)
        else
        {
            // Find successor or predecessor to avoid quarrel
            T successor_data = this->sucesor(IATA);

            // Replace node's key with successor's key
            node->set_data(successor_data);
            node->set_IATA(successor_data->obtenerCodigo());
            // Delete the old successor's key
            node->set_right(eliminar(node->get_right(), successor_data->obtenerCodigo()));
        }
    }

    else if (node->get_data()->obtenerCodigo() < IATA)
        node->set_right(eliminar(node->get_right(), IATA));

    else
        node->set_left(eliminar(node->get_left(), IATA));

    return node;
}

template <class T>
void BST<T>::eliminar(string IATA)
{
    this->root = eliminar(this->root,IATA);
}
/********************************************/
/*******************************************************************************************************/
template <class T>
BSTNode<T>* BST<T>::get_root(){
    return this->root;
}

template <class T>
bool BST<T>::empty()
{
    return this->root == NULL;
}


template <class T>
void BST<T>::delete_all(BSTNode<T>* node)
{
    if(node == NULL)
        return;
    this->delete_all(node->get_left());
    this->delete_all(node->get_right());
    delete node->get_data();
    delete node;
}


template <class T>
void BST<T>::liberarNodo(BSTNode<T>* node)
{
    delete node->get_data();
    delete node;
}

template <class T>
void BST<T>::delete_all()
{
    this->delete_all(this->root);
}

template <class T>
BST<T>::~BST<T>()
{
    this->delete_all();
}


#endif //ABB_BST_H
