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

#ifndef COLOR_H_
#define COLOR_H_

class Color {
public:
	enum OFFSET {
		OFF_ROJO = 0,
		OFF_VERDE = 1,
		OFF_AZUL = 2,
		OFF_MAX = 0
	};

	float rojo;
	float verde;
	float azul;

	Color();
	Color(float r, float v, float a);
	Color operator+=(const Color &c);
//	float &obtenerCanal(OFFSET off);
	float obtenerCanal(OFFSET off);
	Color operator*(const Color &c);
	Color operator*(float c);
	Color operator+(const Color &c);
};

#endif /* COLOR_H_ */
