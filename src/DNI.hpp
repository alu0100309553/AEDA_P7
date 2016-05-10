/*
 * DNI.hpp
 * Autor: Rubén Labrador Páez
 * EMail: alu0100309553@ull.edu.es
 * Grado en Ingeniería informática, 2ºCurso, Universidad de La Laguna.
 * Algoritmos y estructuras de datos avanzadas, Práctica 6, ArbolBB
 */

#ifndef DNI_HPP_
#define DNI_HPP_

//Clase DNI
class DNI {
public:
	static int contador;
	int dniN;  //Variable que almacena el número del DNI
	DNI();
	DNI(int N);
	virtual ~DNI();
	operator int() {return dniN;}; //Operador que convierte DNI en un entero
	bool operator ==(DNI b);
	bool operator <(DNI b);
	bool operator >(DNI b);
	bool operator ==(int b);
	int operator %(int n);
	void operator =(int n);
};
#endif /* DNI_HPP_ */
