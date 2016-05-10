/*
 * arbol.hpp
 * Autor: Rubén Labrador Páez
 * EMail: alu0100309553@ull.edu.es
 * Grado en Ingeniería informática, 2ºCurso, Universidad de La Laguna.
 * Algoritmos y estructuras de datos avanzadas, Práctica 6, ArbolBB
 */

#ifndef arbol_HPP_
#define arbol_HPP_

#include <iostream>
#include "nodo.hpp"
#include "cola.hpp"

using namespace std;

template<class T>
class ArbolBB{
private:
    nodoBB<T> *raiz;
public:
    ArbolBB();
    ~ArbolBB();
    void Podar(nodoBB<T>* &nodo);
    bool EsVacio(nodoBB<T> *nodo);
    bool EsHoja(nodoBB<T> *nodo);
    nodoBB<T>* Buscar(T clave_dada);
    nodoBB<T>* BuscarRama(nodoBB<T>* nodo, T clave_dada);
    void Insertar(T clave_dada);
    void InsertarRama(nodoBB<T>* &nodo, T clave_dada);
    void Eliminar(T clave_dada);
    void EliminarRama(nodoBB<T>* &, T clave_dada);
    void sustituye(nodoBB<T>* &eliminado, nodoBB<T>* &sust);
    void recorreN();
    void procesar(nodoBB<T> *nodo);
};

template<class T>
ArbolBB<T>::ArbolBB():
    raiz(NULL){
    }

template<class T>
ArbolBB<T>::~ArbolBB(){
    Podar(raiz);
}

template<class T>
void ArbolBB<T>::Podar(nodoBB<T>* &nodo){
    if(nodo == NULL){
        return;
    }
    Podar(nodo->izdo);
    Podar(nodo->dcho);
    delete nodo;
    nodo = NULL;
}

template<class T>
bool ArbolBB<T>::EsVacio(nodoBB<T> *nodo){
    return nodo == NULL;
}

template<class T>
bool ArbolBB<T>::EsHoja(nodoBB<T> *nodo){
    return !nodo->dcho && !nodo->izdo;
}

template<class T>
nodoBB<T>* ArbolBB<T>::Buscar(T clave_dada){
    return BuscarRama(raiz, clave_dada);
}

template<class T>
nodoBB<T>* ArbolBB<T>::BuscarRama(nodoBB<T> *nodo, T clave_dada){
    if(nodo == NULL){
        return NULL;
    }

    if(clave_dada == nodo->clave){
        return nodo;
    }

    if(clave_dada < nodo->clave){
        return BuscarRama(nodo->izdo, clave_dada);
    }

    return BuscarRama(nodo->dcho, clave_dada);
}

template<class T>
void ArbolBB<T>::Insertar(T clave_dada){
    InsertarRama(raiz, clave_dada);
}

template<class T>
void ArbolBB<T>::InsertarRama(nodoBB<T>* &nodo, T clave_dada){
    if(nodo == NULL){
        nodo = new nodoBB<T>(clave_dada);
    }
    else if(clave_dada < nodo->clave){
        InsertarRama(nodo->izdo, clave_dada);
    }
    else{
        InsertarRama(nodo->dcho, clave_dada);
    }
}

template<class T>
void ArbolBB<T>::Eliminar(T clave_dada){
    EliminarRama(raiz, clave_dada);
}

template<class T>
void ArbolBB<T>::EliminarRama(nodoBB<T>* &nodo, T clave_dada){
    if(nodo == NULL){
        return;
    }
    if(clave_dada < nodo->clave){
        EliminarRama(nodo->izdo, clave_dada);
    }
    else if(clave_dada > nodo->clave){
        EliminarRama(nodo->dcho, clave_dada);
    }
    else{
        nodoBB<T> *Eliminando = nodo;

        if(nodo->dcho == NULL){
            nodo = nodo->izdo;
        }
        else if(nodo->izdo == NULL){
            nodo = nodo->dcho;
        }
        else{
            sustituye(Eliminando, nodo->izdo);
        }
        delete (Eliminando);
    }
}

template<class T>
void ArbolBB<T>::sustituye(nodoBB<T>* &eliminado, nodoBB<T>* &sust){
    if(sust->dcho != NULL){
        sustituye(eliminado, sust->dcho);
    }
    else{
        eliminado->clave = sust->clave;
        eliminado = sust;
        sust = sust->izdo;
    }
}

template<class T>
void ArbolBB<T>::recorreN(){
    cola<T> cola;
    nodoBB<T> *nodo;

    int nivel = 0;
    int nivel_actual = 0;

    cola.add(raiz,0);

    while(!cola.vacia()){
        nodo = cola.extraer(nivel);

        if(nivel > nivel_actual){
            nivel_actual = nivel;

            cout << endl;
        }
        if(nodo != NULL){
            procesar(nodo);
            cola.add(nodo->izdo, nivel+1);
            cola.add(nodo->dcho, nivel+1);
        }
        else{
            cout << "[.]";
        }
    }
}

template<class T>
void ArbolBB<T>::procesar(nodoBB<T> *nodo){
    nodo->write();
}
#endif /* arbol_HPP_ */
