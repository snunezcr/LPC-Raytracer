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

#include <Vector.h>

Vector::Vector() : x(0), y(0), z(0) {
}

Vector::Vector(float xx, float yy, float zz) {
	x = xx;
	y = yy;
	z = zz;
}

Vector Vector::operator=(const Vector &v) {
	x = v.x;
	y = v.y;
	z = v.z;

	return *this;
}

Vector Vector::operator+(const Vector &v) const {
	Vector w(x + v.x, y + v.y, z + v.z);
	return w;
}

Vector Vector::operator-(const Vector &v) const {
	Vector w(x - v.x, y - v.y, z - v.z);
	return w;
}

Vector Vector::operator*(float c) const {
	Vector v(x * c, y * c, z * c);
	return v;
}

float Vector::operator*(const Vector &v) const {
	float f = x * v.x + y * v.y + z * v.z;
	return f;
}
