//
// Created by carolina on 3/6/20.
//

#include "BSTNode2.h"
#include<iostream>

#ifndef ABB_BST2_H
#define ABB_BST2_H

template <class T>
class BST2
{
private:
    // attributes
    BSTNode2<T>* root;

    // methods
    BSTNode2<T>* insert(BSTNode2<T>* node, T data);
    void print_in_order(BSTNode2<T> * node);
    BSTNode2<T>* search(BSTNode2<T>* node, T data);
    T find_min(BSTNode2<T>* node);
    T find_max(BSTNode2<T>* node);
    T successor(BSTNode2<T>* node);
    T predecessor(BSTNode2<T>* node);
    BSTNode2<T>* remove(BSTNode2<T>* node, T data);
    void delete_all(BSTNode2<T>* node);

public:
    //methods

    // Creates an empty tree
    BST2();

     // Adds a new node to the actual BST. If its the tree is empty
     // the node inserted will be the root
    void insert(T data);

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

    // Finds the predecessor of a given data value.
    T predecessor(T data);

    // Removes a given data from the BST
    void remove(T data);

    BSTNode2<T>* get_root();
    bool empty();

    // Deletes all the nodes in the BST
    void delete_all();
    ~BST2<T>();

};

template <class T>
BST2<T>::BST2() {
    this->root = NULL;
}

template <class T>
BSTNode2<T>* BST2<T>::insert(BSTNode2<T>* node, T data) {

    if (node == NULL) {
        node = new BSTNode2<T>(data);
    }

    else if (data > node->get_data()) {
        node->set_right(insert(node->get_right(), data), node);
    }

    else {
        node->set_left(insert(node->get_left(), data), node);
    }
    return node;
}

template <class T>
void BST2<T>::insert(T data)
{
    this->root = insert(this->root, data);
}

template <class T>
void BST2<T>::print_in_order(BSTNode2<T>* node)
{
    if (node != NULL)
    {
        print_in_order(node->get_left());
        std::cout<<node->get_data()<<' ';
        print_in_order(node->get_right());
    }
}

template <class T>
void BST2<T>::print_in_order()
{
    this->print_in_order(this->root);
}

template <class T>
BSTNode2<T>* BST2<T>::search(BSTNode2<T>* node, T data)
{
    if (node == NULL || node->get_data() == data)
        return node;

    if (data > node->get_data())
        return search(node->get_right(), data);

    return search(node->get_left(), data);
}

template <class T>
bool BST2<T>::search(T data)
{
    BSTNode2<T>* result = search(this->root, data);

    return result != NULL;
}

template <class T>
T BST2<T>::find_min(BSTNode2<T>* node)
{
    if(node == NULL)
        return -1;
    else if(node->get_left() == NULL)
        return node->get_data();
    else
        return find_min(node->get_left());
}

template <class T>
T BST2<T>::find_min()
{
    return find_min(this->root);
}

template <class T>
T BST2<T>::find_max(BSTNode2<T>* node)
{
    if(node == NULL)
        return -1;
    else if(node->get_right() == NULL)
        return node->get_data();
    else
        return find_max(node->get_right());
}

template <class T>
T BST2<T>::find_max()
{
    return find_max(this->root);
}

template <class T>
T BST2<T>::successor(BSTNode2<T>* node)
{
    if (node->get_right() != NULL)
    {
        return find_min(node->get_right());
    }
    BSTNode2<T>* successor = NULL;
    BSTNode2<T>* ancestor = this->root;
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
T BST2<T>::successor(T data)
{
    BSTNode2<T>* data_node = this->search(this->root, data);
    // Return the key. If the key is not found or successor is not found, return -1
    if(data_node == NULL)
        return -1;
    else return successor(data_node);
}

template <class T>
T BST2<T>::predecessor(BSTNode2<T> * node)
{
    if (node->get_left() != NULL)
    {
        return find_max(node->get_left());
    }

    BSTNode2<T>* successor = NULL;
    BSTNode2<T>* ancestor = this->root;
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
T BST2<T>::predecessor(T data)
{
    BSTNode2<T> * data_node = this->search(this->root, data);

    if(data_node == NULL)
        return -1;
    else return predecessor(data_node);
}

template <class T>
BSTNode2<T> * BST2<T>::remove(BSTNode2<T>* node, T data)
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
            BSTNode2<T>* aux = node;
            node = node->get_right();
            delete aux;
        }
        else if (node->leftChildOnly())
        {
            // The only child will be connected to the parent's of node directly
            node->get_left()->set_parent(node->get_parent());
            // Bypass node
            BSTNode2<T>* aux = node;
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
void BST2<T>::remove(T data)
{
    this->root = remove(this->root, data);
}

template <class T>
BSTNode2<T>* BST2<T>::get_root(){
    return this->root;
}

template <class T>
bool BST2<T>::empty()
{
    return this->root == NULL;
}


template <class T>
void BST2<T>::delete_all(BSTNode2<T>* node)
{
    if(node == NULL)
        return;
    this->delete_all(node->get_left());
    this->delete_all(node->get_right());
    delete node;
}

template <class T>
void BST2<T>::delete_all()
{
    this->delete_all(this->root);
}

template <class T>
BST2<T>::~BST2<T>()
{
    this->delete_all();
}


#endif //ABB_BST_H
