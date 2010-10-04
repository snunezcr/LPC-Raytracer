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

Raytracer::Raytracer(char *ain, char *aout) {
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

	ostream archivoTGA(archivoOut, ios::binary);

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
			float rojo = 0.0f;
			float verde =0.0f;
			float azul = 0.0f;
			float c = 1.0f;
			int level;

			/* Se coloca el rayo a una distancia promedio para evitar problemas
			 * de redondeo. Una forma de mejorarlo es
			 */
			Punto origen(float(i), float(j), -1000.0f);
			Vector normal(0.0f, 0.0f, 1.0f);
			Rayo rayo(origen, normal);

			do {
				int k;
				int m;
				float t = 2000.0f;
				int esferaActual = -1;

				for (k = 0; k < escena.listaEsferas.size(); k++)
					if (intersecaEsfera(rayo, escena.listaEsferas[k], t))
						esferaActual = k;

				if (esferaActual == -1)
					break;

				Punto posRayoNormal = rayo.inicio - t * rayo.direccion;
				Vector rayoNormal = posRayoNormal -
						escena.listaEsferas[k].posicion;
				float divisorNormal = rayoNormal * rayoNormal;

				if (divisorNormal == 0.0f)
					break;

				divisorNormal = 1.0f/sqrt(divisorNormal);
				rayoNormal = divisorNormal * rayoNormal;

				Material materialActual =
					escena.listaMateriales[escena.listaEsferas[k].idMaterial];

				/* Se calcula el efecto de la luz sobre un objeto y su color */
				for (m = 0; m < escena.listaLuces.size(); m++) {
					Luz luzActual = escena.listaLuces[m];
					Vector distanciaLuz = luzActual - posRayoNormal;

					if (rayoNormal * distanciaLuz <= 0.0f)
						continue;

					float magnitud = sqrt(distanciaLuz * distanciaLuz);

					if (magnitud <= 0.0f)
						continue;

					Rayo rayoLuz;
					rayoLuz.inicio = posRayoNormal;
					rayoLuz.direccion = (1 / magnitud) * distanciaLuz;

					/* Se calculan las sombras para cada uno de los objetos */
					bool enSombra = false;

					for (k = 0; k < escena.listaEsferas.size(); k++) {
						if (intersecaEsfera(rayoLuz, escena.listaEsferas[k],
																	magnitud)) {
							enSombra = true;
							break;
						}
					}

					/* Se calcula la relacion de Lambert que correlaciona
					 * intensidad, direccion del rayo de Luz y material
					 */
					if (! enSombra) {
						float lambert = (rayoLuz.dir * rayoNormal) * c;
						rojo += lambert * luzActual.rojo * materialActual.rojo;
						verde += lambert * luzActual.verde * materialActual.verde;
						azul += lambert * luzActual.azul * materialActual.azul;
					}
				}

				/* Se itera para cada una de las intensidades de reflexion del
				 * material (i.e. capacidad de reflejar la luz.
				 */
				c *= materialActual.reflexion;
				float reflejado = 2.0f * (rayo * rayoNormal);
				rayo.inicio = posRayoNormal;
				rayo.direccion = rayo.direccion - reflejado * rayoNormal;
			} while (c > 0.0f && level < 10);
		}
	}
}

bool Raytracer::intersecaEsfera(const Rayo &rayo, const Esfera &esfera,
																	float &t) {
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
