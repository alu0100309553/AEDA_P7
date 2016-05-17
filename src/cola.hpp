/*
 * arbol.hpp
 * Autor: Rubén Labrador Páez
 * EMail: alu0100309553@ull.edu.es
 * Grado en Ingeniería informática, 2ºCurso, Universidad de La Laguna.
 * Algoritmos y estructuras de datos avanzadas, Práctica 7, ArbolAVL
 */

#ifndef cola_HPP_
#define cola_HPP_

#include <iostream>
#include "nodo.hpp"

using namespace std;

// Clase nodo
template<class T_N>
class nodo{
  private:
    nodoAVL<T_N> *valor;
    nodo<T_N> *siguiente;
    int nivel;
    template<class T_C>
    friend class cola;
  public:
    nodo(nodoAVL<T_N> *x, int niv, nodo *sig = NULL){
      valor = x;
      nivel = niv;
      siguiente = sig;
    }
};

// Clase cola
template<class T_C>
class cola{
  private:
    typedef nodo<T_C> *punt_nodo;

    punt_nodo primero;
    punt_nodo ultimo;

  public:
    cola() : ultimo(NULL), primero(NULL) {}
    ~cola();
    void add(nodoAVL<T_C> *ele, int nivel);
    bool vacia();
    T_C leer();
    nodoAVL<T_C>* extraer(int &nivel);
};


template<class T_C>
cola<T_C>::~cola(){}

template<class T_C>
void cola<T_C>::add(nodoAVL<T_C> *ele, int nivel){
  punt_nodo nuevo;
  nuevo = new nodo<T_C>(ele,nivel);
  if(ultimo != NULL){
    ultimo->siguiente = nuevo;
  }

  ultimo = nuevo;

  if(primero == NULL){
    primero = nuevo;
  }
}

template<class T_C>
bool cola<T_C>::vacia(){
    if((primero == NULL) && (ultimo == NULL))    {
        return true;
    }
    else{
        return false;
    }
}

template<class T_C>
nodoAVL<T_C>* cola<T_C>::extraer(int &nivel){
  punt_nodo punt_aux;
  nodoAVL<T_C> *aux;

  punt_aux = primero;
  primero = punt_aux->siguiente;
  aux = punt_aux->valor;
  nivel = punt_aux->nivel;
  delete punt_aux;
  if(primero == NULL){
    ultimo = NULL;
  }
  return aux;
}
#endif /* cola_HPP_ */
