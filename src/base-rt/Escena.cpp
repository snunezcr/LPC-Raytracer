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
#include <Color.h>
#include <Escena.h>
#include <Configuracion.h>
#include <Raytracer.h>

using namespace std;

const Vector vectorNulo(0.0f, 0.0f, 0.0f);
const Punto origen(0.0f, 0.0f, 0.0f);
const String cadenaVacia("");

Material::Material() : difusividad(0.0f, 0.0f, 0.0f), 
					especularidad(0.0f, 0.0f, 0.0f) {
	reflexion = 0;
	potencia = 0;
}

Material::Material(float rf, float pt, Color &dif, Color &esp) {
	reflexion = rf;
	potencia = pt;
	difusividad = dif;
	especularidad = esp;
}

Material::~Material() {

}

Material Material::operator=(const Material &mat) {
	reflexion = mat.reflexion;
	potencia = mat.potencia;
	difusividad = mat.difusividad;
	especularidad = mat.especularidad;
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

Esfera Esfera::operator=(const Esfera &es) {
	posicion = es.posicion;
	tamano = es.tamano;
	idMaterial = es.idMaterial;
}

Luz::Luz() : posicion(0.0f, 0.0f, 0.0f), intensidad(0.0f, 0.0f, 0.0f) {
	
}

Luz::Luz(Punto &p, Color &it) {
	posicion = p;
	intensidad = it;
}

Luz::~Luz() {

}

Luz Luz::operator=(const Luz &lz) {
	posicion = lz.posicion;
	intensidad = lz.intensidad;
}

Rayo::Rayo() : inicio(0.0f, 0.0f, 0.0f), direccion(0.0f, 0.0f, 0.0f) {

}

Rayo::Rayo(Punto &i, Vector &d) {
	inicio = i;
	direccion = d;
}

Rayo::~Rayo() {

}

Rayo Rayo::operator=(const Rayo &ry) {
	inicio = ry.inicio;
	direccion = ry.direccion;
}

Escena::Escena() {
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

	listaMateriales.resize(numMateriales);
	listaEsferas.resize(numEsferas);
	listaLuces.resize(numLuces);

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
	float colorEsp;
	float colorPot;

	colorDif = float(archivo.cargarPorNombreFloat("Difusividad", 0.0f));
	Vector vecDif(colorDif, colorDif, colorDif);
	vecDif = archivo.obtenerPorNombreVector("Difusividad", vecDif);
	material.difusividad.rojo = vecDif.x;
	material.difusividad.verde = vecDif.y;
	material.difusividad.azul = vecDif.z;

	colorEsp = float(archivo.cargarPorNombreFloat("Especularidad", 0.0f));
        Vector vecEsp(colorDif, colorDif, colorDif);
        vecEsp = archivo.obtenerPorNombreVector("Especularidad", vecEsp);
        material.especularidad.rojo = vecEsp.x;
        material.especularidad.verde = vecEsp.y;
        material.especularidad.azul = vecEsp.z;

	colorRef = float(archivo.cargarPorNombreFloat("Reflexividad", 0.0f));
	material.reflexion = colorRef;

	colorPot = float(archivo.cargarPorNombreFloat("Potencia", 0.0f));
        material.potencia = colorPot;
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
	luz.intensidad.rojo = vectorInt.x;
	luz.intensidad.verde = vectorInt.y;
	luz.intensidad.azul = vectorInt.z;
}

