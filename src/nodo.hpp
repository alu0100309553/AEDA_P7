/*
 * nodo.hpp
 * Autor: Rubén Labrador Páez
 * EMail: alu0100309553@ull.edu.es
 * Grado en Ingeniería informática, 2ºCurso, Universidad de La Laguna.
 * Algoritmos y estructuras de datos avanzadas, Práctica 6, ArbolBB
 */

#ifndef nodo_HPP_
#define nodo_HPP_

#include <iostream>

using namespace std;

template<class T>
class nodoBB
{
public:
    nodoBB(T cl, nodoBB *iz=NULL, nodoBB *de=NULL):
        clave(cl),
        izdo(iz),
        dcho(de)
        {}
    T clave;
    nodoBB<T> *izdo;
    nodoBB<T> *dcho;

    void write();
};

template<class T>
void nodoBB<T>::write()
{
    cout << clave << " ";
}
#endif /* nodo_HPP_ */
