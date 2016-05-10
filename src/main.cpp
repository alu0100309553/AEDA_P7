/*
 * main.cpp
 * Autor: Rubén Labrador Páez
 * EMail: alu0100309553@ull.edu.es
 * Grado en Ingeniería informática, 2ºCurso, Universidad de La Laguna.
 * Algoritmos y estructuras de datos avanzadas, Práctica 6, ArbolBB
 */

#include <iostream>
#include <iomanip>
#include <random>
#include <cstdlib>
#include "arbol.hpp"
#include "DNI.hpp"



using namespace std;

int main(){

	int opcion = 0;
	cout << "==== Modo del programa ====" << endl << endl;
	cout << "1. Demostracion" << endl;
	cout << "2. Estadistica" << endl;
	cin >> opcion;

	switch(opcion){
		case 1:{
			//Modo demostracion
			ArbolBB<DNI> arbol;
			int opcionDemo = 0;
			do{
				cout << "==== ARBOL ====" << endl;
				arbol.recorreN();
				cout << endl << endl << "1. Insertar clave" << endl;
				cout << "2. Eliminar clave" << endl;
				cout << "3. Salir" << endl;
				cin >> opcionDemo;
				switch(opcionDemo){
					case 1:{
						int clave = 0;

						cout << endl << "Insertar clave: "<< endl;
						cin >> clave;

						clave += 30000000;
						clave %= 80000000;
						DNI dni(clave);


						arbol.Insertar(dni);
					}break;
					case 2:{
						int clave = 0;
						cout << "Introduzca clave: " << endl;
						cin >> clave;

						clave += 30000000;
						clave %= 80000000;
						DNI dni(clave);


						arbol.Eliminar(dni);
					}break;
				}
			}while(opcionDemo != 3);
		}break;
		case 2:{
			ArbolBB<DNI> arbol;
			int num_nodos;
			int num_pruebas;
			cout << "Introduzca el numero de nodos del arbol: ";
			cin >> num_nodos;
			cout << "Introduzca el numero de pruebas: ";
			cin >> num_pruebas;
			DNI vector_insertar[num_pruebas];
			DNI vector_buscar[num_pruebas];
			for (int j = 0; j<num_pruebas; j++){
				int aux = (rand() % 50000000) + 30000000;
				vector_insertar[j] = aux;
				aux = (rand() % 50000000) + 30000000;
				vector_buscar[j] = aux;
			}

			for(int i = 0; i < num_pruebas; i++){
				arbol.Insertar(vector_buscar[i]);
			}

			int maxBuscar = 0;
			int minBuscar = 10000000;
			int valueBuscar = 0;
			int mediaBuscar = 0;

			for(int i = 0; i < num_pruebas; i++){
				DNI::contador=0;
				arbol.Buscar(vector_buscar[i]);
				valueBuscar = DNI::contador;
				if (valueBuscar < minBuscar){
					minBuscar = valueBuscar;
				}
				if (valueBuscar > maxBuscar){
					maxBuscar = valueBuscar;
				}
				mediaBuscar += valueBuscar;
			}
			mediaBuscar /= num_pruebas;
			int maxInsertar = 0;
			int minInsertar = 10000000;
			int valueInsertar = 0;
			int mediaInsertar = 0;
			for(int i = 0; i < num_pruebas; i++){
				DNI::contador=0;
				arbol.Buscar(vector_insertar[i]);
				valueInsertar = DNI::contador;
				if (valueInsertar < minInsertar){
					minInsertar = valueInsertar;
				}
				if (valueInsertar > maxInsertar){
					maxInsertar = valueInsertar;
				}
				mediaInsertar += valueInsertar;
			}
			mediaInsertar /= num_pruebas;
			cout << setw(13) << fixed << "N" << setw(10) << fixed << "P" << setw(10) << fixed << "Minimo" << setw(10) << fixed << "Medio" << setw(10) << fixed << "Maximo" << endl;

			cout << "Busqueda:" << setw(4) << fixed << num_nodos;
			cout << setw(10) << fixed << num_pruebas;
			cout << setw(10) << fixed << minBuscar;
			cout << setw(10) << fixed << mediaBuscar;
			cout << setw(10) << fixed << maxBuscar << endl;

			cout << "Insercion:" << setw(3) << fixed << num_nodos;
			cout << setw(10) << fixed << num_pruebas;
			cout << setw(10) << fixed << minInsertar;
			cout << setw(10) << fixed << mediaInsertar;
			cout << setw(10) << fixed << maxInsertar << endl;
			cout << endl << endl;
		}break;
	}
	return 0;
}
