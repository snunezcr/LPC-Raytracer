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

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include <Raytracer.h>

Raytracer::Raytracer(const char *ain, const char *aout) {
	archivoIn = ain;
	archivoOut = aout;
}

Raytracer::~Raytracer() {

}

bool Raytracer::init() {
	return escena.init(archivoIn);
}

bool Raytracer::dibujar() {
	int i;
	int j;

	ofstream archivoTGA(archivoOut, ios_base::binary);

	if (! archivoTGA)
		return false;

	/* Se escribe el encabezado del formato TGA */

	/* RGB sin compresion */
	archivoTGA.put(0);
	archivoTGA.put(0);
	archivoTGA.put(2);

	/* Padding de compresion */
	archivoTGA.put(0);
	archivoTGA.put(0);
	archivoTGA.put(0);
	archivoTGA.put(0);
	archivoTGA.put(0);

	/* Origen de la imagen */
	archivoTGA.put(0);
	archivoTGA.put(0);
	archivoTGA.put(0);
	archivoTGA.put(0);

	/* Dimensiones de la imagen */
	archivoTGA.put((unsigned char)(escena.tamX & 0x00FF));
	archivoTGA.put((unsigned char)((escena.tamX & 0xFF00) / 256));
	archivoTGA.put((unsigned char)(escena.tamY & 0x00FF));
	archivoTGA.put((unsigned char)((escena.tamY & 0xFF00) / 256));

	/* Profundidad del bitmap */
	archivoTGA.put(24);

	/* Fin del encabezado TGA */
	archivoTGA.put(0);

	/* Para cada pixel en la escena */
	for (j = 0; j < escena.tamY; j++) {
		for (i = 0; i < escena.tamX; i++) {
			/* Se coloca el rayo a una distancia promedio para evitar problemas
			 * de redondeo. Una forma de mejorarlo es incrementar la cantidad de
			 * iteraciones.
			 */
			Punto origen(float(i), float(j), -1000.0f);
			Vector u(0.0f, 0.0f, 1.0f);
			Rayo rayo(origen, u);
			Color pixel = agregarRayo(rayo); 
			
			
			archivoTGA.put((unsigned char) min(pixel.azul*255.0f, 255.0f));
			archivoTGA.put((unsigned char) min(pixel.verde*255.0f, 255.0f));
			archivoTGA.put((unsigned char) min(pixel.rojo*255.0f, 255.0f));
		}
	}
	return true;
}

bool Raytracer::intersecaEsfera(const Rayo &rayo, const Esfera &esfera, float &t) {
	Vector distancia = esfera.posicion - rayo.inicio;
	float b = rayo.direccion * distancia;
	float d = b*b - distancia*distancia + esfera.tamano*esfera.tamano;

	if (d < 0.0f)
		return false;

	float lim_izq = b - sqrtf(d);
	float lim_der = b + sqrtf(d);

	bool resultado = false;

	if (lim_izq > 0.1f && lim_izq < t) {
		t = lim_izq;
		resultado = true;
	}

	if (lim_der > 0.1f && lim_der < t) {
		t = lim_izq;
		resultado = true;
	}

	return resultado;
}

Color Raytracer::agregarRayo(Rayo &rayo) {
	Color resultado(0.0f, 0.0f, 0.0f);
	float c = 1.0f;
	int nivel = 0;
	/* Se coloca el rayo a una distancia promedio para evitar problemas
	 * de redondeo. Una forma de mejorarlo es
	 */

	do {
		unsigned int k;
		int m;
		float t = 2000.0f;
		int esferaActual = -1;

		for (k = 0; k < escena.listaEsferas.size(); k++) {
			if (intersecaEsfera(rayo, escena.listaEsferas[k], t)) {
				esferaActual = k;
			}
		}

		if (esferaActual == -1)
			break;

		Punto nInicio = rayo.inicio + (rayo.direccion * t);
		Vector normal = nInicio -
				escena.listaEsferas[esferaActual].posicion;
		float divisorNormal = normal * normal;

		if (divisorNormal == 0.0f)
			break;

		divisorNormal = 1.0f/sqrt(divisorNormal);
		normal = normal*divisorNormal;

		Material materialActual =
			escena.listaMateriales[escena.listaEsferas[esferaActual].idMaterial];
		/* Se calcula el efecto de la luz sobre un objeto y su color */
		for (m = 0; m < escena.listaLuces.size(); m++) {
			Luz luzActual = escena.listaLuces[m];
			Vector distanciaLuz = luzActual.posicion - nInicio;

			if (normal * distanciaLuz <= 0.0f)
				continue;

			float magnitud = sqrt(distanciaLuz * distanciaLuz);

			if (magnitud <= 0.0f)
				continue;

			Rayo rayoLuz;
			rayoLuz.inicio = nInicio;
			rayoLuz.direccion = distanciaLuz*(1 / magnitud);

			/* Se calculan las sombras para cada uno de los objetos */
			bool enSombra = false;

			for (k = 0; k < escena.listaEsferas.size(); k++) {
				if (intersecaEsfera(rayoLuz, escena.listaEsferas[k], magnitud)) {
					enSombra = true;
					break;
				}
			}

			/* Se calcula la relacion de Lambert que correlaciona
			 * intensidad, direccion del rayo de Luz y material
			 */
			if (! enSombra) {
				float lambert = (rayoLuz.direccion * normal) * c;
				resultado.rojo += lambert * luzActual.intensidad.rojo *
						materialActual.difusividad.rojo;
				resultado.verde += lambert * luzActual.intensidad.verde *
						materialActual.difusividad.verde;
				resultado.azul += lambert * luzActual.intensidad.azul *
						materialActual.difusividad.azul;
			}
		}

		/* Se itera para cada una de las intensidades de reflexion del
		 * material (i.e. capacidad de reflejar la luz).
		 */
		c *= materialActual.reflexion;
		float reflejado = 2.0f * (rayo.direccion*normal);
		rayo.inicio = nInicio;
		rayo.direccion = rayo.direccion - normal*reflejado;

		nivel++;
	} while (c > 0.0f && nivel < 10);


	return resultado;
}
