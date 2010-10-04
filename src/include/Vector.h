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

#ifndef VECTOR_H_
#define VECTOR_H_

class Vector {
public:
	float x;
	float y;
	float z;

	Vector();
	Vector(float x, float y, float z);
	Vector operator+(const Vector &v);
	Vector operator-(const Vector &v);
	Vector operator*(float c);
	float operator*(const Vector &v);
};

#endif /* VECTOR_H_ */
