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

#include <Color.h>

Color::Color() {
        rojo = 0;
        verde = 0;
        azul = 0;
}

Color::Color(float r, float v, float a) {
	rojo = r;
	verde = v;
	azul = a;
}

Color Color::operator+=(const Color &c) {
	rojo += c.rojo;
	verde += c.verde;
	azul += c.azul;

	return *this;
}

/*
float & Color::obtenerCanal(OFFSET off) {
	return reinterpret_cast<float *>(this)[off];
}
*/

float Color::obtenerCanal(OFFSET off)  {
	return reinterpret_cast<const float *>(this)[off];
}

Color Color::operator*(const Color &c) {
	Color k(this->rojo * c.rojo, this->verde * c.verde, this->azul * c.azul);
	return k;
}

Color Color::operator*(float c) {
	Color k(this->rojo * c, this->verde * c, this->azul * c);
	return k;
}

Color Color::operator+(const Color &c) {
	Color k(this->rojo + c.rojo, this->verde + c.verde, this->azul + c.azul);
	return k;
}
