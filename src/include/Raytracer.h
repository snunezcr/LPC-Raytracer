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

#ifndef RAYTRACE_H_
#define RAYTRACE_H_

#include <Punto.h>
#include <Vector.h>
#include <Color.h>
#include <Escena.h>

class Raytracer {
private:
	Escena escena;
	const char *archivoIn;
	const char *archivoOut;
	bool intersecaEsfera(const Rayo &rayo, const Esfera &esfera, float &t);
public:
	Raytracer(const char *ain, const char *aout);
	~Raytracer();
	bool init();
	bool dibujar();
};

#endif /* RAYTRACE_H_ */
