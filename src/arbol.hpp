/*
 * arbol.hpp
 * Autor: Rubén Labrador Páez
 * EMail: alu0100309553@ull.edu.es
 * Grado en Ingeniería informática, 2ºCurso, Universidad de La Laguna.
 * Algoritmos y estructuras de datos avanzadas, Práctica 7, ArbolAVL
 */

#ifndef arbol_HPP_
#define arbol_HPP_

#include <iostream>
#include "nodo.hpp"
#include "cola.hpp"

using namespace std;

template<class T>
class ArbolAVL{
private:
    nodoAVL<T> *raiz;


public:
    ArbolAVL();
    ~ArbolAVL();
    void el_arbol();
    void Podar(nodoAVL<T>* &nodo);
    bool Buscar(T clave_dada);
    bool BuscarRama(nodoAVL<T>* nodo, T clave_dada);
    //Insertar
    void Insertar(T clave_dada);
    void inserta_bal(nodoAVL<T>* &nodo, nodoAVL<T>* nuevo,bool& crece);
    //Eliminar
    void Eliminar(T clave_dada);
    void EliminarRama(nodoAVL<T>* &nodo, T clave_dada, bool& decrece);
    void sustituye(nodoAVL<T>* &eliminado, nodoAVL<T>* &sust, bool &decrece);
    //Visualizar
    void recorreN();
    void procesar(nodoAVL<T> *nodo);
    //Rotar
    void rotacion_II(nodoAVL<T>* &nodo);
    void rotacion_DD(nodoAVL<T>* &nodo);
    void rotacion_ID(nodoAVL<T>* &nodo);
    void rotacion_DI(nodoAVL<T>* &nodo);
    //Balanceo
    void insert_re_balancea_izda(nodoAVL<T>* &nodo, bool& crece);
    void insert_re_balancea_dcha(nodoAVL<T>* &nodo, bool& crece);
    void eliminar_re_balancea_izda(nodoAVL<T>* &nodo, bool &decrece);
    void eliminar_re_balancea_dcha(nodoAVL<T>* &nodo, bool &decrece);

};

template<class T>
ArbolAVL<T>::ArbolAVL(): raiz(NULL){
    }

template<class T>
ArbolAVL<T>::~ArbolAVL(){
    Podar(raiz);
}

template<class T>
void ArbolAVL<T>::el_arbol(){
  Podar(raiz);
}

template<class T>
void ArbolAVL<T>::Podar(nodoAVL<T>* &nodo){
    if(nodo == NULL){
        return;
    }
    Podar(nodo->izdo); //Poda el subarbol izquierdo
    Podar(nodo->dcho); //Poda el subarbol derecho
    delete nodo; //Elimina el nodo
    nodo = NULL;
}

template<class T>
bool ArbolAVL<T>::Buscar(T clave_dada){
    return BuscarRama(raiz, clave_dada);
}

template<class T>
bool ArbolAVL<T>::BuscarRama(nodoAVL<T> *nodo, T clave_dada){
    if(nodo == NULL){
        return false;
    }

    if(clave_dada == nodo->clave){
        return true;
    }

    if(clave_dada < nodo->clave){
        return BuscarRama(nodo->izdo, clave_dada);
    }

    return BuscarRama(nodo->dcho, clave_dada);
}

template<class T>
void ArbolAVL<T>::Insertar(T clave_dada){
    nodoAVL<T> *nuevo = new nodoAVL<T>(clave_dada);
    bool crece = false;
    inserta_bal(raiz, nuevo, crece);
}

template<class T>
void ArbolAVL<T>::inserta_bal(nodoAVL<T>* &nodo, nodoAVL<T>* nuevo, bool& crece){
    if(nodo == NULL){
        nodo = nuevo;
        crece = true;
    }
    else if(nuevo->clave < nodo->clave){
        inserta_bal(nodo->izdo, nuevo, crece);
        if(crece){
            insert_re_balancea_izda(nodo, crece);
        }
    }
    else{
        inserta_bal(nodo->dcho, nuevo, crece);
        if(crece){
            insert_re_balancea_dcha(nodo, crece);
        }
    }
}

template<class T>
void ArbolAVL<T>::Eliminar(T clave_dada){
    bool decrece = false;
    EliminarRama(raiz, clave_dada, decrece);
}

template<class T>
void ArbolAVL<T>::EliminarRama(nodoAVL<T>* &nodo, T clave_dada, bool& decrece){
    if(nodo == NULL){
        return;
    }
    if(clave_dada < nodo->clave){
        EliminarRama(nodo->izdo, clave_dada, decrece);
        if(decrece)
        {
            eliminar_re_balancea_izda(nodo, decrece);
        }
    }
    else if(clave_dada > nodo->clave){
        EliminarRama(nodo->dcho, clave_dada, decrece);
        if(decrece){
            eliminar_re_balancea_dcha(nodo, decrece);
        }
    }
    else{
        nodoAVL<T> *Eliminando = nodo;
        if(nodo->izdo == NULL){
            nodo = nodo->dcho;
            decrece = true;
        }
        else if(nodo->dcho == NULL){
            nodo = nodo->izdo;
            decrece = true;
        }
        else{
            sustituye(Eliminando, nodo->izdo, decrece);
            if(decrece){
                eliminar_re_balancea_izda(nodo, decrece);
            }
        }
        delete (Eliminando);
    }
}

