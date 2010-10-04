/*
 * Instituto Tecnologico de Costa Rica
 * Sede Cartago
 *
 * Ingenieria en Computacion
 * Lenguajes de Programacion
 *
 * Orientacion a Objetos: el LPC-RayTracer
 * Instructor: Santiago Nunez Corrales
 *
 * Objetivo del proyecto: el estudiante debe agregar nuevos tipos de objetos geometricos
 * para generar imagenes mas complejas utilizando Geometria Constructiva de Solidos
 */

#ifndef PUNTO_H_
#define PUNTO_H_

#include <Vector.h>

class Punto {
public:
	float x;
	float y;
	float z;

	Punto();
	Punto(float x, float y, float z);
	Punto operator+(const Vector &v);
	Punto operator-(const Vector &v);
	Vector operator-(const Punto &p);
};

#endif /* PUNTO_H_ */