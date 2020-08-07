//
// Created by carolina on 3/6/20.
//

#ifndef ABB_BSTNODE2_H
#define ABB_BSTNODE2_H

template <class T>
class BSTNode2
{
private:
    T data;
    BSTNode2<T>* left; //Left children
    BSTNode2<T>* right; //Right children
    BSTNode2<T>* parent;

public:
    BSTNode2(T data);
    T get_data();
    void set_data(T data);
    void set_right(BSTNode2<T>* right, BSTNode2<T>* parent);
    void set_left(BSTNode2<T>* left, BSTNode2<T>* parent);
    void set_left(BSTNode2<T>* left);
    void set_right(BSTNode2<T>* right);
    void set_parent(BSTNode2<T>* parent);
    BSTNode2<T>* get_right();
    BSTNode2<T>* get_left();
    BSTNode2<T>* get_parent();
    bool isLeaf();
    bool rightChildOnly();
    bool leftChildOnly();
};

template <class T>
BSTNode2<T>::BSTNode2(T data)
{
    this->data = data;
    this->left = NULL;
    this->right = NULL;
    this->parent = NULL;
}

template <class T>
T BSTNode2<T>::get_data()
{
    return this->data;
}

template <class T>
void BSTNode2<T>::set_right(BSTNode2<T>* right, BSTNode2<T>* parent){
    this->right = right;
    this->parent = parent;
}

template <class T>
void BSTNode2<T>::set_right(BSTNode2<T>* right){
    this->right = right;
}

template <class T>
void BSTNode2<T>::set_left(BSTNode2<T>* left, BSTNode2<T>* parent){
    this->left = left;
    this->parent = parent;
}

template <class T>
void BSTNode2<T>::set_parent(BSTNode2<T> *parent) {
    this->parent = parent;
}

template <class T>
void BSTNode2<T>::set_data(T data) {
    this->data = data;
}


template <class T>
void BSTNode2<T>::set_left(BSTNode2<T>* left){
    this->left = left;
}

template <class T>
BSTNode2<T>* BSTNode2<T>::get_right()
{
    return this->right;
}

template <class T>
BSTNode2<T>* BSTNode2<T>::get_left()
{
    return this->left;
}

template <class T>
BSTNode2<T>* BSTNode2<T>::get_parent()
{
    return this->parent;
}

template <class T>
bool BSTNode2<T>::isLeaf() {
    return (this->get_left() == NULL && this->get_right() == NULL);
}

template <class T>
bool BSTNode2<T>::rightChildOnly() {
    return (this->get_left() == NULL && this->get_right() != NULL);
}

template <class T>
bool BSTNode2<T>::leftChildOnly() {
    return (this->get_left() != NULL && this->get_right() == NULL);
}

#endif //ABB_BSTNODE2s_H
