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

Punto Punto::operator+(const Vector &v) const {
	Punto p(x + v.x, y + v.y, z + v.z);

	return p;
}

Punto Punto::operator-(const Vector &v) const {
	Punto p(x - v.x, y - v.y, z - v.z);

	return p;
}

Vector Punto::operator-(const Punto &p) const {
	Vector v(x - p.x, y - p.y, z - p.z);

	return v;
}
