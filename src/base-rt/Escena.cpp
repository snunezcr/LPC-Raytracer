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
#include <Escena.h>
#include <Configuracion.h>
#include <Raytracer.h>

using namespace std;

const Vector vectorNulo(0.0f, 0.0f, 0.0f);
const Punto origen(0.0f, 0.0f, 0.0f);
const String cadenaVacia("");

Material::Material() {
	reflexion = 0;
	rojo = 0;
	verde = 0;
	azul = 0;
}

Material::Material(float rf, float rj, float vd, float az) {
	reflexion = rf;
	rojo = rj;
	verde = vd;
	azul = az;
}

Material::~Material() {

}

Esfera::Esfera() : posicion(0.0f, 0.0f, 0.0f) {
	tamano = 0.0f;
	idMaterial = 0;
}

Esfera::Esfera (Punto &p, float t, int id) {
	posicion = p;
	tamano = t;
	idMaterial = id;
}

Esfera::~Esfera() {

}

Luz::Luz() : posicion(0.0f, 0.0f, 0.0f) {
	rojo = 0;
	verde = 0;
	azul = 0;
}

Luz::Luz(Punto &p, float rj, float vd, float az) {
	posicion = p;
	rojo = rj;
	verde = vd;
	azul = az;
}

Luz::~Luz() {

}

Rayo::Rayo() : inicio(0.0f, 0.0f, 0.0f), direccion(0.0f, 0.0f, 0.0f) {

}

Rayo::Rayo(Punto &i, Vector &d) {
	inicio = i;
	direccion = d;
}

Rayo::~Rayo() {

}

Escena::Escena() : listaMateriales(), listaEsferas(), listaLuces() {
	tamX = 0;
	tamY = 0;
}

Escena::~Escena() {

}

bool Escena::init(const char *archivo) {
	int numMateriales;
	int numEsferas;
	int numLuces;
	int i;

	Configuracion archivoEscena(archivo);

	if (archivoEscena.establecerSeccion("Escena") == -1) {
		cout << "Expresion mal formada. No se encontro seccion Escena." << endl;
		return false;
	}

	tamX = archivoEscena.cargarPorNombreInt("Imagen.Ancho", 800);
	tamY = archivoEscena.cargarPorNombreInt("Imagen.Alto", 600);

	numMateriales = archivoEscena.cargarPorNombreInt("CantidadMateriales", 0);
	numEsferas = archivoEscena.cargarPorNombreInt("CantidadEsferas", 0);
	numLuces = archivoEscena.cargarPorNombreInt("CantidadLuces", 0);

	for (i = 0; i < numMateriales; i++) {
		Material &actual = listaMateriales[i];
		String seccion("Material");
		seccion.pegar((unsigned long) i);

		if (archivoEscena.establecerSeccion(seccion) == -1) {
			cout << "Expresion mal formada. No se encontro seccion Material."
				 << endl;
			return false;
		}

		obtenerMaterial(archivoEscena, actual);
	}

	for (i = 0; i < numEsferas; i++) {
		Esfera &actual = listaEsferas[i];
		String seccion("Esfera");
		seccion.pegar((unsigned long) i);

		if (archivoEscena.establecerSeccion(seccion) == -1) {
			cout << "Expresion mal formada. No se encontro seccion Esfera."
				 << endl;
			return false;
		}

		obtenerEsfera(archivoEscena, actual);
	}

	for (i = 0; i < numLuces; i++) {
		Luz &actual = listaLuces[i];
		String seccion("Luz");
		seccion.pegar((unsigned long) i);

		if (archivoEscena.establecerSeccion(seccion) == -1) {
			cout << "Expresion mal formada. No se encontro seccion Esfera."
				 << endl;
			return false;
		}

		obtenerLuz(archivoEscena, actual);
	}

	return true;
}

void Escena::obtenerMaterial(const Configuracion &archivo, Material &material) {
	float colorDif;
	float colorRef;

	colorDif = float(archivo.cargarPorNombreFloat("Difusividad", 0.0f));
	Vector vecColor(colorDif, colorDif, colorDif);
	vecColor = archivo.obtenerPorNombreVector("Difusividad", vecColor);
	material.rojo = vecColor.x;
	material.verde = vecColor.y;
	material.azul = vecColor.z;

	colorRef = float(archivo.cargarPorNombreFloat("Reflexividad", 0.0f));
	material.reflexion = colorRef;
}

void Escena::obtenerEsfera(const Configuracion &archivo, Esfera &esfera) {
	esfera.posicion = archivo.obtenerPorNombrePunto("Centro", origen);
	esfera.tamano = float(archivo.cargarPorNombreFloat("Tamano", 0.0f));
	esfera.idMaterial = archivo.cargarPorNombreInt("Material.id", 0);
}

void Escena::obtenerLuz(const Configuracion &archivo, Luz &luz) {
	float colorInt;

	luz.posicion = archivo.obtenerPorNombrePunto("Posicion", origen);

	colorInt = float(archivo.cargarPorNombreFloat("Intensidad", 0.0f));
	Vector vectorInt(colorInt, colorInt, colorInt);
	vectorInt = archivo.obtenerPorNombreVector("Intensidad", vectorInt);
	luz.rojo = vectorInt.x;
	luz.verde = vectorInt.y;
	luz.azul = vectorInt.z;
}
