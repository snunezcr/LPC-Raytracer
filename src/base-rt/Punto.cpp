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

#include <Punto.h>
#include <Vector.h>

Punto::Punto() : x(0), y(0), z(0) {
}

Punto::Punto(float xx, float yy, float zz) {
	x = xx;
	y = yy;
	z = zz;
}

Punto Punto::operator+(const Vector &v) {
	Punto p(this->x + v.x, this->y + v.y, this->z + v.z);

	return p;
}

Punto Punto::operator-(const Vector &v) {
	Punto p(this->x - v.x, this->y - v.y, this->z - v.z);

	return p;
}

Vector Punto::operator-(const Punto &p) {
	Vector v(this->x - p.x, this->y - p.y, this->z - p.z);

	return v;
}
