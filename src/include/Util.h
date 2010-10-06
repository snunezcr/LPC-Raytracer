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

#ifndef UTIL_H_
#define UTIL_H_

#include <cmath>

inline float inversoSqrt(float valor) {
	return 1.0f/sqrtf(valor); 
}

float codificarSRGB(float color) {
	if (color <= 0.0031308f)
		return 12.92f*color;
	else
		return 1.055f*powf(color, 0.4166667f) - 0.055f;
}

#endif /* UTIL_H_ */
