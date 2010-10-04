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

Vector::Vector(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector Vector::operator+(const Vector &v) {
	Vector w(this->x + v.x, this->y + v.y, this->z + v.z);
	return w;
}

Vector Vector::operator-(const Vector &v) {
	Vector w(this->x - v.x, this->y - v.y, this->z - v.z);
	return w;
}

Vector Vector::operator*(float c) {
	Vector v(this->x * c, this->y * c, this->z * c);
	return v;
}

float Vector::operator*(const Vector &v) {
	float f  = this->x * v.x + this->y * v.y + this->z * v.z;
	return f;
}