template<class T>
void ArbolAVL<T>::sustituye(nodoAVL<T>* &eliminado, nodoAVL<T>* &sust, bool &decrece){
    if(sust->dcho != NULL){
        sustituye(eliminado, sust->dcho, decrece);
        if(decrece){
            eliminar_re_balancea_dcha(sust, decrece);
        }
    }
    else{
        eliminado->clave = sust->clave;
        eliminado = sust;
        sust = sust->izdo;
        decrece = true;
    }
}

template<class T>
void ArbolAVL<T>::recorreN(){
    cola<T> cola;
    nodoAVL<T> *nodo;

    int nivel = 0;
    int nivel_actual = 0;

    cola.add(raiz,0); //La cola recibe el dato y el nivel

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
void ArbolAVL<T>::procesar(nodoAVL<T> *nodo){
    nodo->write();
}

template<class T>
void ArbolAVL<T>::rotacion_II(nodoAVL<T>* &nodo){
    nodoAVL<T>* nodo1 = nodo->izdo;
    nodo->izdo = nodo1->dcho;
    nodo1->dcho = nodo;

    if(nodo1->bal == 1){
        nodo->bal = 0;
        nodo1->bal = 0;
    }
    else{
        nodo->bal = 1;
        nodo1->bal = -1;
    }
    nodo = nodo1;
}

template<class T>
void ArbolAVL<T>::rotacion_DD(nodoAVL<T>* &nodo){
    nodoAVL<T>* nodo1 = nodo->dcho;
    nodo->dcho = nodo1->izdo;
    nodo1->izdo = nodo;

    if(nodo1->bal == -1){
        nodo->bal = 0;
        nodo1->bal = 0;
    }
    else{
        nodo->bal = -1;
        nodo1->bal = 1;
    }
    nodo = nodo1;
}

template<class T>
void ArbolAVL<T>::rotacion_ID(nodoAVL<T>* &nodo){
    nodoAVL<T>* nodo1 = nodo->izdo;
    nodoAVL<T>* nodo2 = nodo1->dcho;
    nodo->izdo = nodo2->dcho;
    nodo2->dcho = nodo;
    nodo1->dcho = nodo2->izdo;
    nodo2->izdo = nodo1;

    if(nodo2->bal == -1){
        nodo1->bal = 1;
    }
    else{
        nodo1->bal = 0;
    }
    if(nodo2->bal == 1){
        nodo->bal = -1;
    }
    else{
        nodo->bal = 0;
    }
    nodo2->bal = 0;
    nodo = nodo2;
}

template<class T>
void ArbolAVL<T>::rotacion_DI(nodoAVL<T>* &nodo){
    nodoAVL<T>* nodo1 = nodo->dcho;
    nodoAVL<T>* nodo2 = nodo1->izdo;
    nodo->dcho = nodo2->izdo;
    nodo2->izdo = nodo;
    nodo1->izdo = nodo2->dcho;
    nodo2->dcho = nodo1;

    if(nodo2->bal == 1){
        nodo1->bal = -1;
    }
    else{
        nodo1->bal = 0;
    }
    if(nodo2->bal == -1){
        nodo->bal = 1;
    }
    else{
        nodo->bal = 0;
    }
    nodo2->bal = 0;
    nodo = nodo2;
}

template<class T>
void ArbolAVL<T>::insert_re_balancea_izda(nodoAVL<T>* &nodo, bool& crece){
    switch(nodo->bal){
    case -1:{
            nodo->bal = 0;
            crece = false;
        }break;
    case 0:{
            nodo->bal = 1;
        }break;
    case 1:{
            nodoAVL<T>* nodo1 = nodo->izdo;
            if(nodo1->bal == 1)
            {
                rotacion_II(nodo);
            }
            else
            {
                rotacion_ID(nodo);
            }
            crece = false;
        }break;
    }
}

template<class T>
void ArbolAVL<T>::insert_re_balancea_dcha(nodoAVL<T>* &nodo, bool& crece){
    switch(nodo->bal){
    case 1:{
            nodo->bal = 0;
            crece = false;
        }break;
    case 0:{
            nodo->bal = -1;
        }break;
    case -1:{
            nodoAVL<T>* nodo1 = nodo->dcho;
            if(nodo1->bal == -1)
            {
                rotacion_DD(nodo);
            }
            else
            {
                rotacion_DI(nodo);
            }
            crece = false;
        }break;
    }
}

template<class T>
void ArbolAVL<T>::eliminar_re_balancea_izda(nodoAVL<T>* &nodo, bool &decrece)
{
    switch(nodo->bal){
    case -1:{
            nodoAVL<T> *nodo1 = nodo->dcho;
            if(nodo1->bal > 0){
                rotacion_DI(nodo);
            }
            else{
                if(nodo1->bal == 0){
                    decrece = false;
                }
                rotacion_DD(nodo);
            }
        }break;
    case 0:{
            nodo->bal = -1;
            decrece = false;
        }break;
    case 1:{
            nodo->bal = 0;
        }break;
    }
}

template<class T>
void ArbolAVL<T>::eliminar_re_balancea_dcha(nodoAVL<T>* &nodo, bool &decrece)
{
    switch(nodo->bal){
    case 1:{
            nodoAVL<T> *nodo1 = nodo->izdo;
            if(nodo1->bal < 0){
                rotacion_ID(nodo);
            }
            else{
                if(nodo1->bal == 0){
                    decrece = false;
                }
                rotacion_II(nodo);
            }
        }break;
    case 0:{
            nodo->bal = 1;
            decrece = false;
        }break;
    case -1:{
            nodo->bal = 0;
        }break;
    }
}

#endif /* arbol_HPP_ */
