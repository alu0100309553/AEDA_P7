/*
 * arbol.hpp
 * Autor: Rubén Labrador Páez
 * EMail: alu0100309553@ull.edu.es
 * Grado en Ingeniería informática, 2ºCurso, Universidad de La Laguna.
 * Algoritmos y estructuras de datos avanzadas, Práctica 7, ArbolAVL
 */

#ifndef nodo_HPP_
#define nodo_HPP_

#include <iostream>

using namespace std;

template<class T>
class nodoAVL{
public:
    nodoAVL(T cl, nodoAVL *iz=NULL, nodoAVL *de=NULL):clave(cl),bal(0),izdo(iz),dcho(de){}
    T clave;
    int bal;
    nodoAVL<T> *izdo;
    nodoAVL<T> *dcho;
    void write();
};

template<class T>
void nodoAVL<T>::write(){
    cout << clave << " ";
}
#endif /* nodo_HPP_ */
